#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

typedef long long LL;

const int N = 100000;
const int M = 1000;
const int MAXA = 131072;
const LL MOD = 1000000007;


int a[N + 100];
LL f[MAXA + 100];
LL power[MAXA + 100];

int lowbit(int x) {
    return x & -x;
}

template<typename T>
void update(T* tree_array, int n, int x, T k, T mod) {
    while (x <= n) {
        tree_array[x] = (tree_array[x] + k) % mod;
        x += lowbit(x);
    }
}

template<typename T>
T query(T* tree_array, int n, int x, T mod) {
    T sum = 0;
    while (x > 0) {
        sum = (sum + tree_array[x]) % mod;
        x -= lowbit(x);
    }
    return sum;
}

template<typename T>
T query_section(T* tree_array, int n, int l, int r, T mod) {
    if (l == 0) {
        return query(tree_array, n, r, mod);
    } else {
        return (query(tree_array, n, r, mod) - query(tree_array, n, l - 1, mod) + MOD) % MOD;
    }
}

void debug(int n, int i) {
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


int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    std::fill(f, f + MAXA, 0);
    std::fill(power, power + MAXA, 0);

    LL sum = 0;
    LL pow2 = 1;
    for (int i = 0; i < n; i++) {
        LL add = sum;
        int val = a[i];

        int lowerb = std::max(val - m, 1);
        int upperb = std::min(val + m, MAXA);
        add = (add + query_section(power, MAXA, lowerb, upperb, MOD) - query_section(f, MAXA, lowerb, upperb, MOD) + MOD) % MOD;

        sum = (sum + add) % MOD;
        update(f, MAXA, val, add, MOD);
        update(power, MAXA, val, pow2, MOD);
        pow2 = (pow2 << 1) % MOD;
        // debug(10, i);
    }
    
    printf("%lld\n", sum);
    return 0;
}
