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
        Session(int);
        void startSession();
        void stopSession();
        void updateGraph();
        void updateCoherence();
        SessionData getSessionData();
        bool isActive();
        void setHrvContact();
    
    private:
        bool hrvContact;
        SessionData *sessionData;
        QTimer *hrvTimer;
        QTimer *coherenceTimer;

    signals:
        void timeUpdated(int);
        void graphUpdated(QCPDataContainer<QCPGraphData>);
        void coherenceUpdated(float, float);
        void coherenceLevelUpdated(int);
};


#endif // SESSION_H
