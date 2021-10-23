
const int trialSize = 10000;
//Represents each Pilot we would like to test
class Pilot{
    double mean;
    double stdevX;
    double stdevY;
    double radius;
    double probHitTarget;
    double normalX[trialSize];
    double normalY[trialSize];
public:
    Pilot();
    Pilot(const Pilot& pilotName);
    void run();
    void generateRandPoints();
    double rationalApprox(double t);
    double normalInversePoints(double prob);
    double getRand(double stdevX, double mean);
    int inRadius();
    double getMean(){return mean;}
    double getStdevX(){return stdevX;}
    double getStdevY(){return stdevY;}
    double getRadius(){return radius;}
    double getProbHitTarget(){return probHitTarget;}
    double *getnX(){return normalX;}
    double *getnY(){return normalY;}
    void test();
    bool operator=(const Pilot& pilotName);
    bool operator<(const Pilot& pilotName);
    bool operator>(const Pilot& pilotName);
};
