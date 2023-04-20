#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include "qcustomplot.h"
#include <string>
using namespace std;

class SessionData
{
public:
    SessionData();
    friend class Session; //So that session can access the members of this class without needing getters or setters
    float getCoherenceScore();
    float getAchievementScore();
    //getHRVGraph
    int getChallengeLevel();
    float getTimeInLowCoherence();
    float getTimeInMedCoherence();
    float getTimeInHighCoherence();
    float getAvgCoherence();

private:
    float coherenceScore;    
    int sessionLength; //in seconds
    float achievementScore;
    int challengeLevel;
    float timeInLowCoherence;
    float timeInMedCoherence;
    float timeInHighCoherence;
    float avgCoherence;
    QCPDataContainer<QCPGraphData> hrvData;
};

#endif // SESSIONDATA_H
