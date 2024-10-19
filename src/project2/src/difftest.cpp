#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <set>

#include "MinHeap.h"

std::set<int> keySet;

int randInt(int min, int max) {
    if (min >= max) return min;
    return min + rand() % (max - min + 1);
}

distPair randDPair(int n, int min, int max) {
    return distPair(n, randInt(min, max));
}

int main() {
    srand(time(NULL));

    int n = 1000;
    bool passed = true;
    BinaryHeap<dist_t> binHeap(n);
    FibonacciHeap<dist_t> fibHeap(n);

    for (int i = 0; i < n; i++) {
        distPair dpair = randDPair(i, 0, 1000000);
        // printf("i = %d, Inserting (%d, %d)\n", i, dpair.key, dpair.value);
        keySet.insert(dpair.key);

        binHeap.insert(dpair);
        fibHeap.insert(dpair);

        distPair binPair = binHeap.findMin();
        distPair fibPair = fibHeap.findMin();
        // fibHeap.printHeap(i+1);

        if (binPair.key != fibPair.key || binPair.value != fibPair.value) {
            printf("Error 1: i = %d, output: bin=(%d, %d), fib=(%d, %d)\n", i, binPair.key, binPair.value, fibPair.key, fibPair.value);
            passed = false;
            break;
        }

        if (randInt(0, 1000) % 5 == 0 && keySet.size() > 0) {
            // printf("i = %d, Deleting min\n", i);
            keySet.erase(binPair.key);

            binHeap.deleteMin();
            fibHeap.deleteMin();

            // fibHeap.printHeap(i+1);

            binPair = binHeap.findMin();
            fibPair = fibHeap.findMin();

            if (binPair.key != fibPair.key || binPair.value != fibPair.value) {
                printf("Error 2: i = %d, output: bin=(%d, %d), fib=(%d, %d)\n", i, binPair.key, binPair.value, fibPair.key, fibPair.value);
                passed = false;
                break;
            }
        }

        if (randInt(0, 1000) % 3 == 0 && keySet.size() > 0) {
            std::set<int>::iterator it = keySet.begin();
            int t = randInt(0, keySet.size() - 1);
            for (int j = 0; j < t; j++, it++);
            int key = *it;
            distPair decreasedPair = distPair(key, randInt(0, 100000));

            // printf("i = %d, Decreasing key of %d to (%d, %d)\n", i, key, decreasedPair.key, decreasedPair.value);

            binHeap.decreaseKey(decreasedPair);
            fibHeap.decreaseKey(decreasedPair);

            // fibHeap.printHeap(i+1);

            binPair = binHeap.findMin();
            fibPair = fibHeap.findMin();
            if (binPair.key != fibPair.key || binPair.value != fibPair.value) {
                printf("Error 3: i = %d, output: bin=(%d, %d), fib=(%d, %d)\n", i, binPair.key, binPair.value, fibPair.key, fibPair.value);
                passed = false;
                break;
            }
        }
    }

    if (passed) {
        printf("All tests passed.\n");
    }

    return 0;
}
