//HZ - 35.8
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
typedef size_t sizeType;
typedef long double realType;
typedef std::vector<realType> realVector;
typedef std::vector<valueType> valueVector;

int main() {
	int N;
	
	std::cin >> N;
	
	valueVector source(N);
	
	for(auto &iter : source)
		std::cin >> iter;
		
	valueVector point(source);
	
	point.push_back(INT_MIN);
	std::sort(point.begin(), point.end());
	point.erase(std::unique(point.begin(), point.end()), point.end());
	
	sizeType const S = point.size();
	
	for(auto &iter : source)
		iter = std::distance(point.begin(), std::lower_bound(point.begin(), point.end(), iter));
		
	valueVector count(S, 0), sum(S);
	
	for(auto const &iter : source)
		++count[iter];
		
	std::partial_sum(count.begin(), count.end(), sum.begin());
	debug(N, S, point, source, count, sum);
	realVector factorial(S, 1);
	
	for(sizeType i = 1; i < S; ++i)
		factorial[i] = i * factorial[i - 1];
	debug(S, factorial);
	typedef std::function<realType(valueType, valueType)> NumberFunction;
	
	NumberFunction A = [&factorial] (valueType n, valueType m) -> realType {
		return factorial[n] / factorial[n - m];
	};
	
	NumberFunction C = [&factorial] (valueType n, valueType m) -> realType {
		if(m == 0)
			return 1;
		
		return factorial[n] / factorial[n - m] / factorial[m];
	};
	
	realType ans = 0;
	
	for(sizeType i = 1; i < S; ++i)
		for(valueType j = 0; j <= sum[i - 1]; ++j) {
			ans += (realType) count[i] * (N - j) * C(sum[i - 1], j) * A(j, j) * A(sum[i - 1] - j, sum[i - 1] - j) * A(N - sum[i - 1], N - sum[i - 1]);
			debug(i, j, ans);
		}
			
			
	ans /= A(N, N);
	
	std::cout << std::setprecision(2) << std::fixed << ans << std::flush;
	
	return 0;
}
