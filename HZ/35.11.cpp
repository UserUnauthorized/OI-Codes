//HZ - 35.11
//Luogu - P1850
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

typedef long long valueType;
typedef size_t sizeType;
typedef long double realType;

constexpr valueType MAX = INT_MAX >> 1, MIN = INT_MIN >> 1;
constexpr realType INF = INFINITY;

class Graph {
public:
//	typedef std::pair<int, valueType> EdgePair;
//	typedef std::list<EdgePair> OutEdgeList;
//	typedef std::vector<OutEdgeList> EdgeSet;
    typedef std::vector<valueType> OutEdgeList;
    typedef std::vector<OutEdgeList> EdgeSet;
    typedef std::vector<valueType> distanceArray;
    typedef std::vector<distanceArray> distanceMatrix;

protected:
    sizeType N;
    EdgeSet edge;
    distanceMatrix dis;

public:
    Graph(sizeType _N_) : N(_N_), edge(_N_ + 1), dis(_N_ + 1) {
        for (sizeType i = 1; i <= N; ++i) {
            dis[i].resize(N + 1);
            edge[i].resize(N + 1, MAX);
            edge[i][i] = 0;
        }
    };

    void addEdge(int a, int b, valueType w) {
        edge[a][b] = edge[b][a] = std::min(edge[a][b], w);
    }

    void calcDistance() {
        dis = edge;

        for (sizeType k = 1; k <= N; ++k)
            for (sizeType x = 1; x <= N; ++x)
                for (sizeType y = 1; y <= N; ++y)
                    dis[x][y] = std::min(dis[x][y], dis[x][k] + dis[k][y]);
    }

    valueType distance(int a, int b) const {
        return dis[a][b];
    }

    const EdgeSet &data() const {
        return edge;
    }
};

typedef std::vector<valueType> ValueVector;
typedef std::vector<realType> RealVector;
typedef std::vector<RealVector> RealMatrix;
typedef std::function<valueType(int, int)> DistanceFunction;

int main() {
//#define FILEIO
//#ifdef LOCAL
//#ifdef FILEIO
//	freopen("class.in", "r", stdin);
//	freopen("class.out", "w", stdout);
//	freopen("class.err", "w", stderr);
//#endif
//#endif

    int N, M, V, E;

    std::cin >> N >> M >> V >> E;

    Graph G(V);

    ValueVector C(N + 1, 0), D(N + 1, 0);

    RealVector P(N + 1, 0);

    for (int i = 1; i <= N; ++i)
        std::cin >> C[i];

    for (int i = 1; i <= N; ++i)
        std::cin >> D[i];

    for (int i = 1; i <= N; ++i)
        std::cin >> P[i];

    for (int i = 0; i < E; ++i) {
        int a, b, w;

        std::cin >> a >> b >> w;

        G.addEdge(a, b, w);
    }

    G.calcDistance();

    DistanceFunction distance = [&G](int a, int b) -> valueType {
        return G.distance(a, b);
    };

    std::array<std::array<RealVector, 2>, 2> dp;

    dp[0][0].resize(N + 1, INF);
    dp[1][0].resize(N + 1, INF);
    dp[0][1].resize(N + 1, INF);
    dp[1][1].resize(N + 1, INF);

    dp[0][1][0] = 0;
    dp[1][1][1] = 0;

    for (int i = 2; i <= N; ++i) {
        int const now = i & 1, pre = now ^ 1;

        dp[0][now][0] = dp[0][pre][0] + distance(C[i - 1], C[i]);

        for (int j = 1; j <= i; ++j) {
            realType const ans_0_0 = dp[0][pre][j] + distance(C[i - 1], C[i]);

            realType const ans_0_1 =
                    dp[1][pre][j] + (1 - P[i - 1]) * distance(C[i - 1], C[i]) + P[i - 1] * distance(D[i - 1], C[i]);

            dp[0][now][j] = std::min(ans_0_0, ans_0_1);

            realType const ans_1_0 = (dp[0][pre][j - 1] + P[i] * distance(C[i - 1], D[i]) +
                                      (1 - P[i]) * distance(C[i - 1], C[i]));

            realType const ans_1_1 = P[i - 1] * (dp[1][pre][j - 1] + P[i] * distance(D[i - 1], D[i]) +
                                                 (1 - P[i]) * distance(D[i - 1], C[i])) +
                                     (1 - P[i - 1]) * (dp[1][pre][j - 1] + P[i] * distance(C[i - 1], D[i]) +
                                                       (1 - P[i]) * distance(C[i - 1], C[i]));

            dp[1][now][j] = std::min(ans_1_0, ans_1_1);
        }
    }

    realType ans = INF;

    int const final = N & 1;

    for (int i = 0; i <= M; ++i)
        ans = std::min({ans, dp[0][final][i], dp[1][final][i]});


    std::cout << std::setprecision(2) << std::fixed << ans << std::flush;

    return 0;
}
