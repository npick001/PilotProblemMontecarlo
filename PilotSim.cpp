#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <iomanip>
#include <cmath>
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
        this->normalX[i] = this->getRand(this->stdevX, this->meanX);
        this->normalY[i] = this->getRand(this->stdevY, this->meanY);
    }
}
int Pilot::inRadius(){
    int underDistance = 0;
    double distance[trialSize];
    for(int i = 0; i < trialSize; i++){
        distance[i] = sqrt(pow(this->normalX[i],2) + pow(this->normalY[i],2));
        if(distance[i] <= this->radius){
            underDistance++;
        }
        this->avgDistance += distance[i];
    }
    this->avgDistance /= trialSize;
    return underDistance;
}
/*void Pilot::test(){
    for(int i = 0; i < trialSize; i++){
        std::cout << std::setprecision(7) << this->normalX[i] << ", " 
        << this->normalY[i] << std::endl;
    }
    std::cout << "# in radius: " << this->inRadius() << std::endl;
    int inRad = this->inRadius();
    this->probHitTarget = static_cast<double>(inRad) / static_cast<double>(trialSize);
    std::cout << "Average Distance: " << this->avgDistance << '\n';
    std::cout << "Probability of hitting target within radius: "
        << this->probHitTarget << '\n';
}*/
void Pilot::run(){
    this->generateRandPoints();
    this->probHitTarget = static_cast<double>(this->inRadius()) / static_cast<double>(trialSize);
    //this->test();
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
    for(int i = 1; i < replications; i++){
        total += pow((this->outcomes[i] - this->finalMean),2);
    }
    return (total / static_cast<double> (replications - 3));
}
double Pilot::getFinalMean(){
    double total = 0;
    for(int i = 1; i < replications; i++){
        total = total + outcomes[i];
    }
    return (total / static_cast<double> (replications-2));
}
void Pilot::output(){
    for(int i = 1; i < replications; i++){
        std::cout << std::setw(12) << i << std::setw(8) << outcomes[i] << '\n';
    }
    this->finalMean = this->getFinalMean();
    double variance = this->getVariance();
    this->t = this->getTvalue();
    double lowerCI = finalMean - t * sqrt(this->getVariance()/static_cast<double> (trialSize));
    double upperCI = finalMean + t * sqrt(this->getVariance()/static_cast<double> (trialSize));
    if (lowerCI >= upperCI){
        double temp = lowerCI;
        lowerCI = upperCI;
        upperCI = temp;
    }
    std::cout << "Mean: " << finalMean << '\n' << "Variance: " << variance << '\n' << "Confidence Interval: " << confidenceInterval 
            << '\n' << "Alpha: " << alpha << '\n' << "t: " << t << '\n' << "With a " << (confidenceInterval * 100) << "% Confidence Interval, " << '\n'
            << "the probability of the pilot " << '\n' << "hitting the target is in the interval: " << lowerCI << " < x < " << upperCI << '\n';
    std::cout << '\n';
}
void Pilot::doReplications(){
    std::cout << "Replication: " << "Outcome: " << '\n';
    for(int i = 0; i < replications; i++){
        this->run();
        this->outcomes[i] = this->probHitTarget;
        if (outcomes[i] > 1){
            std::cout << "Output " << i << " is not below 1.";
            break;
        }
    }
    this->output();
}