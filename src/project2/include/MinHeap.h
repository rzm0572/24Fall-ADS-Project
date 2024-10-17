#ifndef _MIN_HEAP_H
#define _MIN_HEAP_H

#ifndef HEAPTYPE
    #define HEAPTYPE Binomial
#endif

// Timing marcos
#define START_TIMER \
    struct timeval begin; \
    gettimeofday(&begin, (struct timezone *)0);

#define STOP_TIMER(t) \
    struct timeval end; \
    gettimeofday(&end, (struct timezone *)0); \
    t += (double)(end.tv_sec - begin.tv_sec) + (double)(end.tv_usec - begin.tv_usec) * 1.e-6;

#define PRINT_TIMER(msg, ...) \
{ \
    struct timeval end; \
    gettimeofday(&end, (struct timezone *)0); \
    double t = (double)(end.tv_sec - begin.tv_sec) + (double)(end.tv_usec - begin.tv_usec) * 1.e-6; \
    printf("%.6fs " msg, t, ##__VA_ARGS__); \
}

#define real_tostr(x) #x
#define tostr(x) real_tostr(x)

#define real_cat(a, b) a##b
#define cat(a, b) real_cat(a, b)


// ID-Distance pair struct
template <class T>
struct Pair {
    int key;
    T value;

    Pair() : key(-1) {};
    Pair(int _key, T _value) : key(_key), value(_value) {};
    bool operator < (const Pair<T> &other) const {
        return value < other.value;
    }
};

// Min heap base class
template <class T>
class MinHeap {
protected:
    int size;

public:
    // TODO: Need to implement
    virtual Pair<T> findMin() = 0;
    virtual bool insert(Pair<T> x) = 0;
    virtual bool deleteMin() = 0;
    virtual bool decreaseKey(Pair<T> x) = 0;
    virtual int getSize() = 0;
    // Not necessary to implement in Dijkstra
    // vitrual bool deleteAny(int key);
    // virtual bool merge(MinHeap b);
};

// Four implementations of MinHeap
// TODO: You can add declarations of any helper functions or variables in these classes as your wish.
// For example, decreaseKey needs a array of pointers to nodes, which can be declaired as a private member variable.

template <class T>
class BinomialHeap : public MinHeap<T> {
public:
    BinomialHeap();
    Pair<T> findMin();
    bool insert(Pair<T> x);
    bool deleteMin();
    bool decreaseKey(Pair<T> x);
};

template <class T>
class FibonacciHeap : public MinHeap<T> {
public:
    FibonacciHeap();
    Pair<T> findMin();
    bool insert(Pair<T> x);
    bool deleteMin();
    bool decreaseKey(Pair<T> x);
};

template <class T>
class BinaryHeap : public MinHeap<T> {
protected:
    int size;
    Pair<T> *Heap;
    int * Position;

public:
    BinaryHeap(int n);
    Pair<T> findMin();
    bool insert(Pair<T> x);
    bool deleteMin();
    bool decreaseKey(Pair<T> x);
    int getSize();
};

template <class T>
class LeftistHeap : public MinHeap<T> {
public:
    LeftistHeap();
    Pair<T> findMin();
    bool insert(Pair<T> x);
    bool deleteMin();
    bool decreaseKey(Pair<T> x);
};

typedef int dist_t;              // Type of distance
typedef Pair<dist_t> dist_pair;  // Type of ID-distance pair

template <typename T>
using PriorityQueue = cat(HEAPTYPE, Heap)<T>;

#endif
