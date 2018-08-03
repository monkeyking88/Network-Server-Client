#include <math.h>
#include <iostream>
#include "node.h"
//#include <iostream>

using namespace std;
Node::Node(Simulation* sim) {
    this->sim                   = sim;
    this->curPacket             = NULL;
    this->state                 = IDLE;
    this->counter_generation    = urng.poissonGen(TICKS_PER_SEC/sim->getA());
    this->counter_transmission  = 0;
    this->error_count           = 0;
    this->counter_success       = 0;
    this->overall_delay         = 0;
}

//destructor is called in inverse-inheritance oder, this destructor will be auto-called at end of child class destruction
Node::~Node() {
    //delete all packets ever generated by this node
    for (unsigned int i = 0; i < allPacketsGenerated.size(); i++) {
        delete allPacketsGenerated[i];
    }
}

bool Node::tryGenPacket(unsigned int ticks) {
    if (counter_generation-- <= 0) {    //post decrement
        Packet* newPacket = new Packet(ticks, &buffer);
        allPacketsGenerated.push_back(newPacket);
        counter_generation = urng.poissonGen(TICKS_PER_SEC/sim->getA());
        return true;
    }
    return false;
}

STATE_NODE Node::getState() {
    return state;
}

vector<Packet*> Node::getAllPackets() {
    return allPacketsGenerated;
}

//some useless constructors left here so implementation can be filled in quickly if needed
PersistentNode::PersistentNode(Simulation* sim) : Node(sim) {}
NonPersistentNode::NonPersistentNode(Simulation* sim) : Node(sim) {}
P_PersistentNode::P_PersistentNode(Simulation* sim, int p) : Node(sim), p(p), useBackoff(false) {}

void PersistentNode::update(unsigned int ticks) {
    tryGenPacket(ticks);    //try to generate packet, this is independent

    /*For each tick, see if the node can reach into the next state.*/
    switch(state) {
        case IDLE: {
            curPacket = buffer.pop(ticks);
            if (curPacket != NULL) {
                state = SENSING;
                counter_transmission = LENGTH_SENSING;
            }
            break;
        }
        case SENSING: {
            if (Medium_Sense() != MEDIAN_IDLE) {
                counter_transmission = LENGTH_SENSING;
            }
            else if (counter_transmission-- <= 0) {
                state = TRANSMITTING;    //this state is used to detect collision
                if (sim->getW() != 0) {
                    counter_transmission = TICKS_PER_SEC*sim->getL()/sim->getW();
                } else {
                    counter_transmission = 0;
                }
                busyCounter++;
            }
            break;
        }
        case TRANSMITTING: {
            if (Medium_Sense() == MEDIAN_COLLISION) {
                state = JAMMING;
                busyCounter++;
                counter_transmission = LENGTH_JAMING;
            }
            else if (counter_transmission-- <= 0) {
                //packet transmission finished
                state = IDLE;
                curPacket->go(ticks);
                counter_success += curPacket->get_packet_count();
                overall_delay += curPacket->cal_waiting_time();
                busyCounter--;
            }
            break;
        }
        case JAMMING: {
            if (counter_transmission-- <= 0) {
                state = BACKOFF;
                counter_transmission = urng((unsigned int)pow(2, error_count)-1) * LENGTH_TP * TICKS_PER_SEC / sim->getW();
                busyCounter -= 2;
                error_count++;
                if (error_count >= MAX_K) {
                    state = ERROR;
                }
            }
            break;
        }
        case BACKOFF: {
            if (counter_transmission-- <= 0) {
                state = SENSING;
                counter_transmission = LENGTH_SENSING;
            }
            break;
        }
        case ERROR: {
            return;     //node is error status, nothing we can do
        }
        default: {
            throw "PersistentNode::update undefined state";
        }
    }
}

void NonPersistentNode::update(unsigned int ticks) {
    tryGenPacket(ticks);    //try to generate packet, this is independent

    /*For each tick, see if the node can reach into the next state.*/
    switch(state) {
        case IDLE: {
            curPacket = buffer.pop(ticks);
            if (curPacket != NULL) {
                state = SENSING;
                counter_transmission = LENGTH_SENSING;
            }
            break;
        }
        case RANDOMWAIT: {
            if (counter_transmission-- <= 0) {
                state = SENSING;
                counter_transmission = LENGTH_SENSING;
                waitingCounter--;
                if (waitingCounter < 1) {
                    waitingCounter = 1;
                }
            }
            break;
        }
        case SENSING: {
            if (Medium_Sense() != MEDIAN_IDLE) {
                state = RANDOMWAIT;
                counter_transmission = urng((unsigned int)pow(2, waitingCounter)-1) * LENGTH_TP * TICKS_PER_SEC / sim->getW();
                waitingCounter++;
            }
            else if (counter_transmission-- <= 0) {
                state = TRANSMITTING;    //this state is used to detect collision
                if (sim->getW() != 0) {
                    counter_transmission = TICKS_PER_SEC*sim->getL()/sim->getW();
                } else {
                    counter_transmission = 0;
                }
                busyCounter++;
            }
            break;
        }
        case TRANSMITTING: {
            if (Medium_Sense() == MEDIAN_COLLISION) {
                state = JAMMING;
                busyCounter++;
                counter_transmission = LENGTH_JAMING;
            }
            else if (counter_transmission-- <= 0) {
                //packet transmission finished
                state = IDLE;
                curPacket->go(ticks);
                counter_success += curPacket->get_packet_count();
                overall_delay += curPacket->cal_waiting_time();
                busyCounter--;

            }
            break;
        }
        case JAMMING: {
            if (counter_transmission-- <= 0) {
                state = BACKOFF;
                counter_transmission = urng((unsigned int)pow(2, error_count)-1) * LENGTH_TP * TICKS_PER_SEC / sim->getW();
                busyCounter -= 2;
                error_count++;
                if (error_count >= MAX_K) {
                    state = ERROR;
                }
            }
            break;
        }
        case BACKOFF: {
            if (counter_transmission-- <= 0) {
                state = SENSING;
                counter_transmission = LENGTH_SENSING;
            }
            break;
        }
        case ERROR: {
            return;     //node is error status, nothing we can do
        }
        default: {
            throw "NonPersistentNode::update undefined state";
        }
    }
}

