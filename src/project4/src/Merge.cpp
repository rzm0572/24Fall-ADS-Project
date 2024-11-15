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

int count_BSeq(int n, int m, int a[]) {
    // Allocate memory for helper arrays
    LL *f = new LL[MAXA + 100];      // f[i] = number of BSeqs ended with i
    LL *power = new LL[MAXA + 100];  // power[i] - f[i] = number of Non-BSeqs ended with i
    
    // Initialize helper arrays
    std::fill(f, f + MAXA, 0);
    std::fill(power, power + MAXA, 0);

    LL sum = 0;
    LL pow2 = 1;
    for (int i = 0; i < n; i++) {
        LL add = sum;  // Any BSeqs ended with a[0..i-1] can be concatenated with a[i] to form a BSeq
        int val = a[i];
        for (int j = std::max(val - m, 0); j <= std::min(val + m, MAXA); j++) {
            // Any Non-BSeqs ended with [a[i]-m, a[i]+m] can be concatenated with a[i] to form a BSeq
            add = (add + power[j] - f[j] + MOD) % MOD;
        }
        sum = (sum + add) % MOD;
        f[val] = (f[val] + add) % MOD;
        power[val] = (power[val] + pow2) % MOD;
        pow2 = (pow2 << 1) % MOD;
    }

    delete[] f;
    delete[] power;
    
    return sum;
}
