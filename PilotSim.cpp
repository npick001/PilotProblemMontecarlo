#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include "PilotSim.h"

    double mean = 0;
    double stdevX = 500.000;
    double stdevY = 250.000;
    const int trialSize = 10000;
    //Step 1: Get normal variates for x and y
    double randX[trialSize], randY[trialSize], normalX[trialSize], normalY[trialSize];
    //insert code for random variates
    
    void generateRandPoints(stdevX, stdevY, randX, randY){
        std::default_random_engine generator; 
        void getRand(double stdevX){
            std::normal_distribution<double> distribution(0, stdevX);
            return;
        };
        for(int i = 0; i <= trialSize; ++i){
            randX[i] = getRand(stdevX);
            randY[i] = getRand(stdevY);
            std::cout << randX[i] << ", " << randY[i] << std::endl;
        }
    }

