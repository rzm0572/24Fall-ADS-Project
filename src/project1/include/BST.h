#ifndef BST_H
#define BST_H

// timing marcos
#define START_TIMER \
    struct timeval begin; \
    gettimeofday(&begin, (struct timezone *)0);

#define PRINT_TIMER(msg, ...) \
{ \
    struct timeval end; \
    gettimeofday(&end, (struct timezone *)0); \
    double t = (double)(end.tv_sec - begin.tv_sec) + (double)(end.tv_usec - begin.tv_usec) * 1.e-6; \
    printf("%.6fs " msg, t, ##__VA_ARGS__); \
}

struct Operation {
    int optype;  // 0: insert, 1: delete
    int key;
    int value;
    Operation(int _optype = 0, int _key = 0, int _value = 0) : optype(_optype), key(_key), value(_value) {}
};

void TestBST(int n, Operation ops[]);

#endif