void P_PersistentNode::update(unsigned int ticks) {
    tryGenPacket(ticks);    //try to generate packet, this is independent

    /*For each tick, see if the node can reach into the next state.*/
    switch(state) {
        case IDLE: {
            curPacket = buffer.pop(ticks);
            if (curPacket != NULL) {
                state = SENSING;
                counter_transmission = LENGTH_SENSING;
            }
            break;
        }
        case RANDOMWAIT: {
            if (counter_transmission-- <= 0) {
                state = SENSING;
                counter_transmission = LENGTH_SENSING;
                waitingCounter--;
                if (waitingCounter < 1) {
                    waitingCounter = 1;
                }
            }
            break;
        }
        case SENSING: {
        if (Medium_Sense() != MEDIAN_IDLE) {
                state = RANDOMWAIT;
                counter_transmission = urng( (unsigned int)pow(2, waitingCounter)-1) * LENGTH_TP * TICKS_PER_SEC / sim->getW();
                waitingCounter++;
            } else if ((Medium_Sense() == MEDIAN_IDLE) && useBackoff) {
                //after waiting one time slot and not transmit differ again at
                //transmit with probability p
                //pick a number between 1 and 100 and if it is less than or equal to p
                //then you transmit on a p probability
                int q;
                q = urng((unsigned int)100); //random between 0 and 1
                if (q <= sim->getP()) {
                    state = TRANSMITTING;
                    if (sim->getW() != 0) {
                    counter_transmission = TICKS_PER_SEC*sim->getL()/sim->getW();
                    } else {
                        counter_transmission = 0;
                    }
                    busyCounter++;
                } else {
                    useBackoff = true;
                }

            } else if (useBackoff && (Medium_Sense() != MEDIAN_IDLE)) {
                state = BACKOFF;
                counter_transmission = urng((unsigned int)pow(2, error_count)-1) * LENGTH_TP * TICKS_PER_SEC / sim->getW();
                useBackoff = false;
            } else if (counter_transmission-- <= 0) {
                int q;
                q = urng((unsigned int)100); //random between 0 and 1
                if (q <= sim->getP()) {
                    state = TRANSMITTING;
                    if (sim->getW() != 0) {
                        counter_transmission = TICKS_PER_SEC*sim->getL()/sim->getW();
                    } else {
                        counter_transmission = 0;
                    }
                    busyCounter++;
                } else {
                    useBackoff = true;
                }

            }
            break;
        }
        case TRANSMITTING: {
            if (Medium_Sense() == MEDIAN_COLLISION) {
                state = JAMMING;
                busyCounter++;
                counter_transmission = LENGTH_JAMING;
            }
            else if (counter_transmission-- <= 0) {
                //packet transmission finished
                state = IDLE;
                curPacket->go(ticks);
                counter_success += curPacket->get_packet_count();
                overall_delay += curPacket->cal_waiting_time();
                busyCounter--;
            }
            break;
        }
        case JAMMING: {
            if (counter_transmission-- <= 0) {
                state = BACKOFF;
                counter_transmission = urng((unsigned int)pow(2, error_count)-1 ) * LENGTH_TP * TICKS_PER_SEC / sim->getW();
                busyCounter -= 2;
                error_count++;
                if (error_count >= MAX_K) {
                    state = ERROR;
                }
            }
            break;
        }
        case BACKOFF: {
            if (counter_transmission-- <= 0) {
                state = SENSING;
                counter_transmission = LENGTH_SENSING;
            }
            break;
        }
        case ERROR: {
            return;     //node is error status, nothing we can do
        }
        default: {
            throw "P_PersistentNode::update undefined state";
        }
    }
}

unsigned long long int Node::get_counter_success() {
    return counter_success;
}

unsigned long long int Node::get_overall_delay() {
    return overall_delay;
}
