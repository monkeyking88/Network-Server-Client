#include <iostream>
#include <string>
#include <stdio.h>
#include <iomanip>
#include "simulation.h"
#include "URNG.h"

using namespace std;

int N = 0;    //simulation length in the number of ticks
int L = 0;    //length of packs
int C = 0;    //transimission rate of the output link
int K = 0;    //buffer size

bool CSV = false;

unsigned long long int cum_buff_size = 0;
unsigned long long int Packet::num_packet = 0;
unsigned long long int Packet::cum_time = 0;
unsigned long long int Packet::num_loss_packet = 0;
unsigned long long int Server::idle_time = 0;

URNG urng;

Simulation::Simulation(int buffer_cap, int server_num){
    if (buffer_cap >= 0){
        buff = new Buffer(buffer_cap);
    }
    else{
        buff = new Buffer();
    }

    for (int i = 0; i < server_num; i++) {
        servers.push_back(new Server());
    }
}

Simulation::~Simulation(){
    delete buff;
    for (int i = 0; i < (int)servers.size(); i++) {
        delete servers.at(i);
    }
    for (int i = 0; i < (int)allPackets.size(); i++){
        delete allPackets.at(i);
    }
}

void Simulation::Start_simulation (int ticks) {
	int nextPacket = 1;
	int t = 1;
	int buf_size;
    for (t = 1; t <= ticks; t++) {
		if(nextPacket == t){
			nextPacket = int(urng()) + t;
			Arrival(t);
		}
        Server_Sim(t);
        buf_size = buff->getSize();
        if (buf_size == 0) {
            Server::increment_idle_time();
        }
        else {
            cum_buff_size += buf_size;
        }
    }
}

/*
	If the buffer is full then the packet is now lost
	This logic is done in the buffer push
*/
void Simulation::Arrival (int ticks) {
	Packet* newPacket = new Packet(ticks, L/C);
	buff->push(newPacket, ticks);
}
/*
	First look if there is a packet to be serviced
	If there is set it to serving (if it is serving then it is still serving)
	Decrease its serving time by 1 since a tick has gone by
	If it is now at 0 you want to stop serving the packet and call Departure
*/
void Simulation::Server_Sim (int t) {
	Packet* p = buff->front_buffer();
	Server* serverp = new Server();

	if(p == NULL){
		return;
	}

	p->setState(Serving);

	p->decrement_time_deterministic();

	if(p->get_time_deterministic() == 0){
		serverp->serve(p);
		serverp->go(t);

		Departure(t);
	}

}
/*
	remove head from buffer since its done serving
	old packet is now the new head by simply poping the top
	update the values are done in buffer and its status
*/
void Simulation::Departure (int t) {
	buff->pop(t);
}

void Simulation::Compute_Performance () {
    long double E_N = (long double)(cum_buff_size) / N;
    long double E_T = (long double)(Packet::get_cum_time()) / Packet::get_num_packet();
    long double P_IDLE = (long double)(Server::get_idle_time()) / N;
    long double P_LOSS = (long double)(Packet::get_num_loss_packet()) / Packet::get_num_packet();
    if (CSV) {
        cout << setprecision( 10 ) << fixed << E_N << "," << E_T << "," << P_IDLE << "," << P_LOSS << endl;
    }
    else {
        cout << "E[N] = " << setprecision( 10 ) << fixed << E_N << endl;
        cout << "E[T] = " << setprecision( 10 ) << fixed << E_T << endl;
        cout << "P_IDLE = " << setprecision( 10 ) << fixed << P_IDLE << endl;
        cout << "P_LOSS = " << setprecision( 10 ) << fixed << P_LOSS << endl;
    }
}



void TestPacket(){
    int ticks;
    //demonstraction on packet class
    ticks = 100;
    Packet* packet = new Packet(ticks, L/C);
    cout << "state 0? :" << packet->getState() << endl;
    packet->enter(ticks + 1);
    cout << "state 2? :" << packet->getState() << endl;
    packet->leave(ticks + 10);
    cout << "state 3? :" << packet->getState() << endl;
    packet->go(ticks + 100);
    cout << "state 4? :" << packet->getState() << endl;

    cout << "waiting time: 9? " << packet->cal_delay_time() << endl;
    cout << "service time: 90? " << packet->cal_service_time() << endl;
    packet->lose();
    cout << "state 1? :" << packet->getState() << endl;
    delete packet;

    cout << "Packet works!" << endl;
}

