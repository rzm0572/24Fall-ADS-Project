#include "MinHeap.h"
#include <cstdio>

template class LeftistHeap<dist_pair>;

template<class T>
LeftistHeap<T>::LeftistHeap() {
    printf("LeftistHeap created\n");
}

template<class T>
Pair<T> LeftistHeap<T>::findMin() {
    // TODO
    return Pair<T>();
}

template<class T>
bool LeftistHeap<T>::insert(Pair<T> x) {
    // TODO
    return false;
}

template<class T>
bool LeftistHeap<T>::deleteMin() {
    // TODO
    return false;
}

template<class T>
bool LeftistHeap<T>::decreaseKey(Pair<T> x) {
    // TODO
    return false;
}
