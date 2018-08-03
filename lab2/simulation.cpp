#include <iostream>
#include <string>
#include <stdio.h>
#include <iomanip>
#include "simulation.h"
#include <math.h>
#include "unistd.h"

#define SCRIPTING_MODE false

using namespace std;

Simulation::Simulation(int T, int N, int A, int W, int L, int P) : T(T), N(N), A(A), W(W), L(L), P(P), counter_success(0), overall_delay(0) {}

Simulation::~Simulation() {
    for (int n = 0; n < N; ++n) {
        if (nodes[n] != NULL) {
            delete nodes.at(n);
        }
    }
}

void Simulation::Start_Simulation() {
    // empty
    for (int n = 0; n < N; ++n) {
        //TODO assunming persistent only
        nodes.push_back(new PersistentNode(this));
        //nodes.push_back(new NonPersistentNode(this));
        //nodes.push_back(new P_PersistentNode(this, P));
    }
    for (int t = 0; t < T * TICKS_PER_SEC; ++t) {
        Update_Simulation(t);
    }
    for (int n = 0; n < N; ++n) {
        counter_success += nodes.at(n)->get_counter_success();
        overall_delay += nodes.at(n)->get_overall_delay();
    }
};

void Simulation::Update_Simulation(unsigned int ticks) {
    for (int n = 0; n < N; ++n) {
        nodes.at(n)->update(ticks);
    }
};

void Simulation::Compute_Performance() {
    // Before calculating we need to have:
    // 1. a counter of successfully transmitted packets
    // 2. a counter of total delay time
    // 3. length of transmission (T)

    if (SCRIPTING_MODE) { // fetch csv-like format
        cout << N << ",";
        cout << A << ",,";
        cout << (double)counter_success / T << ",";
        cout << (double)overall_delay / counter_success << endl;
    }
    else {
        // Real things starts from here:
        // 1. Calculate the throughput
        // (total # of successfully transmitted packets)/(length of transmission)
        cout << "Throughput: " << (double)counter_success / T << endl;

        // 2. Calculate the average delay
        // (total delay time of all packets) / (total # of successfully transmitted
        // packets)
        cout << "Average delay: " << (double)overall_delay / counter_success << endl;

    }

};

int main () {
    int T, N, A, W, L, P;

    if (!SCRIPTING_MODE) {
        cout << "Enter T, simulation time: " << endl;
    }
    cin >> T;

    if (!SCRIPTING_MODE) {
        cout << "Enter N, number of nodes: " << endl;
    }
    cin >> N;

    if (!SCRIPTING_MODE) {
        cout << "Enter A, average packet arrival rate: " << endl;
    }
    cin >> A;

    if (!SCRIPTING_MODE) {
        cout << "Enter W, speed of the LAN: " << endl;
    }
    cin >> W;

    if (!SCRIPTING_MODE) {
        cout << "Enter L, packet length: " << endl;
    }
    cin >> L;

    if (!SCRIPTING_MODE) {
        cout << "Enter P, P-persistent: " << endl;
    }
    cin >> P;

    urng.seed(getpid());
    Simulation sim(T, N, A, W, L, P);

    // initial each nodes
    sim.Start_Simulation();
    sim.Compute_Performance();

    return 0;
}

