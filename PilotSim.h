
void generateRandPoints(double stdevX, double stdevY, double randX, double randY);
double getRand(double stdevX);
struct PilotSim{
    double mean = 0;
    double stdevX = 500.000;
    double stdevY = 250.000;
    double randX[trialSize];
    double randY[trialSize]; 
    double normalX[trialSize]; 
    double normalY[trialSize];
};