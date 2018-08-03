#ifndef PACKET_H
#define PACKET_H

#include <vector>
#include "buffer.h"

using namespace std;
class Buffer;

typedef enum packetState { WAITING, TRANSIMITTING, GONE } STATE_PACKET;

class Packet{
private:
    Packet();

protected:
    unsigned long long int time_created;
    unsigned long long int time_transmission_start;
    unsigned long long int time_gone;
    unsigned long long int packet_count;
    STATE_PACKET state;

public:
    Packet(unsigned int ticks, Buffer* buffer);
    unsigned int cal_waiting_time();    //this returns the amount of time spent waiting to be served in the queue

    STATE_PACKET getState();

    void leave(unsigned int ticks);
    void go(unsigned int ticks);
    unsigned int get_packet_count();
};


#endif
