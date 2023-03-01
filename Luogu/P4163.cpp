//HZ - 31.8
//Luogu - P4163
#include<bits/stdc++.h>

using namespace std;
typedef unsigned int bitType;
constexpr bitType maxS = (1 << 10) + 3, maxD = 1e3 + 3;
int T;
int dp[maxS][maxD];
bool vis[maxD];

inline void solve();

int main() {
    cin >> T;
    while (T--)
        solve();
    return 0;
}

inline void solve() {
    memset(dp, 0, sizeof(dp));

    string str;
    cin >> str;
    int D;
    cin >> D;
    vector<int> source;
    for (auto iter: str)
        source.push_back(iter & 15);

    int const K = source.size();
    bitType const S = 1 << K;
    dp[0][0] = 1;

    for (bitType i = 0; i < S; ++i) {
        memset(vis, 0, sizeof(vis));
        for (int j = 0; j < K; ++j) {
            if (i & (1 << j)) continue;
            if (vis[source[j]]) continue;
            vis[source[j]] = true;
            for (int d = 0; d < D; ++d) {
                dp[i | (1 << j)][(d * 10 + source[j]) % D] += dp[i][d];
            }
        }
    }

    cout << dp[S - 1][0] << endl;
}
