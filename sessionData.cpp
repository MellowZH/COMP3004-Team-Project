#include "sessionData.h"

SessionData::SessionData(){
    this->sessionLength = 0;
    this->challengeLevel = 1;
    this->coherenceScore = 0;
    this->achievementScore = 0;
}

float SessionData::getCoherenceScore() {
    return this->coherenceScore;
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
