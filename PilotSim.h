
void generateRandPoints(double mean, double stdevX, double stdevY);
double getRand(double stdevX, double mean);
const int trialSize = 10000;
struct PilotSim{
    double mean;
    double stdevX;
    double stdevY;
    double normalX[trialSize];
    double normalY[trialSize]; 
};
int inRadius(double radius);