#ifndef SESSION_H
#define SESSION_H

#include <string>
using namespace std;

class Session
{
public:
    Session();
    float getCoherenceScore();
    float getAchievementScore();
    //getHRVGraph
    string getChallengeLevel();
    float getTimeInLowCoherence();
    float getTimeInMedCoherence();
    float getTimeInHighCoherence();





private:
    float coherenceScore;    int sessionLength; //in ms
    float achievementScore;
    //HRV GRAPH
    string challengeLevel;
    float timeInLowCoherence;
    float timeInMedCoherence;
    float timeInHighCoherence;
    float avgCoherence;
};

#endif // SESSION_H
