
const int trialSize = 10000;
const int replications = 15;
//Represents each Pilot we would like to test
class Pilot{
    double meanX;
    double meanY;
    double variance;
    double finalMean;
    double stdevX;
    double stdevY;
    double radius;
    double probHitTarget;
    double normalX[trialSize];
    double normalY[trialSize];
public:
    double outcomes[replications];
    double confidenceInterval;
    double alpha;
    double t;
    Pilot();
    Pilot(const Pilot& pilotName);
    void run();
    void generateRandPoints();
    double rationalApprox(double x);
    double normalInversePoints(double prob);
    double getRand(double stdev, double mean);
    double getTvalue();
    double getVariance();
    double getFinalMean();
    int inRadius();
    void doReplications();
    double getVar(){return variance;}
    double getMeanX(){return meanX;}
    double getMeanY(){return meanY;}
    double getStdevX(){return stdevX;}
    double getStdevY(){return stdevY;}
    double getRadius(){return radius;}
    double getProbHitTarget(){return probHitTarget;}
    double *getnX(){return normalX;}
    double *getnY(){return normalY;}
    void test();
    void operator=(const Pilot& pilotName);
    bool operator<(const Pilot& pilotName);
    void operator<<(const Pilot& pilotName);
    bool operator>(const Pilot& pilotName);
    void operator>>(const Pilot& pilotName);
};
