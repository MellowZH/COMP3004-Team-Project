#ifndef SESSION_H
#define SESSION_H

#include <string>
#include "qtimer.h"
#include "sessionData.h"
using namespace std;

class Session: public QObject
{
    Q_OBJECT

    public:
        Session();
        void startSession();
        void stopSession();
        void updateTime();
        SessionData getSessionData();
        bool isActive();
        //QTimer getTimer();
    
    private:
        SessionData *sessionData;
        QTimer *timer;

    signals:
        void timeUpdated(int);
};


#endif // SESSION_H
