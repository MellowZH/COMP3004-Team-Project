#include "session.h"

void Session::startSession() {
    this->sessionData.achievementScore =5;
}

void Session::stopSession() {
    
}

SessionData Session::getSessionData() {
    return this->sessionData;
}
