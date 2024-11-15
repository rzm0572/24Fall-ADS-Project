#ifndef BSEQ_H
#define BSEQ_H

// Default algorithm name
#ifndef ALGORITHM_NAME
    #define ALGORITHM_NAME BItree
#endif

typedef long long LL;

// Constants
static const int N = 100000;
static const int M = 1000;
static const int MAXA = 100000;
static const LL MOD = 1000000007;

// Calculate the number of Beautiful Subsequences in array a[0..n-1]
// @param n: size of the array
// @param m: the threshold of the beautiful subsequence
// @param a: the input array
// @return: the number of beautiful subsequences
int count_BSeq(int n, int m, int a[]);

#endif