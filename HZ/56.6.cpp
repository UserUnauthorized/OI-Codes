//HZ - 56.6
//Luogu - P1646
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType INF = std::numeric_limits<valueType>::max();

class Dinic {
private:
    struct Edge {
    public:
        typedef std::list<Edge> container;
        typedef container::iterator iterator;

        valueType to;
        valueType cap;
        valueType flow;
        iterator pair;

        Edge() : to(-1), cap(-1), flow(-1), pair() {};

        Edge(valueType to, valueType cap, iterator pair = iterator()) : to(to), cap(cap), flow(0), pair(pair) {};
    };

    typedef std::vector<Edge::container> Graph;
    typedef std::vector<Edge::iterator> IterVector;

    valueType N;
    Graph G;
    ValueVector depth;
    IterVector start;
    bool Initialized;

public:
    explicit Dinic(valueType N) : N(N), G(N + 1), depth(N + 1, 0), start(N + 1), Initialized(false) {};

    void addEdge(valueType from, valueType to, valueType cap) {
        if (__builtin_expect(Initialized, false))
            throw std::runtime_error("Dinic: addEdge after init");

        G[from].emplace_back(to, cap);
        G[to].emplace_back(from, 0);
        G[from].back().pair = std::prev(G[to].end());
        G[to].back().pair = std::prev(G[from].end());
    }

    void init() {
        if (__builtin_expect(Initialized, false))
            throw std::runtime_error("Dinic: init twice");

        Initialized = true;

        std::fill(depth.begin(), depth.end(), 0);

        for (valueType i = 1; i <= N; ++i)
            start[i] = G[i].begin();
    }

    void reset() {
        if (__builtin_expect(!Initialized, false))
            throw std::runtime_error("Dinic: reset before init");

        for (valueType i = 1; i <= N; ++i)
            for (auto &iter: G[i])
                iter.flow = 0;

        std::fill(depth.begin(), depth.end(), 0);

        Initialized = false;
    }

    valueType maxFlow(valueType S, valueType T) {
        if (__builtin_expect(!Initialized, false))
            throw std::runtime_error("Dinic: maxFlow before init");

        valueType result = 0;

        while (bfs(S, T)) {
            IterVector begin = start;

            result += dfs(S, T, std::numeric_limits<valueType>::max(), begin);
        }

        return result;
    }

private:
    bool bfs(valueType S, valueType T) {
        std::fill(depth.begin(), depth.end(), 0);

        std::queue<valueType> Q;

        Q.push(S);
        depth[S] = 1;

        while (!Q.empty()) {
            valueType const u = Q.front();

            Q.pop();

            for (auto const &e: G[u]) {
                if ((e.cap > e.flow) && (!depth[e.to])) {
                    depth[e.to] = depth[u] + 1;
                    Q.push(e.to);
                }
            }
        }

        return depth[T] > 0;
    }

    valueType dfs(valueType u, valueType T, valueType flow, IterVector &Begin) {
        if (u == T || flow == 0)
            return flow;

        valueType result = 0;

        for (auto &e = Begin[u]; e != G[u].end(); ++e) {
            if (e->cap > e->flow && depth[e->to] == depth[u] + 1) {
                valueType const f = dfs(e->to, T, std::min(flow - result, e->cap - e->flow), Begin);

                e->flow += f;
                e->pair->flow -= f;

                result += f;

                if (result == flow)
                    return flow;
            }
        }

        return result;
    }
};

int main() {
    valueType N, M;

    std::cin >> N >> M;

    valueType const C = N * M, total = C * 5 + 10;

    valueType const S = C * 5 + 1, T = C * 5 + 2;

    Dinic dinic(total);

    valueType sum = 0;

    for (valueType i = 1; i <= N; ++i) {
        for (valueType j = 1; j <= M; ++j) {
            valueType w;

            std::cin >> w;

            sum += w;

            valueType const u = (i - 1) * M + j;

            dinic.addEdge(S, u, w);
        }
    }

    for (valueType i = 1; i <= N; ++i) {
        for (valueType j = 1; j <= M; ++j) {
            valueType w;

            std::cin >> w;

            sum += w;

            valueType const u = (i - 1) * M + j;

            dinic.addEdge(u, T, w);
        }
    }

    for (valueType i = 1; i < N; ++i) {
        for (valueType j = 1; j <= M; ++j) {
            valueType w;

            std::cin >> w;

            sum += w;

            valueType const u = (i - 1) * M + j, v = i * M + j;

            valueType const x = u + C;

            dinic.addEdge(S, x, w);
            dinic.addEdge(x, u, INF);
            dinic.addEdge(x, v, INF);
        }
    }

    for (valueType i = 1; i < N; ++i) {
        for (valueType j = 1; j <= M; ++j) {
            valueType w;

            std::cin >> w;

            sum += w;

            valueType const u = (i - 1) * M + j, v = i * M + j;

            valueType const x = u + 2 * C;

            dinic.addEdge(x, T, w);
            dinic.addEdge(u, x, INF);
            dinic.addEdge(v, x, INF);
        }
    }

    for (valueType i = 1; i <= N; ++i) {
        for (valueType j = 1; j < M; ++j) {
            valueType w;

            std::cin >> w;

            sum += w;

            valueType const u = (i - 1) * M + j, v = u + 1;

            valueType const x = u + 3 * C;

            dinic.addEdge(S, x, w);
            dinic.addEdge(x, u, INF);
            dinic.addEdge(x, v, INF);
        }
    }

    for (valueType i = 1; i <= N; ++i) {
        for (valueType j = 1; j < M; ++j) {
            valueType w;

            std::cin >> w;

            sum += w;

            valueType const u = (i - 1) * M + j, v = u + 1;

            valueType const x = u + 4 * C;

            dinic.addEdge(x, T, w);
            dinic.addEdge(u, x, INF);
            dinic.addEdge(v, x, INF);
        }
    }

    dinic.init();

    valueType const ans = sum - dinic.maxFlow(S, T);

    std::cout << ans << std::endl;
}