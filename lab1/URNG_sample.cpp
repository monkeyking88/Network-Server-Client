#include <iostream>
#include <unistd.h>
#include "URNG.h"
using namespace std;

int main() {
    cout << "What is LAMBDA? ";
    cin >> LAMBDA;
    URNG urng;
    urng.seed(getpid());
    const int SIZE = 10000;
    double nums[SIZE];
    double sum = 0;
    for (int i=0; i<SIZE; ++i) {
        nums[i] = urng();
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
    cout << avg << " (should be closed to " << double(1) / LAMBDA << ")" << endl;
    cout << stdev << " (should be closed to " << double(1) / LAMBDA / LAMBDA << ")" << endl;

    return 0;
}
