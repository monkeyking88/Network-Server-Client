#ifndef __URNG_H__
#define __URNG_H__

#include <cstdlib>                  // rand
#include <math.h>                   // log
using namespace std;

double LAMBDA  = 0;    //average number of packets generated/arrived packet per second
extern double LAMBDA;

class URNG {
    unsigned int seed_;
  public:
    URNG( unsigned int seed = 1009 ) : seed_( seed ) { srand( seed ); } // set seed
    unsigned int seed() { return seed_; }       // set seed
    void seed( unsigned int seed ) { seed_ = seed; srand( seed ); } // set seed
    double operator()() {
        double uniform = double(rand()) / RAND_MAX;
        double exp = -( log( double(1) - uniform ) ) / double(LAMBDA);
        return exp;
    }    // [0,1]
}; // URNG

#endif // __URNG_H__
