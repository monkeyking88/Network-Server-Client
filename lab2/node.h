#ifndef NODE_H
#define NODE_H

#include "global.h"
#include "buffer.h"
#include "packet.h"
#include "simulation.h"
#include "URNG.h"

#define TICKS_PER_SEC 1000

#define LENGTH_SENSING  96
#define LENGTH_JAMING   48

#define LENGTH_TP       512
#define MAX_K           10  //max number of errors before node goes into error state
#define DELAY_PROPAGATION   200000000

using namespace std;
class Simulation;

typedef enum nodeState { IDLE, SENSING, /*TRANSMIT_START,*/ TRANSMITTING, /*JAM_START,*/ JAMMING, BACKOFF, ERROR, RANDOMWAIT } STATE_NODE;

class Node{     //parent class
protected:
    Simulation* sim;
    Buffer buffer;
    vector<Packet*> allPacketsGenerated;    //stores all packets ever generated by this node
    Packet* curPacket;

    STATE_NODE state;
    unsigned int counter_generation;    //this counter is used to count down the time before next pack is generated
    unsigned int counter_transmission;  //this counter is used for transmission, eg sending, sensing, jamming etc
    int error_count;
    unsigned long long int counter_success;
    unsigned long long int overall_delay;

public:
    Node(Simulation* sim);
    ~Node();
    virtual void update(unsigned int ticks) = 0;    //pure virtual so you don't accidentally use parent class =D
    bool tryGenPacket(unsigned int ticks);  //test if next packet should be generated
    STATE_NODE getState();
    vector<Packet*> getAllPackets();
    unsigned long long int get_counter_success();
    unsigned long long int get_overall_delay();
};

//use for persistent CSMA/CD
class PersistentNode : public Node{
public:
    PersistentNode(Simulation* sim);
    virtual void update(unsigned int ticks);
};


//use for non persistent CSMA/CD
class NonPersistentNode : public Node{
public:
    NonPersistentNode(Simulation* sim);
    virtual void update(unsigned int ticks);
};


//use for p-persistent CSMA/CD
class P_PersistentNode : public Node{
private:
    int p;  //although a percentage, floating point is ugly, so please represent with int
    bool useBackoff;
public:
    P_PersistentNode(Simulation* sim, int p);
    virtual void update(unsigned int ticks);
};

#endif