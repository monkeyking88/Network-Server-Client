#include "packet.h"
//#include <iostream>

Packet::Packet(unsigned int ticks, Buffer* buffer) {
    this->time_created  = ticks;
    this->time_transmission_start = 0;
    this->time_gone     = 0;
    this->state         = WAITING;
    this->packet_count  = 0;

    //push the buffer directly into buffer at creation, easier to use
    buffer->push(this);
}

unsigned int Packet::cal_waiting_time () {
    if (state != TRANSIMITTING && state != GONE) {
        throw "Invalid state for cal_waiting_time";
    }
    //if (time_gone - time_created < 0) cout << "negative wait time!!!" << endl;
    return time_gone - time_created;
}


STATE_PACKET Packet::getState() {
    return this->state;
}

//called when packet leaves queue
void Packet::leave(unsigned int ticks) {
    this->state = TRANSIMITTING;
    this->time_transmission_start = ticks;
}

//called when packet transmission finished
void Packet::go(unsigned int ticks) {
    this->state     = GONE;
    this->time_gone = ticks;
    this->packet_count++;
}

unsigned int Packet::get_packet_count() {
    return packet_count;
}

