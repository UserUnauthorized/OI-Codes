//HZ - 56.5
//Luogu - P5038
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

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

            for (auto const &iter: G[u]) {
                if ((iter.cap > iter.flow) && (!depth[iter.to])) {
                    depth[iter.to] = depth[u] + 1;
                    Q.push(iter.to);
                }
            }
        }

        return depth[T] > 0;
    }

    valueType dfs(valueType u, valueType T, valueType flow, IterVector &Begin) {
        if (u == T || flow == 0)
            return flow;

        valueType result = 0;

        for (auto &iter = Begin[u]; iter != G[u].end(); ++iter) {
            if (iter->cap > iter->flow && depth[iter->to] == depth[u] + 1) {
                valueType const f = dfs(iter->to, T, std::min(flow - result, iter->cap - iter->flow), Begin);

                iter->flow += f;
                iter->pair->flow -= f;

                result += f;

                if (result == flow)
                    return flow;
            }
        }

        return result;
    }
};

bool check(valueType X, ValueMatrix const &data) {
    constexpr static const valueType INF = std::numeric_limits<valueType>::max();

    valueType const N = (valueType) data.size() - 1, M = (valueType) data.front().size() - 1;

    valueType const size = N * M + 2, S = N * M + 1, T = N * M + 2;

    valueType sumBlack = 0, sumWhite = 0, countBlack = 0, countWhite = 0;

    Dinic dinic(size);

    for (valueType i = 1; i <= N; ++i) {
        for (valueType j = 1; j <= M; ++j) {
            if (X < data[i][j])
                return false;

            if ((i + j) & 1) { // Black
                ++countBlack;

                sumBlack += data[i][j];

                dinic.addEdge(S, (i - 1) * M + j, X - data[i][j]);

                if (i > 1)
                    dinic.addEdge((i - 1) * M + j, (i - 2) * M + j, INF);

                if (i < N)
                    dinic.addEdge((i - 1) * M + j, i * M + j, INF);

                if (j > 1)
                    dinic.addEdge((i - 1) * M + j, (i - 1) * M + j - 1, INF);

                if (j < M)
                    dinic.addEdge((i - 1) * M + j, (i - 1) * M + j + 1, INF);
            } else { // White
                ++countWhite;

                sumWhite += data[i][j];

                dinic.addEdge((i - 1) * M + j, T, X - data[i][j]);
            }
        }
    }

    dinic.init();
    sumBlack = countBlack * X - sumBlack;
    sumWhite = countWhite * X - sumWhite;

    return sumBlack == sumWhite && dinic.maxFlow(S, T) == sumBlack;
}

valueType solve(valueType N, valueType M, ValueMatrix const &data) {
    valueType sumBlack = 0, sumWhite = 0, countBlack = 0, countWhite = 0;

    for (valueType i = 1; i <= N; ++i) {
        for (valueType j = 1; j <= M; ++j) {
            if ((i + j) & 1) { // Black
                ++countBlack;

                sumBlack += data[i][j];
            } else { // White
                ++countWhite;

                sumWhite += data[i][j];
            }
        }
    }

    if (countBlack == countWhite)
        return -1;

    valueType const X = (sumBlack - sumWhite) / (countBlack - countWhite);

    if (check(X, data))
        return (X * N * M - sumBlack - sumWhite) / 2;
    else
        return -1;
}

int main() {
    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType N, M;

        std::cin >> N >> M;

        ValueMatrix source(N + 1, ValueVector(M + 1));

        for (valueType i = 1; i <= N; ++i)
            for (valueType j = 1; j <= M; ++j)
                std::cin >> source[i][j];

        if ((N & 1) && (M & 1)) {
            valueType const ans = solve(N, M, source);

            std::cout << ans << '\n';
        } else {
            valueType left = 0, right = 1e15, X = -1;

            while (left <= right) {
                valueType const mid = (left + right) >> 1;

                if (check(mid, source)) {
                    X = mid;
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }

            if (X == -1) {
                std::cout << -1 << '\n';

                continue;
            }

            valueType ans = 0;

            for (valueType i = 1; i <= N; ++i) {
                for (valueType j = 1; j <= M; ++j) {
                    if ((i + j) & 1) {
                        ans += X - source[i][j];
                    }
                }
            }

            std::cout << ans << '\n';
        }
    }

    std::cout << std::flush;

    return 0;
}