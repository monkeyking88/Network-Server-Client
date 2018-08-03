#include <iostream>
#include "URNG.h"
#include <math.h>
using namespace std;

int main() {
    URNG urng;
    urng.seed(getpid());
    const int SIZE = 10000;
    double nums[SIZE];
    double sum = 0;
    for (int i=0; i<SIZE; ++i) {
        nums[i] = urng.poissonGen(10);
        sum += nums[i];
    }
    double avg = sum / SIZE;
    double stdev = 0;
    double diff;
    for (int i=0; i<SIZE; ++i) {
        diff = nums[i] - avg;
        stdev += diff * diff;
    }
    stdev = stdev / SIZE;
    cout << avg << " (should be closed to " << 10 << ")" << endl;
    cout << stdev << " (should be closed to " << 10 << ")" << endl;

    return 0;
}
