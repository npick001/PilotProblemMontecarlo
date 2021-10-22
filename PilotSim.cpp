#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include "PilotSim.h"
const int trialSize = 10000;

//Step 1: Get normal variates for x and y
//insert code for random variates
double getRand(double stdevX){
    std::default_random_engine generator; 
    std::normal_distribution<double> distribution(0, stdevX);
    double value = distribution(generator);
    return value;
};
void generateRandPoints(double stdevX, double stdevY, double randX[], double randY[]){
    
    for(int i = 0; i <= trialSize; ++i){
        randX[i] = getRand(stdevX);
        randY[i] = getRand(stdevY);
        std::cout << randX[i] << ", " << randY[i] << std::endl;
    }
}

