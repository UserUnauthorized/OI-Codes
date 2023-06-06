//HZ - 35.14
//Luogu - P3232
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
typedef long double realType;
typedef std::vector<realType> RealVector;
typedef std::vector<realType> ROW;
typedef std::vector<ROW> MATRIX;
typedef std::pair<int, int> Edge;
typedef std::vector<Edge> EdgeVector;
typedef std::list<int> OutEdgeList;
typedef std::vector<OutEdgeList> EdgeSet;

ROW solve(MATRIX A, const int &size);

int main() {
	int N, M;
	
	std::cin >> N >> M;
	
	EdgeSet edge(N + 1);
	
	EdgeVector source;
	
	MATRIX matrix(N - 1);
	
	for(auto &iter : matrix)
		iter.resize(N, 0);
	
	source.reserve(M);
	
	std::function<void(int, int)> addEdge = [&source, &edge] (int a, int b) mutable {
		source.emplace_back(a, b);
		
		edge[a].emplace_back(b);
		
		edge[b].emplace_back(a);
	};
	
	for(int i = 1; i <= M; ++i) {
		int a, b;
		
		std::cin >> a >> b;
		
		addEdge(a, b);
	}
	
	
	matrix[0][N - 1] = -1;
	for(int i = 1; i < N; ++i) {
		matrix[i - 1][i - 1] = -1;
		
		for(auto const &iter : edge[i]) {
			if(iter == N)
				continue;
				
			matrix[i - 1][iter - 1] = (realType) 1 / edge[iter].size();
		}
	}
	
	ROW result = solve(matrix, N - 1);
	
	RealVector count(N + 1, 0);
	
	for(int i = 1; i < N; ++i)
		count[i] = result[i - 1];
		
	RealVector value(M, 0);
	
	for(int i = 0; i < M; ++i) {
		int const x = source[i].first, y = source[i].second;
		
		value[i] = count[x] / edge[x].size() + count[y] / edge[y].size();
	}
	
	std::sort(value.begin(), value.end(), std::greater<realType>());
	
	realType ans = 0;
	
	for(int i = 0; i < M; ++i)
		ans += value[i] * (i + 1);
		
	std::cout << std::setprecision(3) << std::fixed << ans << std::flush;
	
	return 0;
}

ROW solve(MATRIX A, const int &size) {
    ROW result(size);
    int validLines(0);
    for (int i = 0; i < size; ++i) {
        int maxRow = validLines;
        for (int j = validLines + 1; j < size; ++j)
            if (fabs(A[j][i]) > fabs(A[maxRow][i]))
                maxRow = j;

        if (maxRow != validLines)
            swap(A[maxRow], A[validLines]);

        if (A[validLines][i] == 0)
            continue;

        for (int j = 0; j < size; ++j)
            if (j != validLines)
                for (int k = i + 1; k <= size; ++k)
                    A[j][k] -= A[validLines][k] * A[j][i] / A[validLines][i];

        ++validLines;
    }

    if (validLines < size) {
        result[size + 1] = -2;
        while (validLines < size)
            if (A[validLines++][size] != 0) result[size + 1] = -1;
    } else {
        for (int i = 0; i < size; ++i)
            result[i + 1] = A[i][size] / A[i][i];
    }

    return result;
}
