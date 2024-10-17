#include "MinHeap.h"
#include <cstdio>

template class BinaryHeap<dist_pair>;

template<class T>
BinaryHeap<T>::BinaryHeap() {
    printf("BinaryHeap created\n");
}

template<class T>
Pair<T> BinaryHeap<T>::findMin() {
    // TODO
    return Pair<T>();
}

template<class T>
bool BinaryHeap<T>::insert(Pair<T> x) {
    // TODO
    return false;
}

template<class T>
bool BinaryHeap<T>::deleteMin() {
    // TODO
    return false;
}

template<class T>
bool BinaryHeap<T>::decreaseKey(Pair<T> x) {
    // TODO
    return false;
}
