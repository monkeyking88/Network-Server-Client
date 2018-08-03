#include "packet.h"

Packet::Packet(unsigned int ticks, int time) {
    time_created    = ticks;
    time_entered    = 0;
    time_left       = 0;
    time_gone       = 0;
	time_deterministic = time;
    state           = Created;
    num_packet      += 1;
}

unsigned int Packet::cal_delay_time () {
    if (state != Serving && state != Gone){
        throw "Invalid state for cal_delay_time";
    }
    return time_left - time_entered;
}

unsigned int Packet::cal_service_time () {
    if (state != Gone){
        throw "Invalid state for cal_service_time";
    }
    return time_gone - time_left;
}

State Packet::getState(){
    return state;
}

void Packet::setState(State s) {
    state = s;
}
void Packet::lose(){
    ++num_loss_packet;
    state = Lost;
}

//called when the packet enters the queue
void Packet::enter(unsigned int ticks){
    state = Waiting;
    time_entered = ticks;
}

//called when packet leaves queue
void Packet::leave(unsigned int ticks){
    state = Serving;
    time_left = ticks;
}

//called when packet is gone
void Packet::go(unsigned int ticks){
    state = Gone;
    time_gone = ticks;
    cum_time += time_gone - time_entered;
}

unsigned long long int Packet::get_num_packet() {
    return num_packet;
}

unsigned long long int Packet::get_cum_time() {
    return cum_time;
}

unsigned long long int Packet::get_num_loss_packet() {
    return num_loss_packet;
}

unsigned int Packet::get_time_deterministic() {
    return time_deterministic;
}

void Packet::decrement_time_deterministic() {
    --time_deterministic;
}
