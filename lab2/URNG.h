#ifndef __URNG_H__
#define __URNG_H__

#include <cstdlib>                  // rand
#include <math.h>                   // log
#include <random>
using namespace std;

class URNG {
    unsigned int seed_;
    default_random_engine* generator;
  public:
    URNG( unsigned int seed = 1009 ) : seed_( seed ) { srand( seed ); generator = new default_random_engine(seed); } // set seed
    ~URNG() { free(generator); };
    unsigned int seed() { return seed_; }       // set seed
    void seed( unsigned int seed ) { seed_ = seed; srand( seed ); free(generator); generator = new default_random_engine(seed); } // set seed
    unsigned int operator()() { return rand(); }    // [0,UINT_MAX]
    unsigned int operator()( unsigned int u ) { return operator()() % (u + 1); } // [0,u]
    unsigned int operator()( unsigned int l, unsigned int u ) { return operator()( u - l ) + l; } // [l,u]]}]}
    unsigned int operator()( double u ) { return operator()() % ((unsigned int)u + 1); } // [0,u]
    unsigned int operator()( double l, double u ) { return operator()( (unsigned int)u - (unsigned int)l ) + (unsigned int)l; } // [l,u]]}]}
    unsigned int poissonGen( int m ) {
        poisson_distribution<unsigned int> distribution (m);
        return distribution(*generator);
    };
}; // URNG

#endif // __URNG_H__
