#include "server.h"

Server::Server() {
    p = NULL;
}

void Server::serve(Packet* packet){
    p = packet;
}

void Server::go(unsigned int ticks){
    p->go(ticks);
    p = NULL;
}

unsigned long long int Server::get_idle_time() {
    return idle_time;
}

void Server::increment_idle_time() {
    ++idle_time;
}
