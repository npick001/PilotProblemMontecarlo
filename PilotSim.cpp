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
void Pilot::test(){
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
}
void Pilot::run(){
    this->generateRandPoints();
    this->probHitTarget = static_cast<double>(this->inRadius()) / static_cast<double>(trialSize);
    //this->test();
    this->doReplications();
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
