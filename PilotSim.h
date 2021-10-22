
void generateRandPoints(double mean, double stdevX, double stdevY, double normalX, double normalY);
double getRand(double stdevX, double mean);
struct PilotSim{
    double mean;
    double stdevX;
    double stdevY;
    double normalX[trialSize];
    double normalY[trialSize]; 
};