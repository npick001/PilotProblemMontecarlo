#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include "PilotSim.h"

//Step 1: Get normal variates for x and y
//insert code for random variates
double getRand(double stdevX, double mean){
    std::default_random_engine generator; 
    std::normal_distribution<double> distribution(mean, stdevX);
    double value = distribution(generator);
    return value;
};
void generateRandPoints(double mean, double stdevX, double stdevY){
    PilotSim x;
    for(int i = 0; i <= trialSize; ++i){
        x.normalX[i] = getRand(stdevX, mean);
        x.normalY[i] = getRand(stdevY, mean);
        std::cout << x.normalX[i] << ", " << x.normalY[i] << std::endl;
    }
}

