#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include "PilotSim.h"

//Step 1: Get normal variates for x and y
//insert code for random variates
std::default_random_engine generator; 
double getRand(double stdevX, double mean){
    std::normal_distribution<double> distribution(mean, stdevX);
    double value = distribution(generator);
    return value;
};
void generateRandPoints(double mean, double stdevX, double stdevY){
    PilotSim x;
    for(int i = 0; i <= trialSize; ++i){
        x.normalX[i] = getRand(stdevX, mean);
        x.normalY[i] = getRand(stdevY, mean);
    }
}
int inRadius(double radius){
    PilotSim x;
    int underDistance = 0;
    for(int i = 0; i < trialSize; i++){
        double distance = sqrt(pow(x.normalX[i],2) + pow(x.normalY[i],2));
        if(distance <= radius){
            underDistance++;
        }
    }
    return underDistance;
}
