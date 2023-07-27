//Luogu - P3376
//LOJ - 101
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

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

int main() {
    valueType N, M, S, T;

    std::cin >> N >> M >> S >> T;

    Graph G(N);

    typedef std::function<void(valueType, valueType, valueType)> AddEdgeFunction;

    AddEdgeFunction AddEdge = [&G](valueType from, valueType to, valueType cap) {
        G[from].emplace_back(to, cap);
        G[to].emplace_back(from, 0);

        G[from].back().pair = std::prev(G[to].end());
        G[to].back().pair = std::prev(G[from].end());
    };

    for (valueType i = 0; i < M; ++i) {
        valueType from, to, cap;

        std::cin >> from >> to >> cap;

        AddEdge(from, to, cap);
    }

    ValueVector depth(N + 1, 0);
    IterVector start(N + 1);

    typedef std::function<bool()> BfsFunction;

    BfsFunction bfs = [&G, &start, S, T, &depth]() -> bool {
        std::queue<valueType> Q;

        std::fill(depth.begin(), depth.end(), 0);
        Q.push(S);
        depth[S] = 1;

        while (!Q.empty()) {
            valueType const from = Q.front();
            Q.pop();

            for (auto const &iter: G[from]) {
                if (iter.cap > iter.flow && !depth[iter.to]) {
                    depth[iter.to] = depth[from] + 1;
                    Q.push(iter.to);
                }
            }
        }

        return depth[T] != 0;
    };

    typedef std::function<valueType(valueType, valueType)> DfsFunction;

    IterVector DfsStart = start;

    DfsFunction dfs = [&G, &DfsStart, &depth, T, &dfs](valueType x, valueType flow) -> valueType {
        if (x == T || flow == 0)
            return flow;

        for (auto &iter = DfsStart[x]; iter != G[x].end(); ++iter) {
            if (iter->cap > iter->flow && depth[iter->to] == depth[x] + 1) {
                valueType const current = dfs(iter->to, std::min(flow, iter->cap - iter->flow));

                if (current > 0) {
                    iter->flow += current;
                    iter->pair->flow -= current;

                    return current;
                }
            }
        }

        return 0;
    };
}