#include "session.h"
#include <winsock.h>
#include<iostream>
#include <random>

Session::Session(int challengeLevel){
    this->hrvTimer = new QTimer(this);
    this->coherenceTimer = new QTimer(this);
    this->sessionData = new SessionData(challengeLevel);
    this->hrvContact = true;
    connect(this->hrvTimer, &QTimer::timeout, this, [this]{this->updateGraph();});
    connect(this->coherenceTimer, &QTimer::timeout, this, [this]{this->updateCoherence();});
}
void Session::startSession() {
    this->hrvTimer->start(1000);
    this->coherenceTimer->start(5000);
    //NEED 64 SECOND TIMER AS WELL FOR COHERENCE SCORE AND LEVEL (LOW MED HIGH)
}

void Session::stopSession() {
    this->hrvTimer->stop();
    this->coherenceTimer->stop();
    time_t now = time(0);
    this->sessionData->date = ctime(&now); //Save session date and time
}

void Session::updateGraph(){ //This function is called every second
    int noiseAmp; //This is to be used to add noise to a normal sin wave to mimic different coherence level graphs
    if(sessionData->coherenceScore == 16){
        noiseAmp = 0;
    }else if(sessionData->coherenceScore >14){
        noiseAmp = 2;
    }else if(sessionData->coherenceScore>10){
        noiseAmp = 4;
    }else if (sessionData->coherenceScore > 8){
        noiseAmp = 6;
    }else if (sessionData->coherenceScore > 6){
        noiseAmp = 8;
    }else if (sessionData->coherenceScore > 4){
        noiseAmp = 10;
    }else if (sessionData->coherenceScore > 3){
        noiseAmp = 15;
    }else if (sessionData->coherenceScore > 2){
        noiseAmp = 20;
    }else if (sessionData->coherenceScore > 1){
        noiseAmp = 25;
    }else if (sessionData->coherenceScore > 0.5){
        noiseAmp = 30;
    }else{
        noiseAmp = 35;
    }

    this->sessionData->sessionLength ++;

    if (this->hrvContact == true){
        //gens some new HR values based on coherence level
        std::mt19937 gen(rand());
        std::uniform_real_distribution<double> noiseDist(-noiseAmp, noiseAmp);
        sessionData->hrvData.add(QCPGraphData(sessionData->sessionLength, 15*sin(2*M_PI*(0.07)*sessionData->sessionLength)+80 + noiseDist(gen))); //heart rate of 65-95 at 0.07hz

        //updates time spent in various coherence levels
        switch (this->sessionData->challengeLevel){
            case 1:
                if(this->sessionData->coherenceScore<0.5){
                    this->sessionData->timeInLowCoherence++;
                }else if(0.5<=this->sessionData->coherenceScore<=0.9){
                    this->sessionData->timeInMedCoherence++;
                }else{
                    this->sessionData->timeInHighCoherence++;
                }
                break;

            case 2:
                if(this->sessionData->coherenceScore<0.6){
                    this->sessionData->timeInLowCoherence++;
                }else if(0.6<=this->sessionData->coherenceScore<=2.1){
                    this->sessionData->timeInMedCoherence++;
                }else{
                    this->sessionData->timeInHighCoherence++;
                }
                break;

            case 3:
                if(this->sessionData->coherenceScore<1.8){
                    this->sessionData->timeInLowCoherence++;
                }else if(1.8<=this->sessionData->coherenceScore<=4.0){
                    this->sessionData->timeInMedCoherence++;
                }else{
                    this->sessionData->timeInHighCoherence++;
                }
                break;

            case 4:
                if(this->sessionData->coherenceScore<4.0){
                    this->sessionData->timeInLowCoherence++;
                }else if(4.0<=this->sessionData->coherenceScore<=6.0){
                    this->sessionData->timeInMedCoherence++;
                }else{
                    this->sessionData->timeInHighCoherence++;
                }
                break;
        }
    }else{ //no hrv contact
        sessionData->hrvData.add(QCPGraphData(sessionData->sessionLength, 0));
    }

    emit timeUpdated(this->sessionData->sessionLength);
    emit graphUpdated(this->sessionData->hrvData);
}

void Session::updateCoherence(){
    if(this->sessionData->coherenceScore < 16){
        this->sessionData->coherenceScore += .25;
    }
    this->sessionData->achievementScore += this->sessionData->coherenceScore;
    emit coherenceUpdated(this->sessionData->coherenceScore, this->sessionData->achievementScore);
}

bool Session::isActive(){
    return this->hrvTimer->isActive();
}

SessionData Session::getSessionData() {
    return *this->sessionData;
}

void Session::setHrvContact(){
    this->hrvContact = !this->hrvContact;
}
