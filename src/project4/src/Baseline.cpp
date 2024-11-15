#include <cstdio>
#include <algorithm>
#include "BSeq.h"

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

// Fill the power array with base^0, base^1, base^2, ..., base^(n-1)
void power_init(int n, LL power[], int base) {
    power[0] = 1;
    for (int i = 1; i <= n; i++) {
        power[i] = power[i - 1] * base % MOD;
    }
}

int count_BSeq(int n, int m, int a[]) {
    // Allocate memory for helper arrays
    LL *f = new LL[MAXA + 100];      // f[i] = number of BSeqs in a[0..i-1]
    LL *power = new LL[MAXA + 100];  // power[i] = base^i % MOD

    // Initialize helper arrays
    std::fill(f, f + MAXA, 0);
    power_init(n, power, 2);

    LL sum = 0;
    for (int i = 1; i < n; i++) {
        LL add = sum;  // Any BSeqs ended with a[0..i-1] can be concatenated with a[i] to form a BSeq
        for (int j = 0; j < i; j++) {
            if (std::labs(a[i] - a[j]) <= m) {   // if a[i] and a[j] are within distance m
                // Any Non-BSeqs ended with a[j] can be concatenated with a[i] to form a BSeq
                add = (add + power[j] - f[j] + MOD) % MOD;
            }
        }
        sum = (sum + add) % MOD;
        f[i] = (f[i] + add) % MOD;
        // debug(n, i, f, power);
    }

    delete[] f;
    delete[] power;
    
    return sum;
}
