#ifndef PACKET_H
#define PACKET_H

#include "def.h"

enum State { Created, Lost, Waiting, Serving, Gone };

class Packet{
private:
    Packet();

protected:
    unsigned int time_created;
    unsigned int time_entered;
    unsigned int time_left;
    unsigned int time_gone;
    unsigned int time_deterministic;
    State state;
    static unsigned long long int num_packet;
    static unsigned long long int cum_time;
    static unsigned long long int num_loss_packet;

public:
    Packet(unsigned int ticks, int time);
    unsigned int cal_delay_time();
    unsigned int cal_service_time();

    State getState();
    void setState(State s);

    void lose();
    void enter(unsigned int ticks);
    void leave(unsigned int ticks);
    void go(unsigned int ticks);
    static unsigned long long int get_num_packet();
    static unsigned long long int get_cum_time();
    static unsigned long long int get_num_loss_packet();
    unsigned int get_time_deterministic();
    void decrement_time_deterministic();
};


#endif
