#include "sessionData.h"

SessionData::SessionData(int challengeLevel){
    this->sessionLength = 0;
    this->challengeLevel = challengeLevel;
    this->coherenceScore = 0;
    this->achievementScore = 0;
    this->avgCoherence = 0;
    this->timeInLowCoherence =0;
    this->timeInMedCoherence = 0;
    this->timeInHighCoherence=0;
}

float SessionData::getCoherenceScore() {
    return this->coherenceScore;
}

int SessionData::getSessionLength(){
    return this->sessionLength;
}

float SessionData::getAchievementScore() {
    return this->achievementScore;
}

int SessionData::getChallengeLevel() {
    return this->challengeLevel;
}

float SessionData::getTimeInLowCoherence() {
    return this->timeInLowCoherence;
}

float SessionData::getTimeInMedCoherence() {
    return this->timeInMedCoherence;
}

float SessionData::getTimeInHighCoherence() {
    return this->timeInHighCoherence;
}

float SessionData::getAvgCoherence() {
    return this->avgCoherence;
}

char *SessionData::getDate(){
    return this->date;
}

QCPDataContainer<QCPGraphData> SessionData::getHrvData(){
    return this->hrvData;
}
