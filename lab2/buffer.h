#ifndef BUFFER_H
#define BUFFER_H

#include <queue>
#include "packet.h"

using namespace std;

class Packet;

class Buffer{
private:
    queue<Packet*> buf;

public:
    Buffer();

    void push(Packet* p);
    Packet* pop(unsigned int ticks);
    Packet* front();

    int size();
};

#endif
