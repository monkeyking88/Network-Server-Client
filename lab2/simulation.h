#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <unistd.h>
#include "global.h"
#include "packet.h"
#include "node.h"
#include "URNG.h"

using namespace std;
class Node;

class Simulation{
private:
    int T;              // simulation time
    int N;              // number of nodes
    int A;              // average packet arrival rate
    int W;              // the speed of the LAN
    int L;              // packet length
    int P;                // P needs to be multiplied by 100 by user to use int
                        // instead of float

    unsigned long long int counter_success;
    unsigned long long int overall_delay;
    vector<Node*>   nodes;
public:
    Simulation(int T, int N, int A, int W, int L, int P);
    ~Simulation();

    void Start_Simulation ();
    void Update_Simulation(unsigned int ticks);
    void Compute_Performance ();

    int getT(){ return T; }
    int getN(){ return N; }
    int getA(){ return A; }
    int getW(){ return W << 20; }
    int getL(){ return L << 3; }
    int getP(){ return P; }

};

#endif
