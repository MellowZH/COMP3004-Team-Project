#ifndef SESSIONDATA_H
#define SESSIONDATA_H

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
    string getChallengeLevel();
    float getTimeInLowCoherence();
    float getTimeInMedCoherence();
    float getTimeInHighCoherence();
    float getAvgCoherence();

private:
    float coherenceScore;    
    int sessionLength; //in ms
    float achievementScore;
    //HRV GRAPH
    string challengeLevel;
    float timeInLowCoherence;
    float timeInMedCoherence;
    float timeInHighCoherence;
    float avgCoherence;
};

#endif // SESSIONDATA_H
