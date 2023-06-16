//HZ - 51.3
//Luogu - P4178
#include<bits/stdc++.h>

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
typedef int sizeType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MAX = INT_MAX >> 1;
constexpr valueType maxK = 2e4 + 5, maxN = 4e4 + 5;

valueType N_, K_;
valueType const &N = N_, &K = K_;

typedef std::pair<int, valueType> Edge;
typedef std::list<Edge> OutEdgeList;
typedef std::array<OutEdgeList, maxN> EdgeSet;

class TreeArray {
private:
    ValueVector data;

    ValueVector tree;

    sizeType size;

    static const sizeType constexpr shifting = 5;

    valueType lowBit(valueType x) {
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
            pos -= lowBit(pos);;
        }

        return result;
    }
};

TreeArray exist;
std::array<valueType, maxN> buffer, dist, size, weight;
valueType ans;
std::bitset<maxN> visited;

EdgeSet edge;

void calcSize(int x, int from, int &root, int const &sum);

void calcDist(int x, int from, int &bufferSize);

void dfs(int x, int from);

void addEdge(int a, int b, int w);

int main() {
    std::cin >> N_;

    for (int i = 1; i < N; ++i) {
        int a, b, w;

        std::cin >> a >> b >> w;

        addEdge(a, b, w);
    }

    std::cin >> K_;

    exist.resize(K + 10);

    ans = 0;

    int root = 0;

    weight[root] = MAX;

    calcSize(1, -1, root, N);
    calcSize(root, -1, root, N);

    dfs(root, -1);

    std::cout << ans << std::flush;

    return 0;
}

void addEdge(int a, int b, int w) {
    edge[a].emplace_back(b, w);
    edge[b].emplace_back(a, w);
}

void calcSize(int x, int from, int &root, int const &sum) {
    size[x] = 1;
    weight[x] = 0;

    for (auto const &iter: edge[x]) {
        int const to = iter.first;

        if (to == from || visited[to])
            continue;

        calcSize(to, x, root, sum);

        size[x] += size[to];

        weight[x] = std::max(weight[x], size[to]);
    }

    weight[x] = std::max(weight[x], sum - size[x]);

    if (weight[x] < weight[root])
        root = x;
}

void calcDist(int x, int from, int &bufferSize) {
    buffer[++bufferSize] = dist[x];

    for (auto const &iter: edge[x]) {
        int const to = iter.first;

        int const w = iter.second;

        if (to == from || visited[to])
            continue;

        dist[to] = dist[x] + w;

        calcDist(to, x, bufferSize);
    }
}

void dfs(int x, int from) {
    std::queue<valueType> tag;

    std::function<void(valueType)> sure = [&tag](valueType i) mutable {
        if (i > K)
            return;

        exist.insert(i, 1);
        tag.push(i);
    };

    sure(0);

    visited[x] = true;

    for (auto const &iter: edge[x]) {
        int const to = iter.first;

        int const w = iter.second;

        if (to == from || visited[to])
            continue;

        dist[to] = w;

        int bufferSize = 0;

        calcDist(to, x, bufferSize);

        for (int i = 1; i <= bufferSize; ++i)
            if (buffer[i] <= K)
                ans += exist.sum(K - buffer[i]);

        for (int i = 1; i <= bufferSize; ++i)
            sure(buffer[i]);
    }

    while (!tag.empty()) {
        exist.set(tag.front(), 0);
        tag.pop();
    }

    for (auto const &iter: edge[x]) {
        int const to = iter.first;

        if (to == from || visited[to])
            continue;

        int sum = size[to];

        int root = 0;

        weight[root] = MAX;

        calcSize(to, x, root, sum);
        calcSize(root, -1, root, sum);

        dfs(root, x);
    }
}
