#include "linkedStack.h"
#include <iostream>
#include <sys/time.h>

using namespace std;

int main() {
    linkedStack<int> fcstack1;
    struct timeval begin, end;
    long timeuse;

    gettimeofday(&begin, nullptr);

    for (int i = 0; i < 50000000; i++) {
        fcstack1.push(i);
    }

    for (int i = 0; i < 50000000; i++) {
        fcstack1.pop();
    }

    gettimeofday(&end, nullptr);
    timeuse = end.tv_sec - begin.tv_sec + (long)(end.tv_usec - begin.tv_usec) / 1000000.0;

    cout << "time = " << timeuse << "\n";
    // cout << fcstack1;
    
    return 0;
}