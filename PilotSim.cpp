#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <iomanip>
#include "PilotSim.h"

Pilot::Pilot(){
    this->meanX = 0;
    this->meanY = 0;
    this->variance = 0;
    this->finalMean = 0;
    this->stdevX = 500;
    this->stdevY = 250;
    this->radius = 300;
    this->probHitTarget = 0;
    this->confidenceInterval = .95;
    this->alpha = 1 - confidenceInterval;
    this->t = 0;
    for (int i = 0; i < trialSize; i++){
        this->normalX[i] = 0;
        this->normalY[i] = 0;
    }
}
Pilot::Pilot(const Pilot& pilotName) {
    this->meanX = pilotName.meanX;
    this->meanY = pilotName.meanY;
    this->variance = pilotName.variance;
    this->finalMean = pilotName.finalMean;
    this->stdevX = pilotName.stdevX;
    this->stdevY = pilotName.stdevY;
    this->radius = pilotName.radius;
    this->probHitTarget = pilotName.probHitTarget;
    this->confidenceInterval = pilotName.confidenceInterval;
    this->alpha = pilotName.alpha;

    for(int i = 0; i < trialSize; i++){
        this->normalX[i] = pilotName.normalX[i];
        this->normalY[i] = pilotName.normalY[i];
    }
}
double rationalApprox(double t){
    // Abramowitz and Stegun formula 26.2.23.
    // The absolute value of the error should be less than 4.5 e-4.
    double c[] = {2.515517, 0.802853, 0.010328};
    double d[] = {1.432788, 0.189269, 0.001308};
    return t - ((c[2]*t + c[1])*t + c[0]) / 
               (((d[2]*t + d[1])*t + d[0])*t + 1.0);
}
double normalInversePoints(double prob){
    if (prob <= 0.0 || prob >= 1.0)
    {
        std::cout << "Invalid argument, " << prob 
        << "should be between 0 and 1." << std::endl;
    }
    if (prob < 0.5)
    {
        // F^-1(p) = - G^-1(p)
        return -(rationalApprox(sqrt(-2.0*log(prob))));
    }
    else
    {
        // F^-1(p) = G^-1(1-p)
        return rationalApprox(sqrt(-2.0*log(1-prob)));
    }
}

std::default_random_engine generator; 
double Pilot::getRand(double stdev, double mean){
    std::normal_distribution<double> distribution(mean, stdev);
    double value = distribution(generator);
    return value;
};
void Pilot::generateRandPoints(){
    for(int i = 0; i <= trialSize; ++i){
        //get x and y variates
        // x = Z*stdevX + meanX
        // y = Z*stdevY + meanY
        this->normalX[i] = (this->stdevX * this->getRand(this->stdevX, this->meanX)) + this->meanX;
        this->normalY[i] = (this->stdevY * this->getRand(this->stdevY, this->meanY)) + this->meanY;
    }
}
int Pilot::inRadius(){
    int underDistance = 0;
    for(int i = 0; i < trialSize; i++){
        double distance = sqrt(pow(this->normalX[i],2) + pow(this->normalY[i],2));
        if(distance <= this->radius){
            underDistance++;
        }
    }
    return underDistance;
}
void Pilot::test(){
    /*for(int i = 0; i < trialSize; i++){
        std::cout << std::setprecision(7) << this->normalX[i] << ", " 
        << this->normalY[i] << std::endl;
    }*/
    std::cout << "# in radius: " << this->inRadius() << std::endl;
    this->probHitTarget = (this->inRadius() / trialSize);
    std::cout << "Probability of hitting target within radius: "
        << probHitTarget << std::endl;
}
void Pilot::run(){
    this->generateRandPoints();
    this->probHitTarget = (this->inRadius() / trialSize);
    //this->doReplications();
}
void Pilot::operator=(const Pilot& pilotName){
    this->meanX = pilotName.meanX;
    this->meanY = pilotName.meanY;
    this->variance = pilotName.variance;
    this->finalMean = pilotName.finalMean;
    this->stdevX = pilotName.stdevY;
    this->stdevY = pilotName.stdevY;
    this->radius = pilotName.radius;
    this->probHitTarget = pilotName.probHitTarget;
    this->confidenceInterval = pilotName.confidenceInterval;
    this->alpha = pilotName.alpha;
    for(int i = 0; i < trialSize; i++){
        this->normalX[i] = pilotName.normalX[i];
        this->normalY[i] = pilotName.normalY[i];
    }
}
bool Pilot::operator<(const Pilot& pilotName){
    return (this->probHitTarget < pilotName.probHitTarget);
}
bool Pilot::operator>(const Pilot& pilotName){
    return (this->probHitTarget > pilotName.probHitTarget);
}
double Pilot::getTvalue(){
    std::student_t_distribution<double> tDistribution(replications-1);
    this->t = tDistribution(generator);
    return t;
}
double Pilot::getVariance(){
    double total = 0;
    for(int i = 0; i < replications; i++){
        total += pow((this->outcomes[i] - this->finalMean),2);
    }
    return (total / (replications - 1));
}
double Pilot::getFinalMean(){
    double total = 0;
    for(int i = 0; i < replications; i++){
        total += outcomes[i];
    }
    return (total / replications);
}
void Pilot::doReplications(){
    std::cout << "Replication: " << "Outcome: " << "Mean: " << "Confidence Interval: " 
        << "Alpha: " << "   t: " << std::endl;
    for(int i = 1; i <= replications; i++){
        this->run();
        outcomes[i-1] = this->probHitTarget;
        std::cout << std::setw(10) << i << std::setw(10) << outcomes[i-1] 
        << std::setw(6) << this->getFinalMean();
        if (i == 1){
            std::cout << std::setw(21) << confidenceInterval << std::setw(7)
                << alpha << "   " << this->getTvalue();
        }  
        if (i == 3){
            std::cout << std::setw(27) << "Mean is between ";
        } 
        if (i == 4){
            std::cout << std::setw(17) 
                << (this->getFinalMean() - t * sqrt(this->getVariance()/trialSize))
                << "   "
                << (this->getFinalMean() + t * sqrt(this->getVariance()/trialSize));
        }
        std::cout << '\n';
    }
}
