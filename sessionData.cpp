#include "sessionData.h"

float SessionData::getCoherenceScore() {
    return this->coherenceScore;
}

float SessionData::getAchievementScore() {
    return this->achievementScore;
}

string SessionData::getChallengeLevel() {
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
