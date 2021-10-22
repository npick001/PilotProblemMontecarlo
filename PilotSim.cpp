#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include "PilotSim.h"

//Step 1: Get normal variates for x and y
//insert code for random variates
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