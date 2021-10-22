#include "PilotSim.h"
#include <iterator>
#include <algorithm>

int main(){
    double mean = 0;
    double stdevX = 300;
    double stdevY = 150;
    double radius = 125;
    generateRandPoints(mean, stdevX, stdevY);
    inRadius(radius);


}
 