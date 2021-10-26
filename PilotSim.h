
const int trialSize = 10000;
const int replications = 50;
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
    double avgDistance;
    double normalX[trialSize];
    double normalY[trialSize];
public:
    double outcomes[replications+2];
    double confidenceInterval;
    double alpha;
    double t;
    Pilot();
    Pilot(const Pilot& pilotName);
    void run();
    void generateRandPoints();
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
    //void test();
    void output();
    void operator=(const Pilot& pilotName);
    bool operator<(const Pilot& pilotName);
    bool operator>(const Pilot& pilotName);
};
