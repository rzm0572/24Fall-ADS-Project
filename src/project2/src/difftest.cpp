#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <set>

#include "MinHeap.h"

#define INF 1000000000

#define heaptype1 Binary
#define heaptype2 Test

template <class T>
class TestHeap : public MinHeap<T> {
   private:
    T* vec;
    int n;

   public:
    TestHeap(int n) : MinHeap<T>(0) {
        this->n = n;
        vec = new T[n + 1];
        for (int i = 0; i < n; i++) {
            vec[i] = INF;
        }
    }

    ~TestHeap() {
        delete[] vec;
    }

    distPair findMin() {
        T min = vec[1], mini = 1;
        for (int i = 0; i < n; i++) {
            if (vec[i] < min) {
                min = vec[i];
                mini = i;
            }
        }
        return distPair(mini, min);
    }

    bool insert(distPair x) {
        if (vec[x.key] != INF) {
            return false;
        }
        vec[x.key] = x.value;
        MinHeap<T>::size++;
        return true;
    }

    bool deleteMin() {
        if (MinHeap<T>::size == 0) {
            return false;
        }
        distPair min = findMin();
        vec[min.key] = INF;
        MinHeap<T>::size--;
        return true;
    }

    bool decreaseKey(distPair x) {
        if (vec[x.key] < x.value) {
            return false;
        }
        vec[x.key] = x.value;
        return true;
    }

    bool checkExist(int key) {
        return vec[key] != INF;
    }
};

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
    cat(heaptype1, Heap)<dist_t> heap1(n);
    cat(heaptype2, Heap)<dist_t> heap2(n);

    printf("Testing %sHeap and %sHeap.\n", tostr(heaptype1), tostr(heaptype2));

    for (int i = 0; i < n; i++) {
        distPair dpair = randDPair(i, 0, 1000000);

#ifdef DEBUG
        printf("i = %d, Inserting (%d, %d)\n", i, dpair.key, dpair.value);
#endif
        keySet.insert(dpair.key);

        heap1.insert(dpair);
        heap2.insert(dpair);

        distPair heap1_pair = heap1.findMin();
        distPair heap2_pair = heap2.findMin();

#ifdef DEBUG
        // heap2.printHeap(i+1);
#endif

        if (heap1_pair.key != heap2_pair.key || heap1_pair.value != heap2_pair.value) {
            printf("Error 1: i = %d, output: %s=(%d, %d), %s=(%d, %d)\n", i, tostr(heaptype1), heap1_pair.key, heap1_pair.value, tostr(heaptype2), heap2_pair.key, heap2_pair.value);
            passed = false;
            break;
        }

        if (randInt(0, 1000) % 5 == 0 && keySet.size() > 1) {
#ifdef DEBUG
            printf("i = %d, Deleting min\n", i);
#endif
            keySet.erase(heap1_pair.key);

            heap1.deleteMin();
            heap2.deleteMin();

#ifdef DEBUG
            // heap2.printHeap(i+1);
#endif
            heap1_pair = heap1.findMin();
            heap2_pair = heap2.findMin();

            if (heap1_pair.key != heap2_pair.key || heap1_pair.value != heap2_pair.value) {
                printf("Error 2: i = %d, output: %s=(%d, %d), %s=(%d, %d)\n", i, tostr(heaptype1), heap1_pair.key, heap1_pair.value, tostr(heaptype2), heap2_pair.key, heap2_pair.value);
                passed = false;
                break;
            }
        }

        if (randInt(0, 1000) % 3 == 0 && keySet.size() > 1) {
            std::set<int>::iterator it = keySet.begin();
            int t = randInt(0, keySet.size() - 1);
            for (int j = 0; j < t; j++, it++);
            int key = *it;
            distPair decreasedPair = distPair(key, randInt(0, 100000));

#ifdef DEBUG
            printf("i = %d, Decreasing key of %d to (%d, %d)\n", i, key, decreasedPair.key, decreasedPair.value);
#endif

            heap1.decreaseKey(decreasedPair);
            heap2.decreaseKey(decreasedPair);

#ifdef DEBUG
            // heap2.printHeap(i+1);
#endif

            heap1_pair = heap1.findMin();
            heap2_pair = heap2.findMin();
            if (heap1_pair.key != heap2_pair.key || heap1_pair.value != heap2_pair.value) {
                printf("Error 3: i = %d, output: %s=(%d, %d), %s=(%d, %d)\n", i, tostr(heaptype1), heap1_pair.key, heap1_pair.value, tostr(heaptype2), heap2_pair.key, heap2_pair.value);
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
