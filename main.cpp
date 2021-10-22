#include "PilotSim.h"
#include <iterator>
#include <algorithm>
#include <iostream>

int main(){
    PilotSim x;
    x.mean = 0;
    x.stdevX = 300;
    x.stdevY = 150;
    x.radius = 125;
    int testTrials = trialSize;
    generateRandPoints(x, x.mean, x.stdevX, x.stdevY);
    int totalIn = inRadius(x, x.radius);
    //DO TEST HERE
    
    for(int i = 0; i < testTrials; i++){
        std::cout << x.normalX[i] << ", " << x.normalY[i] << std::endl;
    }
    std::cout << "# in radius: " << totalIn << std::endl;

}
 