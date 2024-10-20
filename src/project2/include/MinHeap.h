#ifndef _MIN_HEAP_H
#define _MIN_HEAP_H

#ifndef HEAPTYPE
#define HEAPTYPE Binomial
#endif

// Timing marcos
#define START_TIMER       \
    struct timeval begin; \
    gettimeofday(&begin, (struct timezone*)0);

#define STOP_TIMER(t)                        \
    struct timeval end;                      \
    gettimeofday(&end, (struct timezone*)0); \
    t += (double)(end.tv_sec - begin.tv_sec) + (double)(end.tv_usec - begin.tv_usec) * 1.e-6;

#define PRINT_TIMER(msg, ...)                                                                           \
    {                                                                                                   \
        struct timeval end;                                                                             \
        gettimeofday(&end, (struct timezone*)0);                                                        \
        double t = (double)(end.tv_sec - begin.tv_sec) + (double)(end.tv_usec - begin.tv_usec) * 1.e-6; \
        printf("%.6fs " msg, t, ##__VA_ARGS__);                                                         \
    }

// Logging marcos
#define logger(file, msg, ...)             \
    {                                      \
        printf(msg, ##__VA_ARGS__);        \
        fprintf(file, msg, ##__VA_ARGS__); \
        fflush(file);                      \
    }

// Transform x to string
#define real_tostr(x) #x
#define tostr(x) real_tostr(x)

// Concatenate two marco
#define real_cat(a, b) a##b
#define cat(a, b) real_cat(a, b)

// ID-Distance pair struct
template <class T>
struct Pair {
    int key;  // ID
    T value;  // distance

    Pair() : key(-1) {};
    Pair(int _key, T _value) : key(_key), value(_value) {};
    bool operator<(const Pair<T>& other) const {  // operator < for Pair
        return value < other.value;
    }
};

// Min heap base class
template <class T>
class MinHeap {
   protected:
    int size;

   public:
    MinHeap(int _size = 0) : size(_size) {}
    // TODO: Need to implement
    virtual Pair<T> findMin() = 0;
    virtual bool insert(Pair<T> x) = 0;
    virtual bool deleteMin() = 0;
    virtual bool decreaseKey(Pair<T> x) = 0;

    // Not necessary to implement in Dijkstra
    // vitrual bool deleteAny(int key);
    // virtual bool merge(MinHeap b);

    // Helper function
    int getSize() { return size; }
    virtual bool checkExist(int key) = 0;
};

// Four implementations of MinHeap
// TODO: You can add declarations of any helper functions or variables in these classes as your wish.
// For example, decreaseKey needs a array of pointers to nodes, which can be declaired as a private member variable.

// BinomialHeap implementation
template <class T>
class BinomialHeap : public MinHeap<T> {
   private:
    // TODO: You can add any helper functions or variables as your wish ^v^
    struct TreeNode {
        // TODO: This the node structure of BinomialHeap
    };

   public:
    BinomialHeap(int n);
    ~BinomialHeap();
    Pair<T> findMin();
    bool insert(Pair<T> x);
    bool deleteMin();
    bool decreaseKey(Pair<T> x);
    bool checkExist(int key);
};

// FibonacciHeap implementation
template <class T>
class FibonacciHeap : public MinHeap<T> {
   private:
    int rootLen;       // Length of root list
    struct TreeNode {  // Node structure
        Pair<T> data;
        int deg;
        bool marked;
        TreeNode* parent;
        TreeNode* child;
        TreeNode* left;
        TreeNode* right;
        TreeNode(Pair<T> _data = Pair<T>(), int _deg = 0, bool _marked = false, TreeNode* _parent = nullptr, TreeNode* child = nullptr, TreeNode* _left = nullptr, TreeNode* _right = nullptr) : data(_data), deg(_deg), marked(_marked), parent(_parent), left(_left), right(_right) {}
    };

    TreeNode* minNode;  // Pointer to minimum node
    TreeNode** Position;

    // Helper function
    void insertRootList(TreeNode* newNode);        // Insert a new node to root list
    bool deleteRootList(TreeNode* deleteNodePtr);  // Delete a node from root list
    TreeNode* heapLink(TreeNode* x, TreeNode* y);  // Let one of x and y be a child of the other
    void consolidate();                            // merge trees of equal degree in the root list
    void cut(TreeNode* x);                         // cut x from its parent and add it to root list
    void cascadingCut(TreeNode* x);

   public:
    FibonacciHeap(int n);         // Constructor
    ~FibonacciHeap();             // Destructor
    Pair<T> findMin();            // Find the minimum node in the heap
    bool insert(Pair<T> x);       // Insert a new node into the heap
    bool deleteMin();             // Delete the minimum node from the heap
    bool decreaseKey(Pair<T> x);  // Decrease the key of a node in the heap
    bool checkExist(int key);     // Check if a node with a given key exists in the heap

    void printHeap(int n);  // Debugging function to print the heap
};

// BinaryHeap implementation
template <class T>
class BinaryHeap : public MinHeap<T> {
   private:
    Pair<T>* Heap;
    int* Position;

   public:
    BinaryHeap(int n);
    ~BinaryHeap();
    Pair<T> findMin();
    bool insert(Pair<T> x);
    bool deleteMin();
    bool decreaseKey(Pair<T> x);
    bool checkExist(int key);
};

// LeftistHeap implementation
template <class T>
class LeftistHeap : public MinHeap<T> {
   private:
    struct TreeNode {  // 节点结构
        Pair<T> value;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
        int height;

    }* root;
    TreeNode** Position;

   public:
    LeftistHeap(int n);  // 初始化
    ~LeftistHeap();
    TreeNode* Merge(TreeNode* T1, TreeNode* T2);  // 合并两个左式堆
    Pair<T> findMin();                            // 找到最小值
    bool insert(Pair<T> x);                       // 插入元素
    bool deleteMin();                             // 删除最小值
    bool decreaseKey(Pair<T> x);                  // 减小值
    TreeNode* NewNode(Pair<T> x);                 // 创建新节点
    bool checkExist(int key);                     // 检查是否存在
};

typedef int dist_t;             // Type of distance
typedef Pair<dist_t> distPair;  // Type of ID-distance pair

template <typename T>
using PriorityQueue = cat(HEAPTYPE, Heap)<T>;  // Let PriorityQueue be a synonym of the chosen heap type

#endif
