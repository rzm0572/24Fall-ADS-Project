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

#define logger(file, msg, ...) \
{ \
    printf(msg, ##__VA_ARGS__); \
    fprintf(file, msg, ##__VA_ARGS__); \
}

#define real_tostr(x) #x
#define tostr(x) real_tostr(x)

#define real_cat(a, b) a##b
#define cat(a, b) real_cat(a, b)


// ID-Distance pair struct
template <class T>
struct Pair {
    int key;  // ID
    T value;  // distance

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

    // Not necessary to implement in Dijkstra
    // vitrual bool deleteAny(int key);
    // virtual bool merge(MinHeap b);

    // Helper function
    virtual int getSize() = 0;
    virtual bool checkExist(int key) = 0;
};

// Four implementations of MinHeap
// TODO: You can add declarations of any helper functions or variables in these classes as your wish.
// For example, decreaseKey needs a array of pointers to nodes, which can be declaired as a private member variable.

template <class T>
class BinomialHeap : public MinHeap<T> {
public:
    BinomialHeap(int n);
    Pair<T> findMin();
    bool insert(Pair<T> x);
    bool deleteMin();
    bool decreaseKey(Pair<T> x);
    int getSize();
    bool checkExist(int key);
};

template <class T>
class FibonacciHeap : public MinHeap<T> {
public:
    FibonacciHeap(int n);
    Pair<T> findMin();
    bool insert(Pair<T> x);
    bool deleteMin();
    bool decreaseKey(Pair<T> x);
    int getSize();
    bool checkExist(int key);
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
    bool checkExist(int key);
};
/*
左式堆
*/
template <class T>
class LeftistHeap : public MinHeap<T> {
protected:
    int size;// 堆的大小
    struct TreeNode{// 节点结构
        Pair<T> value;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
        int height;

    }*root;
    TreeNode **Position;
public:
    LeftistHeap(int n);// 初始化
    TreeNode* Merge(TreeNode* T1, TreeNode* T2);// 合并两个左式堆
    Pair<T> findMin();// 找到最小值
    bool insert(Pair<T> x);// 插入元素
    bool deleteMin();// 删除最小值
    bool decreaseKey(Pair<T> x);// 减小值
    int getSize();// 获取大小
    TreeNode* NewNode(Pair<T> x);// 创建新节点
    bool checkExist(int key);// 检查是否存在
};

typedef int dist_t;              // Type of distance
typedef Pair<dist_t> distPair;  // Type of ID-distance pair

template <typename T>
using PriorityQueue = cat(HEAPTYPE, Heap)<T>;

#endif
