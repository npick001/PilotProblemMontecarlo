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
    for (int i = 0; i < trialSize; i++){
        this->normalX[i] = 0;
        this->normalY[i] = 0;
    }
}
Pilot::Pilot(Pilot& pilotName) {
    this->mean = pilotName.getMean();
    this->stdevX = pilotName.getStdevX();
    this->stdevY = pilotName.getStdevY();
    this->radius = pilotName.getRadius();
}
std::default_random_engine generator; 
double Pilot::getRand(double stdevX, double mean){
    std::normal_distribution<double> distribution(mean, stdevX);
    double value = distribution(generator);
    return value;
};
void Pilot::generateRandPoints(){
    for(int i = 0; i <= trialSize; ++i){
        this->normalX[i] = this->getRand(this->stdevX, this->mean);
        this->normalY[i] = this->getRand(this->stdevY, this->mean);
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