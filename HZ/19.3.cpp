//HZ - 19.3
//Luogu - P4159
//LOJ - 10225
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

constexpr long long const MOD = 2009;

class Matrix{
public:
	typedef long long valueType;
	typedef size_t sizeType;
	typedef std::vector<valueType> Row;
	typedef std::vector<Row> Container;
	
public:
	sizeType row, column;
	Container data;
	
public:
	Matrix(sizeType _row_, sizeType _column_) : row(_row_), column(_column_), data(row + 1){
		for(sizeType i = 1; i <= row; ++i)
			data[i].resize(column + 1, 0);
	};
	
	Matrix operator*(const Matrix &T) const {
		Matrix result(this->row, T.column);
		
		for(sizeType i = 1; i <= this->row; ++i) {
			for(sizeType k = 1; k <= this->column; ++k) {
				valueType r = this->data[i][k];
				
				for(sizeType j = 1; j <= T.column; ++j)
					result.data[i][j] = (result.data[i][j] + T.data[k][j] * r) % MOD;
			}
		}
		
		return result;
	}
	
	friend std::ostream &operator<<(std::ostream &os, const Matrix &T) {
		for(sizeType i = 1; i <= T.row; ++i)
			for(sizeType j = 1; j <= T.column; ++j)
				os << T.data[i][j] << " \n"[j == T.column];
				
		return os;
	}
	
	friend std::istream &operator>>(std::istream &os, Matrix &T) {
		for(sizeType i = 1; i <= T.row; ++i)
			for(sizeType j = 1; j <= T.column; ++j)
				os >> T.data[i][j];
				
		return os;
	}
};

int main() {
	int N, T;
	
	std::cin >> N >> T;
	
	int const M = N * 10;
	
	Matrix Graph(M, M);
	
	std::function<void(int, int)> addSingleEdge = [&Graph] (int u, int v) mutable {
		++Graph.data[u][v];
	};
	
	std::function<void(int, int, int)> addEdge = [&addSingleEdge](int u, int v, int w) mutable {
		int const from = (u - 1) * 9 + w;
		int const to = (v - 1) * 9 + 1;

		addSingleEdge(from, to);
	};
	
	for(int i = 1; i <= N; ++i)
		for(int j = (i - 1) * 9 + 2; j <= i * 9; ++j)
			addSingleEdge(j - 1, j);
			
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			int w;
			scanf("%1d", &w);
			if(w > 0)
				addEdge(i, j, w);
		}
	}
	
	Matrix base = Graph, ans(M, M);
	
	for(int i = 1; i <= M; ++i)
		ans.data[i][i] = 1;
		
	while(T) {
		if(T & 1)
			ans = ans * base;
		
		base = base * base;
		
		T = T >> 1;
	}
	
	std::cout << ans.data[1][(N - 1) * 9 + 1] << std::flush;
	
	return 0;
}
