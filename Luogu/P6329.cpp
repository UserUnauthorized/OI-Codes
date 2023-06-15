//Luogu - P6329
#include <bits/stdc++.h>

namespace DEBUG {
    template<typename T>
    inline void _debug(const char *format, T t) {
        std::cerr << format << '=' << t << std::endl;
    }

    template<class First, class... Rest>
    inline void _debug(const char *format, First first, Rest... rest) {
        while (*format != ',') std::cerr << *format++;
        std::cerr << '=' << first << ",";
        _debug(format + 1, rest...);
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &V) {
        os << "[ ";
        for (const auto &vv: V) os << vv << ", ";
        os << "]";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, __int128 V) {
        if (V < 0) {
            os << '-';
            V = -V;
        }

        if (V > 9)
            os << V / 10;

        os << (int) (V % 10);

        return os;
    }

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

typedef int valueType;
typedef std::vector<valueType> ValueVector;

class TreeArray {
public:
    typedef int sizeType;

private:
    ValueVector data;

    ValueVector tree;

    sizeType size;

    static const sizeType constexpr shifting = 5;

    static valueType lowBit(valueType x) {
        return x & -x;
    }

public:
    TreeArray() : data(0, 0), tree(0, 0), size(0) {};

    void resize(sizeType N) {
        size = N + shifting;

        data.resize(size, 0);
        tree.resize(size, 0);
    }

    void set(sizeType pos, valueType key) {
        pos = pos + shifting;

        valueType const difference = key - data[pos];

        if (difference == 0)
            return;

        data[pos] = key;

        while (pos < size) {
            tree[pos] += difference;
            pos += lowBit(pos);
        }
    }

    void insert(sizeType pos, valueType key) {
        pos = pos + shifting;

        data[pos] += key;

        while (pos < size) {
            tree[pos] += key;
            pos += lowBit(pos);
        }
    }

    valueType sum(sizeType pos) {
        pos = pos + shifting;

        valueType result = 0;

        while (pos > 0) {
            result += tree[pos];
            pos -= lowBit(pos);
        }

        return result;
    }
};

class ST {
public:
    typedef ST self;
    typedef size_t sizeType;
    typedef std::vector<sizeType> SizeVector;
    typedef std::vector<SizeVector> SizeMatrix;

private:
    sizeType size, K;

    SizeMatrix data;

    ValueVector source;

    bool compare(sizeType a, sizeType b) const {
        return source[a] > source[b];
    }

    sizeType max(sizeType a, sizeType b) const {
        return compare(a, b) ? b : a;
    }

public:
    ST(sizeType N, ValueVector s) : size(N), K(std::ceil(std::log2((double) size))), data(K + 1), source(std::move(s)) {
        for (auto &iter: data)
            iter.resize(N + 1);

        for (sizeType i = 1; i <= N; ++i) // 1 - index
            data[0][i] = i;

        for (sizeType i = 1; i <= K; ++i)
            for (sizeType j = 1; j + (1 << i) <= N; ++j)
                data[i][j] = max(data[i - 1][j], data[i - 1][j + (1 << (i - 1))]);
    }

