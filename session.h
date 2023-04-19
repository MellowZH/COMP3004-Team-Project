#ifndef SESSION_H
#define SESSION_H

#include <string>
#include "sessionData.h"
using namespace std;

class Session
{
    public:
        void startSession();
        void stopSession();
        SessionData getSessionData();
    
    private:
        SessionData sessionData;
};


#endif // SESSION_H