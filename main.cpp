#include "PilotSim.h"
#include <iterator>
#include <algorithm>
#include <iostream>

int main(){
    double mean = 0;
    double stdevX = 300;
    double stdevY = 150;
    double radius = 125;
    int testTrials = trialSize;
    generateRandPoints(mean, stdevX, stdevY);
    int totalIn = inRadius(radius);
    //DO TEST HERE
    PilotSim x;
    for(int i = 0; i < testTrials; i++){
        std::cout << x.normalX[i] << ", " << x.normalY[i] << std::endl;
    }
    std::cout << "# in radius: " << totalIn << std::endl;

}
 