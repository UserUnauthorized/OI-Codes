//HZ - 51.4
#include<bits/stdc++.h>

typedef long long valueType;

constexpr valueType MAX = INT_MAX >> 1;
constexpr valueType maxN = 1e5 + 5, maxK = maxN * 2 + 100, shifting = maxN + 50;

valueType N_, K_;
valueType const &N = N_, &K = K_;

typedef std::pair<int, valueType> Edge;
typedef std::list<Edge> OutEdgeList;
typedef std::array<OutEdgeList, maxN> EdgeSet;

std::array<valueType, maxK> exist;
std::array<std::array<valueType, maxK>, 2> F, G;
std::array<valueType, maxN> dist, size, weight;
valueType ans = 0;
std::bitset<maxN> visited;

EdgeSet edge;

void calcSize(int x, int from, int &root, valueType const &sum);

void calcDist(int x, int from, valueType &maxDepth);

void dfs(int x, int from);

void addEdge(int a, int b, int w);

int main() {
    std::cin >> N_;

    for (int i = 1; i < N; ++i) {
        int a, b, w;

        std::cin >> a >> b >> w;

        if (w == 0)
            w = -1;

        addEdge(a, b, w);
    }

    ans = 0;

    int root = 0;

    weight[root] = MAX;

    calcSize(1, -1, root, N);

    dfs(root, -1);

    std::cout << ans << std::flush;

    return 0;
}

void addEdge(int a, int b, int w) {
    edge[a].emplace_back(b, w);
    edge[b].emplace_back(a, w);
}

void calcSize(int x, int from, int &root, valueType const &sum) {
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

void calcDist(int x, int from, valueType &maxDepth) {
    maxDepth = std::max(maxDepth, std::abs(dist[x]));

    if (exist[dist[x] + shifting] > 0)
        ++G[1][dist[x] + shifting];
    else
        ++G[0][dist[x] + shifting];

    ++exist[dist[x] + shifting];

    for (auto const &iter: edge[x]) {
        int const to = iter.first;

        valueType const w = iter.second;

        if (to == from || visited[to])
            continue;

        dist[to] = dist[x] + w;

        calcDist(to, x, maxDepth);
    }

    --exist[dist[x] + shifting];
}

void dfs(int x, int from) {
    valueType maxDepth = 0;

    visited[x] = true;

    for (auto const &iter: edge[x]) {
        int const to = iter.first;

        int const w = iter.second;

        if (to == from || visited[to])
            continue;

        dist[to] = w;

        valueType thisDepth = 0;

        calcDist(to, x, thisDepth);

        maxDepth = std::max(maxDepth, thisDepth);

        for (int i = 0; i <= thisDepth; ++i) {
            ans += F[0][shifting - i] * G[1][shifting + i];
            ans += F[1][shifting - i] * G[0][shifting + i];
            ans += F[1][shifting - i] * G[1][shifting + i];

            if (i == 0)
                continue;

            ans += F[0][shifting + i] * G[1][shifting - i];
            ans += F[1][shifting + i] * G[0][shifting - i];
            ans += F[1][shifting + i] * G[1][shifting - i];
        }

        ans += F[0][shifting + 0] * G[0][shifting + 0];

        ans += G[1][shifting + 0];

        for (int i = 0; i <= thisDepth; ++i) {
            F[0][shifting - i] += G[0][shifting - i];
            F[1][shifting - i] += G[1][shifting - i];

            G[1][shifting - i] = 0;
            G[0][shifting - i] = 0;

            if (i == 0)
                continue;

            F[0][shifting + i] += G[0][shifting + i];
            F[1][shifting + i] += G[1][shifting + i];

            G[1][shifting + i] = 0;
            G[0][shifting + i] = 0;
        }
    }

    for (int i = 0; i <= maxDepth; ++i) {
        F[1][shifting + i] = 0;
        F[0][shifting + i] = 0;
        F[1][shifting - i] = 0;
        F[0][shifting - i] = 0;
    }

    for (auto const &iter: edge[x]) {
        int const to = iter.first;

        if (to == from || visited[to])
            continue;

        valueType const sum = size[to];

        int root = 0;

        weight[root] = MAX;

        calcSize(to, x, root, sum);

        dfs(root, x);
    }
}
