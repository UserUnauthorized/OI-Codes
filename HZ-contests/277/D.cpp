//HZ - 277.4
#include <bits/stdc++.h>

using namespace std;
constexpr int maxn = 1e6 + 6;

struct NODE {
    int SAN;
    bool minSan[5];
    int size;
    vector<int> to;
    set<int> sans;

    NODE();
} node[maxn];

inline int read();

inline void init();

void dfs(int);

int n, k, q, ans = 0;

int main() {
//    freopen("scratch_21.txt", "w", stdout);
//    freopen("ex_coc2.in", "r", stdin);

    init();
    dfs(1);

    for (int i = 1; i <= n; ++i)
        if (!node[i].minSan[1] && !node[i].minSan[2] && !node[i].minSan[3] && node[i].size < q)
            ++ans;

    printf("%d", ans);
//    fclose(stdin);
//    fclose(stdout);
    return 0;
}

NODE::NODE() : SAN(-1), size(-1) {
    memset(minSan, 0, sizeof(minSan));
}

inline void init() {
    n = read();
    k = read();
    q = read();

    for (int i = 1; i <= n; ++i)
        node[i].SAN = read();

    for (int i = 2; i <= n; ++i)
        node[read()].to.push_back(i);
}

inline int read() {
    int result(0), ch(getchar());
    bool positive(true);

    while ((ch < '0' || ch > '9') && ch != '-')
        ch = getchar();

    if (ch == '-') {
        positive = false;
        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        result = (result << 3) + (result << 1) + (ch ^ 48);
        ch = getchar();
    }

    if (positive)
        return result;
    else
        return -result;
}

void dfs(int x) {
    node[x].minSan[1] = node[x].SAN < k;
    node[x].sans.insert(node[x].SAN);

    for (const int &iter: node[x].to) {
        dfs(iter);
        node[x].sans.insert(node[iter].sans.begin(), node[iter].sans.end());
        node[x].minSan[2] = node[x].minSan[2] || node[iter].minSan[1];
        node[x].minSan[3] = node[x].minSan[3] || node[iter].minSan[2];
    }

    node[x].size = (int) node[x].sans.size();
}