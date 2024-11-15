#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "BSeq.h"

// lowbit function
// Return the lowest 1-bit in x
// For example, if x = 10101010, lowbit(x) = 00000010
int lowbit(int x) {
    return x & -x;
}

// Single Point Update function of Binary Indexed Tree (BIT)
// @param tree_array: the array storing the BIT
// @param n: the size of the array
// @param x: the index of the element to be updated
// @param k: the value to be added to the element
// @param mod: the modulus value
template<typename T>
void update(T* tree_array, int n, int x, T k, T mod) {
    while (x <= n) {
        tree_array[x] = (tree_array[x] + k) % mod;  // Update the value in BIT
        x += lowbit(x);  // Find the parent of x
    }
}

// Prefix Sum Query function of Binary Indexed Tree (BIT)
// @param tree_array: the array storing the BIT
// @param n: the size of the array
// @param x: the right endpoint of the section to be queried
// @param mod: the modulus value
// @return the sum of the elements in the range [1, x]
template<typename T>
T query(T* tree_array, int n, int x, T mod) {
    T sum = 0;
    while (x > 0) {
        sum = (sum + tree_array[x]) % mod;  // Add the value in BIT to sum
        x -= lowbit(x);  // Find the child of x
    }
    return sum;
}

// Section Sum Query function of Binary Indexed Tree (BIT)
// @param tree_array: the array storing the BIT
// @param n: the size of the array
// @param l: the left endpoint of the section to be queried
// @param r: the right endpoint of the section to be queried
// @param mod: the modulus value
// @return the sum of the elements in the range [l, r]
template<typename T>
T query_section(T* tree_array, int n, int l, int r, T mod) {
    if (l == 0) {
        return query(tree_array, n, r, mod);
    } else {
        return (query(tree_array, n, r, mod) - query(tree_array, n, l - 1, mod) + MOD) % MOD;
    }
}

// Debug function
void debug(int n, int i, LL *f, LL *power) {
    printf("i = %d\n", i);
    for (int i = 0; i < n; i++) {
        printf("%lld ", f[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%lld ", power[i]);
    }
    printf("\n\n");
}

int count_BSeq(int n, int m, int* a) {
    // Allocate memory for BIT
    LL *f = new LL[MAXA + 100];      // f[i] = BIT(number of BSeqs ended with i)
    LL *power = new LL[MAXA + 100];  // power[i] - f[i] = BIT(number of Non-BSeqs ended with i)

    // Initialize BIT
    std::fill(f, f + MAXA, 0);
    std::fill(power, power + MAXA, 0);

    LL sum = 0;
    LL pow2 = 1;
    for (int i = 0; i < n; i++) {
        LL add = sum;  // Any BSeqs ended with a[0..i-1] can be concatenated with a[i] to form a BSeq
        int val = a[i];

        int lowerb = std::max(val - m, 1);      // The lower bound of the section to be queried
        int upperb = std::min(val + m, MAXA);   // The upper bound of the section to be queried

        // Any Non-BSeqs ended with [a[i]-m, a[i]+m] can be concatenated with a[i] to form a BSeq
        add = (add + query_section(power, MAXA, lowerb, upperb, MOD) - query_section(f, MAXA, lowerb, upperb, MOD) + MOD) % MOD;

        sum = (sum + add) % MOD;
        update(f, MAXA, val, add, MOD);       // Update f
        update(power, MAXA, val, pow2, MOD);  // Update power
        pow2 = (pow2 << 1) % MOD;
        // debug(10, i, f, power);
    }

    delete[] f;
    delete[] power;
    
    return sum;
}
