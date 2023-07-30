//HZ - 56.1
//Luogu - P2472
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType MAX = std::numeric_limits<valueType>::max();

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
    valueType R, C, D;

    std::cin >> R >> C >> D;

    valueType const N = R * C;

    valueType const S = 2 * N + 1, T = 2 * N + 2;

    Dinic Graph(2 * N + 2);

    typedef std::function<valueType(valueType, valueType)> IDFunction;

    IDFunction id = [R, C, N, T](valueType x, valueType y) -> valueType {
        if (x < 1 || y < 1 || x > R || y > C)
            return T;

        return (x - 1) * C + y;
    };

    for (valueType i = 1; i <= R; ++i) {
        for (valueType j = 1; j <= C; ++j) {
            valueType const u = (i - 1) * C + j;

            char c;

            std::cin >> c;

            valueType const h = c & 15;

            if (h == 0)
                continue;

            Graph.addEdge(u, u + N, h);

            if (D >= 1) {
                Graph.addEdge(u + N, id(i - 1, j), MAX);
                Graph.addEdge(u + N, id(i + 1, j), MAX);
                Graph.addEdge(u + N, id(i, j - 1), MAX);
                Graph.addEdge(u + N, id(i, j + 1), MAX);
            }

            if (D >= 2) {
                Graph.addEdge(u + N, id(i - 2, j), MAX);
                Graph.addEdge(u + N, id(i + 2, j), MAX);
                Graph.addEdge(u + N, id(i, j - 2), MAX);
                Graph.addEdge(u + N, id(i, j + 2), MAX);
                Graph.addEdge(u + N, id(i - 1, j - 1), MAX);
                Graph.addEdge(u + N, id(i - 1, j + 1), MAX);
                Graph.addEdge(u + N, id(i + 1, j - 1), MAX);
                Graph.addEdge(u + N, id(i + 1, j + 1), MAX);
            }

            if (D >= 3) {
                Graph.addEdge(u + N, id(i - 3, j), MAX);
                Graph.addEdge(u + N, id(i + 3, j), MAX);
                Graph.addEdge(u + N, id(i, j - 3), MAX);
                Graph.addEdge(u + N, id(i, j + 3), MAX);
                Graph.addEdge(u + N, id(i - 2, j - 1), MAX);
                Graph.addEdge(u + N, id(i - 2, j + 1), MAX);
                Graph.addEdge(u + N, id(i + 2, j - 1), MAX);
                Graph.addEdge(u + N, id(i + 2, j + 1), MAX);
                Graph.addEdge(u + N, id(i - 1, j - 2), MAX);
                Graph.addEdge(u + N, id(i - 1, j + 2), MAX);
                Graph.addEdge(u + N, id(i + 1, j - 2), MAX);
                Graph.addEdge(u + N, id(i + 1, j + 2), MAX);
                Graph.addEdge(u + N, id(i - 2, j - 2), MAX);
                Graph.addEdge(u + N, id(i - 2, j + 2), MAX);
                Graph.addEdge(u + N, id(i + 2, j - 2), MAX);
                Graph.addEdge(u + N, id(i + 2, j + 2), MAX);
            }

            if (D >= 4) {
                Graph.addEdge(u + N, id(i - 4, j), MAX);
                Graph.addEdge(u + N, id(i + 4, j), MAX);
                Graph.addEdge(u + N, id(i, j - 4), MAX);
                Graph.addEdge(u + N, id(i, j + 4), MAX);
                Graph.addEdge(u + N, id(i - 3, j - 1), MAX);
                Graph.addEdge(u + N, id(i - 3, j + 1), MAX);
                Graph.addEdge(u + N, id(i + 3, j - 1), MAX);
                Graph.addEdge(u + N, id(i + 3, j + 1), MAX);
                Graph.addEdge(u + N, id(i - 1, j - 3), MAX);
                Graph.addEdge(u + N, id(i - 1, j + 3), MAX);
                Graph.addEdge(u + N, id(i + 1, j - 3), MAX);
                Graph.addEdge(u + N, id(i + 1, j + 3), MAX);
                Graph.addEdge(u + N, id(i - 3, j - 2), MAX);
                Graph.addEdge(u + N, id(i - 3, j + 2), MAX);
                Graph.addEdge(u + N, id(i + 3, j - 2), MAX);
                Graph.addEdge(u + N, id(i + 3, j + 2), MAX);
                Graph.addEdge(u + N, id(i - 2, j - 3), MAX);
                Graph.addEdge(u + N, id(i - 2, j + 3), MAX);
                Graph.addEdge(u + N, id(i + 2, j - 3), MAX);
                Graph.addEdge(u + N, id(i + 2, j + 3), MAX);
            }
        }
    }

    valueType count = 0;

    for (valueType i = 1; i <= R; ++i) {
        for (valueType j = 1; j <= C; ++j) {
            valueType const u = (i - 1) * C + j;

            char ch;

            std::cin >> ch;

            if (ch == 'L') {
                ++count;

                Graph.addEdge(S, u, 1);
            }
        }
    }

    Graph.init();

    std::cout << (count - Graph.maxFlow(S, T)) << std::endl;
}