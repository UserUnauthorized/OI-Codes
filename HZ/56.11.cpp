//HZ - 56.11
//Luogu - P2153
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

class MCMF {
private:
    struct Edge {
    public:
        typedef std::list<Edge> container;
        typedef container::iterator iterator;

        valueType to;
        valueType cap;
        valueType flow;
        valueType cost;
        iterator pair;

        Edge() : to(-1), cap(-1), flow(-1), cost(0), pair() {};

        Edge(valueType to, valueType cap, valueType c, iterator pair = iterator()) : to(to), cap(cap), flow(0), cost(c),
                                                                                     pair(pair) {};
    };

    typedef std::vector<Edge::container> Graph;
    typedef std::vector<Edge::iterator> IterVector;
    typedef std::vector<bool> bitset;

    valueType N;
    Graph G;
    ValueVector dist;
    IterVector start;
    bool Initialized;

public:
    explicit MCMF(valueType N) : N(N), G(N + 1), dist(N + 1, 0), start(N + 1), Initialized(false) {};

    Edge::iterator addEdge(valueType from, valueType to, valueType cap, valueType cost) {
        if (__builtin_expect(Initialized, false))
            throw std::runtime_error("MCMF: addEdge after init");

        G[from].emplace_back(to, cap, cost);
        G[to].emplace_back(from, 0, -cost);
        G[from].back().pair = std::prev(G[to].end());
        G[to].back().pair = std::prev(G[from].end());

        return std::prev(G[from].end());
    }

    void init() {
        if (__builtin_expect(Initialized, false))
            throw std::runtime_error("MCMF: init twice");

        Initialized = true;

        std::fill(dist.begin(), dist.end(), 0);

        for (valueType i = 1; i <= N; ++i)
            start[i] = G[i].begin();
    }

    void reset() {
        if (__builtin_expect(!Initialized, false))
            throw std::runtime_error("MCMF: reset before init");

        for (valueType i = 1; i <= N; ++i)
            for (auto &iter: G[i])
                iter.flow = 0;

        std::fill(dist.begin(), dist.end(), 0);

        Initialized = false;
    }

    std::pair<valueType, valueType> maxFlow(valueType S, valueType T) {
        if (__builtin_expect(!Initialized, false))
            throw std::runtime_error("MCMF: maxFlow before init");

        std::pair<valueType, valueType> result(0, 0);

        while (bfs(S, T)) {
            IterVector begin = start;

            bitset visited(N + 1, false);

            valueType const flow = dfs(S, T, std::numeric_limits<valueType>::max(), begin, visited);

            result.first += flow;
            result.second += flow * dist[T];
        }

        return result;
    }

private:
    bool bfs(valueType S, valueType T) {
        std::fill(dist.begin(), dist.end(), std::numeric_limits<valueType>::max());

        bitset visited(N + 1, false);

        std::queue<valueType> Q;

        Q.push(S);
        dist[S] = 0;
        visited[S] = true;

        while (!Q.empty()) {
            valueType const u = Q.front();

            visited[u] = false;
            Q.pop();

            for (auto const &e: G[u]) {
                if ((e.cap > e.flow) && (dist[e.to] > dist[u] + e.cost)) {
                    dist[e.to] = dist[u] + e.cost;

                    if (!visited[e.to]) {
                        Q.push(e.to);
                        visited[e.to] = true;
                    }
                }
            }
        }

        return dist[T] != std::numeric_limits<valueType>::max();
    }

    valueType dfs(valueType u, valueType T, valueType flow, IterVector &Begin, bitset &visited) {
        if (u == T || flow == 0)
            return flow;

        valueType result = 0;

        visited[u] = true;

        for (auto &e = Begin[u]; e != G[u].end() && flow > 0; ++e) {
            if (!visited[e->to] && e->cap > e->flow && dist[e->to] == dist[u] + e->cost) {
                valueType const f = dfs(e->to, T, std::min(flow - result, e->cap - e->flow), Begin, visited);

                if (f == 0) {
                    dist[e->to] = std::numeric_limits<valueType>::max();

                    continue;
                }

                e->flow += f;
                e->pair->flow -= f;

                result += f;

                if (result == flow) {
                    visited[u] = false;

                    return flow;
                }
            }
        }

        visited[u] = false;

        return result;
    }
};

int main() {
    valueType N, M;

    std::cin >> N >> M;

    valueType const size = 2 * N + 10;

    valueType S = 1 << 1 | 1, T = N << 1;

    MCMF mcmf(size);

    constexpr valueType INF = std::numeric_limits<valueType>::max();

    for (valueType i = 0; i < M; ++i) {
        valueType u, v, w;

        std::cin >> u >> v >> w;

        if (u == 1 && v == N) {
            mcmf.addEdge(S, T, 1, w);

            continue;
        }

        mcmf.addEdge(u << 1 | 1, v << 1, INF, w);
    }

    for (valueType i = 1; i <= N; ++i)
        mcmf.addEdge(i << 1, i << 1 | 1, 1, 0);

    mcmf.init();

    auto const result = mcmf.maxFlow(S, T);

    std::cout << result.first << ' ' << result.second << std::endl;
}