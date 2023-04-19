#include "session.h"
#include <winsock.h>

Session::Session(){
    this->timer = new QTimer(this);
    this->sessionData = new SessionData();
    connect(this->timer, &QTimer::timeout, this, [this]{this->updateTime();});
}
void Session::startSession() {
    this->timer->start(1000);
}

void Session::stopSession() {
    this->timer->stop();
}

void Session::updateTime(){
    this->sessionData->sessionLength ++;
    if (this->sessionData->challengeLevel == "low"){
        this->sessionData->timeInLowCoherence++;
    }else if(this->sessionData->challengeLevel == "med"){
        this->sessionData->timeInMedCoherence++;
    }else if(this->sessionData->challengeLevel == "high"){
        this->sessionData->timeInHighCoherence++;
    }

    emit timeUpdated(this->sessionData->sessionLength);
}

bool Session::isActive(){
    return this->timer->isActive();
}

SessionData Session::getSessionData() {
    return *this->sessionData;
}
