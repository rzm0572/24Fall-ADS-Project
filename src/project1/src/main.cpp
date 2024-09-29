#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <sys/time.h>
#include <algorithm>
#include "BST.h"

int main(int argc, char* argv[]) {
    int n;

    FILE *fp = fopen(argv[1], "r");
    fscanf(fp, "%d", &n);

    Operation *ops = new Operation[n];

    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d %d", &ops[i].optype, &ops[i].key);
    }

    START_TIMER;
    TestBST(n, ops);
    PRINT_TIMER("Operation end\n");

    fclose(fp);
    delete[] ops;
    return 0;
}
