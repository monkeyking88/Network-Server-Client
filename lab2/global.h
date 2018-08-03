#ifndef GLOBAL_H
#define GLOBAL_H

#include <cstdlib>
#include "URNG.h"

typedef enum mediamState { MEDIAN_IDLE, MEDIAN_BUSY, MEDIAN_COLLISION } STATE_MEDIAN;

extern int busyCounter;
extern int waitingCounter;
extern URNG urng;

inline STATE_MEDIAN Medium_Sense(){
    switch (busyCounter) {
        case MEDIAN_IDLE :
            return MEDIAN_IDLE;
        case MEDIAN_BUSY :
            return MEDIAN_BUSY;
        default:
            return MEDIAN_COLLISION;
    }
}

#endif
