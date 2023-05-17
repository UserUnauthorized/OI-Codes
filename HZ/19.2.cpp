//HZ - 19.2
//LOJ - 10220
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

long long MOD_;
long long const &MOD = MOD_;

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
	int N;
	
	std::cin >> N >> MOD_;
	
	Matrix ans(1, 2), base(2, 2);
	
	base.data[1][1] = base.data[1][2] = base.data[2][1] = 1;
	base.data[2][2] = 0;
	ans.data[1][2] = ans.data[1][1] = 1;
	
	N = N - 2;
	
	while(N) {
		if(N & 1) ans = ans * base;
		
		base = base * base;
		
		N = N >> 1;
	}
	
	std::cout << ans.data[1][1] << std::flush;
	
	return 0;
}
