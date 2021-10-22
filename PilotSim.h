
const int trialSize = 10000;
class Pilot{
    double mean;
    double stdevX;
    double stdevY;
    double radius;
    double normalX[trialSize];
    double normalY[trialSize];
public:
    void generateRandPoints(double mean, double stdevX, double stdevY);
    double getRand(double stdevX, double mean);
    int inRadius(double radius);
    double getMean(){return mean;}
    double getStdevX(){return stdevX;}
    double getStdevY(){return stdevY;}
    double getRadius(){return radius;}
    double *getnX(){return normalX;}
    double *getnY(){return normalY;}
};
