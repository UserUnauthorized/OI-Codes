//HZ - 31.7
#include<bits/stdc++.h>

using namespace std;
constexpr int maxN = 1e3 + 5, maxS = 1 << 15 | 5, maxD = 15;
typedef unsigned int bitType;
int N, D, K, ans(0);
bitType disease[maxN];

void init();

inline int getBitSum(bitType x);

int main() {
    init();

    bitType const S = 1 << D;

    if (D == K) {
        cout << N;
        return 0;
    }

    for (bitType i = 0; i < S; ++i) {
        if (getBitSum(i) != K)
            continue;

        int result(0);

        for (int j = 1; j <= N; ++j)
            if ((disease[j] | i) == i)
                ++result;

        ans = max(ans, result);
    }

    cout << ans;
    return 0;
}

void init() {
    memset(disease, 0, sizeof(disease));

    cin >> N >> D >> K;

    for (int i = 1; i <= N; ++i) {
        int t;
        cin >> t;
        while (t--) {
            int k;
            cin >> k;
            disease[i] += 1 << (k - 1);
        }
    }
}

inline int getBitSum(bitType x) {
    int result(0);
    for (; x > 0; x >>= 1)
        if (x & 1)
            ++result;
    return result;
}
