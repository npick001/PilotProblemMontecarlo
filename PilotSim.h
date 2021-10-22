
void generateRandPoints(PilotSim x, double mean, double stdevX, double stdevY);
double getRand(PilotSim x, double stdevX, double mean);
const int trialSize = 10000;
struct PilotSim{
    double mean;
    double stdevX;
    double stdevY;
    double radius;
    double normalX[trialSize];
    double normalY[trialSize]; 
};
int inRadius(PilotSim x, double radius);