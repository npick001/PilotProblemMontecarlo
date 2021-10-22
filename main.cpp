#include "PilotSim.h"

int main(){

    PilotSim x;
    double normalX = x.normalX;
    double normalY = x.normalY;
    double mean = 0;
    double stdevX = 300;
    double stdevY = 150;
    generateRandPoints(mean, stdevX, stdevY, normalX, normalY);



}
 