void TestBuffer(){
    int ticks = 100;
    Buffer* buff = new Buffer(3);

    Packet* packet_1 = new Packet(ticks, L/C);
    Packet* packet_2 = new Packet(ticks, L/C);
    Packet* packet_3 = new Packet(ticks, L/C);
    Packet* packet_4 = new Packet(ticks, L/C);
    Packet* packet_5 = new Packet(ticks, L/C);

    ticks += 100;
    buff->push(packet_1, ticks);
    buff->push(packet_2, ticks);
    buff->push(packet_3, ticks);
    buff->push(packet_4, ticks);

    if (packet_1->getState() != Waiting){
        throw "Incorrect Packet State at Push";
    }
    if (packet_2->getState() != Waiting){
        throw "Incorrect Packet State at Push";
    }
    if (packet_3->getState() != Waiting){
        throw "Incorrect Packet State at Push";
    }

    if (packet_4->getState() != Lost){
        throw "Incorrect Packet State at Push";
    }

    ticks += 111;

    if (buff->pop(ticks) != packet_1 ){
        throw "Incorrect Packet State at Pop";
    }
    if (buff->pop(ticks) != packet_2 ){
        throw "Incorrect Packet State at Pop";
    }
    if (buff->pop(ticks) != packet_3 ){
        throw "Incorrect Packet State at Pop";
    }
    if (buff->pop(ticks) != NULL ){
        throw "Incorrect Packet State at Pop";
    }

    if (packet_1->getState() != Serving || packet_1->cal_delay_time() != 111){
        throw "Incorrect Packet State";
    }

    buff->push(packet_5, ticks);
    if (packet_5->getState() != Waiting){
        throw "Incorrect Packet State at Push";
    }

    delete packet_1;
    delete packet_2;
    delete packet_3;
    delete packet_4;
    buff->pop(ticks);
    delete packet_5;
    delete buff;

    cout << "Buffer works!" << endl;
}

void TestServer(){
    int ticks = 1000;
    Buffer* buff = new Buffer();
    Packet* packet_1 = new Packet(ticks, L/C);
    Packet* packet_2 = new Packet(ticks, L/C);
    Server* server = new Server();

    buff->push(packet_1, ticks);
    buff->push(packet_2, ticks);

    ticks += 2000;

    server->serve(buff->pop(ticks));
    ticks += 1;
    server->go(ticks);

    ticks+= 1;
    server->serve(buff->pop(ticks));
    ticks += 5;
    server->go(ticks);

    if (packet_1->getState() != Gone || packet_1->cal_delay_time() != 2000 || packet_1->cal_service_time() != 1) {
        throw "Packet 1 failed at server";
    }
    if (packet_2->getState() != Gone || packet_2->cal_delay_time() != 2002 || packet_2->cal_service_time() != 5) {
        throw "Packet 2 failed at server";
    }

    delete packet_1;
    delete packet_2;
    delete buff;
    delete server;

    cout << "Server works!" << endl;
}

void TestSimulation(){
    Simulation* sim = new Simulation(-1, 10);
    delete sim;
    cout << "Simulation works!" << endl;
}

int main () {
    if (!CSV) {
        cout << "Enter thy n: ";
    }
    cin >> N;
    if (!CSV) {
        cout << endl << "Enter thy lambda: ";
    }
    cin >> LAMBDA;
    if (!CSV) {
        cout << endl << "Enter thy L: ";
    }
    cin >> L;
    if (!CSV) {
        cout << endl << "Enter thy C: ";
    }
    cin >> C;
    if (!CSV) {
        cout << endl << "Enter thy K (-1 means M/D/1): ";
    }
    cin >> K;
    cout << endl;

    int server_num = 1;

    urng.seed(getpid());
    Simulation sim(K, server_num);

    sim.Start_simulation (N);
    sim.Compute_Performance();

    //TestPacket();
    //TestBuffer();
    //TestServer();
    //TestSimulation();

    return 0;
}

