//AT_agc017_d
#include <bits/stdc++.h>

typedef long long valueType;

constexpr valueType MOD = 1e9 + 7;
typedef std::vector<valueType> ValueVector;

template<typename T1, typename T2>
void Inc(T1 &a, const T2 &b) {
    a = a + b;

    if (a > MOD)
        a -= MOD;
}

template<typename T1, typename T2>
void Dec(T1 &a, const T2 &b) {
    a = a - b;

    if (a < 0)
        a += MOD;
}

template<typename T1, typename T2>
T1 sum(const T1 &a, const T2 &b) {
    return a + b >= MOD ? a + b - MOD : a + b;
}

template<typename T1, typename T2>
T1 sub(const T1 &a, const T2 &b) {
    return a - b < 0 ? a - b + MOD : a - b;
}

template<typename T1, typename T2>
T1 mul(const T1 &a, const T2 &b) {
    return (long long) a * b % MOD;
}

template<typename T1, typename T2>
void Mul(T1 &a, const T2 &b) {
    a = (long long) a * b % MOD;
}

template<typename T1, typename T2>
T1 pow(T1 a, T2 b) {
    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a);

        Mul(a, a);
        b = b >> 1;
    }

    return result;
}

class Inverse {
public:
    typedef ValueVector container;

private:
    valueType size;
    container data;
public:
    explicit Inverse(valueType n) : size(n), data(size + 1, 0) {
        data[1] = 1;

        for (valueType i = 2; i <= size; ++i)
            data[i] = mul((MOD - MOD / i), data[MOD % i]);
    }

    valueType operator()(valueType n) const {
        if (n <= size)
            return data[n];

        return mul((MOD - MOD / n), operator()(MOD % n));
    }
} Inv(1e6);

typedef std::list<int> EdgeList;
typedef std::vector<EdgeList> EdgeSet;

int main() {
    std::ios::sync_with_stdio(false);

    valueType N;

    std::cin >> N;

    EdgeSet G(N + 1);

    for (valueType i = 1; i < N; ++i) {
        valueType u, v;

        std::cin >> u >> v;

        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    ValueVector F(N + 1, 0);

    typedef std::function<void(valueType, valueType)> DfsFunction;

    DfsFunction dfs = [&](valueType x, valueType from) {
        F[x] = 0;

        for (auto const &iter: G[x]) {
            if (iter == from)
                continue;

            dfs(iter, x);

            F[x] ^= F[iter] + 1;
        }
    };

    dfs(1, 0);

    valueType count = 0;

    std::cout << (F[1] > 0 ? "Alice" : "Bob") << std::endl;

    return 0;
}