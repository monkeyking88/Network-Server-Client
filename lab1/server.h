#ifndef SERVER_H
#define SERVER_H

#include "packet.h"
#include "def.h"

class Server{
protected:
    Packet* p;
    static unsigned long long int idle_time;

public:
    Server();
    void serve(Packet* p);
    void go(unsigned int ticks);
    static unsigned long long int get_idle_time();
    static void increment_idle_time();
};

#endif
