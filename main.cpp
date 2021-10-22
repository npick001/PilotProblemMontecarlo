#include "PilotSim.h"
#include <iterator>
#include <algorithm>
#include <iostream>

int main(){
    Pilot nick;
    int testTrials = trialSize;
    nick.generateRandPoints(nick.getMean(), nick.getStdevX(), nick.getStdevY());
    int totalIn = nick.inRadius(nick.getRadius());
    //DO TEST HERE
    double *normalX = nick.getnX();
    double *normalY = nick.getnY();
    for(int i = 0; i < testTrials; i++){
        std::cout << normalX[i] << ", " << normalY[i] << std::endl;
    }
    std::cout << "# in radius: " << totalIn << std::endl;

}
 