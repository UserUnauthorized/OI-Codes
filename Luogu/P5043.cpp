#include <bits/stdc++.h>

typedef int valueType;
typedef unsigned long long hashType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef std::vector<hashType> HashVector;
typedef std::map<hashType, valueType> HashMap;

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


hashType getSub(valueType x, valueType from, ValueMatrix const &G, HashVector &sub) {
    static const hashType C = std::chrono::system_clock::now().time_since_epoch().count() ^ 0xc0ffee;

    hashType ans = C;

    for (auto &iter: G[x])
        if (iter != from)
            ans += xor_shift(getSub(iter, x, G, sub));

    return sub[x] = ans;
}

void getRoot(valueType x, valueType from, ValueMatrix const &G, HashVector const &sub, HashVector &root) {
    for (auto const &iter: G[x]) {
        if (iter == from)
            continue;

        root[iter] = sub[iter] + xor_shift(root[x] - xor_shift(sub[iter]));

        getRoot(iter, x, G, sub, root);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType M;

    std::cin >> M;

    HashMap table;

    for (valueType number = 1; number <= M; ++number) {
        valueType N;

        std::cin >> N;

        ValueMatrix G(N + 1);

        valueType ROOT = 0;

        for (valueType i = 1; i <= N; ++i) {
            valueType father;

            std::cin >> father;

            if (father == 0) {
                ROOT = i;
            } else {
                G[father].push_back(i);
                G[i].push_back(father);
            }
        }

        HashVector sub(N + 1), root(N + 1);

        getSub(ROOT, 0, G, sub);

        root[ROOT] = sub[ROOT];

        getRoot(ROOT, 0, G, sub, root);

        hashType ans = 0;

        for (valueType i = 1; i <= N; ++i)
            ans += xor_shift(root[i]);

        if (table.count(ans) == 0)
            table[ans] = number;

        std::cout << table[ans] << std::endl;
    }

    return 0;
}