//Luogu - P3324
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

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

typedef std::vector<char> CharVector;
typedef std::vector<CharVector> CharMatrix;

constexpr valueType EPS = 1e4, maxT = 1e7, R = maxT * EPS;

int main() {
    valueType N, M;

    std::cin >> N >> M;

    ValueVector A(N), B(M);

    for (auto &iter: A) {
        std::cin >> iter;

        iter *= EPS;
    }

    valueType const SUM = std::accumulate(A.begin(), A.end(), (valueType) 0);

    for (auto &iter: B)
        std::cin >> iter;

    CharMatrix map(M, CharVector(N));

    for (auto &iter: map)
        for (auto &iter2: iter)
            std::cin >> iter2;

    typedef std::function<bool(valueType)> CheckFunction;

    CheckFunction check = [&](valueType Time) -> bool {
        //build
        Dinic dinic(N + M + 2);

        valueType const S = N + M + 1, T = N + M + 2;

        for (valueType i = 1; i <= M; ++i)
            dinic.addEdge(S, i, B[i - 1] * Time);

        for (valueType i = 1; i <= N; ++i)
            dinic.addEdge(M + i, T, A[i - 1]);

        for (valueType i = 1; i <= M; ++i)
            for (valueType j = 1; j <= N; ++j)
                if (map[i - 1][j - 1] == '1')
                    dinic.addEdge(i, M + j, std::numeric_limits<valueType>::max());

        dinic.init();

        return dinic.maxFlow(S, T) >= SUM;
    };

    valueType left = 0, right = R, ans;

    while (left <= right) {
        valueType const mid = (left + right) >> 1;

        if (check(mid)) {
            ans = mid;
            right = mid - 1;
        } else
            left = mid + 1;
    }

    long double const result = (long double) ans / EPS;

    std::cout << std::fixed << result << std::endl;
}