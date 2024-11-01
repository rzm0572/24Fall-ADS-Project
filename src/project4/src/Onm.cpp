#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

typedef long long LL;

const int N = 100000;
const int M = 1000;
const int MAXA = 100000;
const LL MOD = 1000000007;


int a[N + 100];
LL f[MAXA + 100];
LL power[MAXA + 100];

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
        for (int j = std::max(val - m, 0); j <= std::min(val + m, MAXA); j++) {
            add = (add + power[j] - f[j]) % MOD;
        }
        sum = (sum + add) % MOD;
        f[val] = (f[val] + add) % MOD;
        power[val] = (power[val] + pow2) % MOD;
        pow2 = (pow2 << 1) % MOD;
    }
    
    printf("%lld\n", sum);
    return 0;
}
