#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include "PilotSim.h"
const int trialSize = 10000;

//Step 1: Get normal variates for x and y
//insert code for random variates
double getRand(double stdevX, double mean){
    std::default_random_engine generator; 
    std::normal_distribution<double> distribution(mean, stdevX);
    double value = distribution(generator);
    return value;
};
void generateRandPoints(double mean, double stdevX, double stdevY, double normalX[], double normalY[]){
    
    for(int i = 0; i <= trialSize; ++i){
        normalX[i] = getRand(stdevX, mean);
        normalY[i] = getRand(stdevY, mean);
        std::cout << normalX[i] << ", " << normalY[i] << std::endl;
    }
}

