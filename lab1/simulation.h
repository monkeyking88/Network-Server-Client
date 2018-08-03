#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <unistd.h>
#include "packet.h"
#include "buffer.h"
#include "server.h"
#include "URNG.h"
#include "def.h"

class Simulation{
protected:
    vector<Packet*> allPackets; //vector to store all packets generated
    Buffer* buff;               //the FIFO buffer
    vector<Server*> servers;    //list of servers

public:
    Simulation(int buffer_cap, int server_num);
    ~Simulation();

    void Server_Sim(int t);
    void Arrival (int t);
    void Departure (int t);
    void Start_simulation (int ticks);
    void Compute_Performance ();
};



#endif
