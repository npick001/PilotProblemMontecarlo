#include "PilotSim.h"
#include <iterator>
#include <algorithm>
#include <iostream>

int main(){
    Pilot nick;
    int testTrials = trialSize;
    nick.generateRandPoints(nick.getMean(), nick.getStdevX(), nick.getStdevY());
    nick.test();
}
 