#include <bits/stdc++.h>

typedef int valueType;
typedef unsigned long long hashType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef std::set<hashType> hashSet;

const hashType mask = (std::chrono::system_clock::now().time_since_epoch().count() << 27) ^
                      (std::chrono::system_clock::now().time_since_epoch().count()) ^ (std::random_device()() << 13) ^
                      (std::random_device()());

hashType xor_shift(hashType n) {
    n ^= mask;
    n ^= n << 13;
    n ^= n >> 17;
    n ^= n << 5;
    n ^= mask;

    return n;
}

valueType N;
ValueMatrix G;
hashSet set;

hashType dfs(valueType x, valueType from) {
    static const hashType C = std::chrono::system_clock::now().time_since_epoch().count() ^ 0xc0ffee;

    hashType ans = C;

    for (auto &iter: G[x])
        if (iter != from)
            ans += xor_shift(dfs(iter, x));

    set.insert(ans);

    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> N;

    G.resize(N + 1);

    for(valueType i = 1; i < N; ++i) {
        valueType a, b;

        std::cin >> a >> b;

        G[a].push_back(b);
        G[b].push_back(a);
    }

    dfs(1, 0);

    std::cout << set.size() << std::endl;

    return 0;
}