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
        void updateGraph();
        void updateCoherence();
        SessionData getSessionData();
        bool isActive();
    
    private:
        SessionData *sessionData;
        QTimer *hrvTimer;
        QTimer *coherenceTimer;

    signals:
        void timeUpdated(int);
        void graphUpdated(QCPDataContainer<QCPGraphData>);
        void coherenceUpdated(float, float);
};


#endif // SESSION_H