    valueType query(sizeType l, sizeType r) const {
        sizeType const k = std::floor(std::log2((double) (r - l + 1)));

        return (valueType) max(data[k][l], data[k][r - (1 << k) + 1]);
    }
};

typedef std::array<TreeArray, 2> TreeArrayPair;

constexpr valueType MAX = INT_MAX >> 1;
constexpr valueType maxN = 1e5 + 5;

valueType N_, M_;
valueType const &N = N_, &M = M_;

typedef std::list<int> EdgeList;
typedef std::vector<EdgeList> EdgeSet;

int main() {
    EdgeSet edge;

    std::vector<bool> visited;
    ValueVector value, depth, leftBound, rightBound, father, size, node, weight;

    std::vector<TreeArrayPair> tree;

    std::cin >> N_ >> M_;

    visited.resize(N + 1);
    value.resize(N + 1);
    depth.resize(N + 1);
    leftBound.resize(N + 1);
    rightBound.resize(N + 1);
    father.resize(N + 1);
    size.resize(N + 1);
    node.resize(2 * N + 1);
    weight.resize(N + 1);
    edge.resize(N + 1);
    tree.resize(N + 1);

    for (int i = 1; i <= N; ++i)
        std::cin >> value[i];

    std::function<void(int, int)> addEdge = [&](int u, int v) {
        edge[u].push_back(v);
        edge[v].push_back(u);
    };

    for (int i = 1; i < N; ++i) {
        int a, b;

        std::cin >> a >> b;

        addEdge(a, b);
    }

    std::function<void(int, int)> dfs = [&](int x, int from) {
        static int dfsCount = 0;

        leftBound[x] = ++dfsCount;
//        debug(x, leftBound[x]);
        node[dfsCount] = x;
        size[x] = 1;
        depth[x] = depth[from] + 1;

        for (auto v: edge[x]) {
            if (v == from)
                continue;

            dfs(v, x);

            size[x] += size[v];
        }

        rightBound[x] = ++dfsCount;
        node[dfsCount] = x;
    };

    dfs(1, 0);

    ValueVector stSource(2 * N + 1, 0);

    for (int i = 1; i <= (N * 2); ++i)
        stSource[i] = depth[node[i]];

    ST st(N * 2 + 1, stSource);
//    debug(node);
//    debug(leftBound);
//    debug(rightBound);
//    debug(depth);
//    debug(stSource);
//    debug(leftBound, depth, stSource);
    std::function<int(int, int)> LCA = [&](int a, int b) {
        if (leftBound[a] > leftBound[b])
            std::swap(a, b);
        int const result = st.query(leftBound[a], leftBound[b]);
//        debug(a, b, result);
        return node[st.query(leftBound[a], leftBound[b])];
    };

    std::function<valueType(int, int)> distance = [&](int a, int b) {
        int const lca = LCA(a, b);

//        debug(a, b, lca, depth);
        return depth[a] + depth[b] - 2 * depth[LCA(a, b)];
    };

    std::function<void(int, int, int &, const int &)> calcSize = [&](int x, int from, int &root, int const sum) {
        size[x] = 1;

        weight[x] = 0;

        for (auto const &iter: edge[x]) {
            if (iter == from || visited[iter])
                continue;

            calcSize(iter, x, root, sum);

            size[x] += size[iter];

            weight[x] = std::max(weight[x], size[iter]);
        }

        weight[x] = std::max(weight[x], sum - size[x]);

        if (weight[x] < weight[root])
            root = x;
    };

    std::function<void(int, valueType)> build = [&](int x, valueType sum) {
        visited[x] = true;

        size[x] = sum;

        tree[x][0].resize(sum + 3);
        tree[x][1].resize(sum + 3);

        for (auto const &iter: edge[x]) {
            if (visited[iter])
                continue;

            int root = 0;
            weight[0] = MAX;

            calcSize(iter, x, root, size[iter]);

            build(iter, size[iter]);

            father[root] = x;
        }
    };

    std::function<void(int, valueType)> modify = [&](int x, valueType key) {
        for (int i = x; i != 0; i = father[i])
            tree[i][0].insert(distance(x, i), key);


        for (int i = x; father[i] != 0; i = father[i])
            tree[i][1].insert(distance(x, father[i]), key);
    };

    std::function<valueType(int, valueType)> query = [&](int x, valueType key) -> valueType {
        valueType result = 0;

        result += tree[x][0].sum(key);

        for (int i = x; father[i] != 0; i = father[i]) {
            valueType const dis = distance(x, father[i]);
//            debug(i, father[i], x, dis);
            if (key >= dis)
                result += tree[father[i]][0].sum(key - dis) - tree[i][1].sum(key - dis);
        }

        return result;
    };

    build(1, N);

    for (int i = 1; i <= N; ++i)
        modify(i, value[i]);

    valueType lastAns = 0;
    for (int i = 1; i <= M; ++i) {
        int opt, x, y;

        std::cin >> opt >> x >> y;

        x ^= lastAns;
        y ^= lastAns;

        if (opt == 0) {
//            debug(x, y);
            lastAns = query(x, y);
//            debug(lastAns);
            std::cout << lastAns << '\n';
        } else if (opt == 1) {
            modify(x, y - value[i]);

            value[i] = y;
        }
    }

    std::cout << std::flush;

    return 0;
}