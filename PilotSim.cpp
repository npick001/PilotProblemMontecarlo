#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include "PilotSim.h"

//Step 1: Get normal variates for x and y
//insert code for random variates
Pilot::Pilot(){
    this->mean = 0;
    this->stdevX = 1;
    this->stdevY = 1;
    this->radius = 1;
    this->probHitTarget = 0;
    for (int i = 0; i < trialSize; i++){
        this->normalX[i] = 0;
        this->normalY[i] = 0;
    }
}
Pilot::Pilot(const Pilot& pilotName) {
    this->mean = pilotName.mean;
    this->stdevX = pilotName.stdevX;
    this->stdevY = pilotName.stdevY;
    this->radius = pilotName.radius;
    this->probHitTarget = pilotName.probHitTarget;
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

    // See article above for explanation of this section.
    if (prob < 0.5)
    {
        // F^-1(p) = - G^-1(p)
        return -rationalApprox( sqrt(-2.0*log(prob)) );
    }
    else
    {
        // F^-1(p) = G^-1(1-p)
        return rationalApprox( sqrt(-2.0*log(1-prob)) );
    }
}

std::default_random_engine generator; 
double Pilot::getRand(double stdevX, double mean){
    std::normal_distribution<double> distribution(mean, stdevX);
    double value = distribution(generator);
    return value;
};
void Pilot::generateRandPoints(){
    for(int i = 0; i <= trialSize; ++i){
        this->normalX[i] = this->normalInversePoints(getRand(this->stdevX, this->mean));
        this->normalY[i] = this->normalInversePoints(getRand(this->stdevY, this->mean));
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
    for(int i = 0; i < trialSize; i++){
        std::cout << this->normalX[i] << ", " << this->normalY[i] << std::endl;
    }
    std::cout << "# in radius: " << this->inRadius() << std::endl;
}
void Pilot::run(){
    this->generateRandPoints();
    this->test();
}
bool Pilot::operator=(const Pilot& pilotName){
    this->mean = pilotName.mean;
    this->stdevX = pilotName.stdevY;
    this->stdevY = pilotName.stdevY;
    this->radius = pilotName.radius;
    this->probHitTarget = pilotName.probHitTarget;
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
