
const int trialSize = 10000;
//Represents each Pilot we would like to test
class Pilot{
    double mean;
    double stdevX;
    double stdevY;
    double radius;
    double normalX[trialSize];
    double normalY[trialSize];
public:
    Pilot();
    Pilot(Pilot& pilotName);
    void generateRandPoints();
    double getRand(double stdevX, double mean);
    int inRadius();
    double getMean(){return mean;}
    double getStdevX(){return stdevX;}
    double getStdevY(){return stdevY;}
    double getRadius(){return radius;}
    double *getnX(){return normalX;}
    double *getnY(){return normalY;}
    void test();
};
