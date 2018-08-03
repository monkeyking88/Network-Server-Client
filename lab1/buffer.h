#ifndef BUFFER_H
#define BUFFER_H

#include <queue>
#include "packet.h"
#include "def.h"

using namespace std;

class Buffer{
private:
    queue<Packet*> buf;
    int capacity;

public:
    Buffer();
    Buffer(int k);
    void push(Packet* p, unsigned int ticks);
    Packet* pop(unsigned int ticks);
    Packet* front_buffer();
    int getSize();
};

#endif
