//LOJ - 2874
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
typedef std::vector<valueType> ValueVector;

ValueVector belong;

struct Query{
	int l;
	int r;
	int id;

	Query():l(-1), r(-1), id(-1){};
	Query(int _l_, int _r_, int i):l(_l_), r(_r_), id(i){};
	
	bool operator<(Query const &Object) const{
		if(belong[this->l] != belong[Object.l])
			return this->l < Object.l;
			
		return this->r < Object.r;
	}
};

typedef std::vector<Query> QueryVector;

class Recorder {
private:
	std::queue<int> tag;
	
public:
	Recorder() : tag(){};
	
	void prepare() {
		while(!tag.empty()) {
			tag.pop();
		}
	}
	
	void push(valueType x) {
		tag.push(x);
	}
	
	bool empty() const {
		return tag.empty();
	}
	
	valueType pop() {
		valueType const result = tag.front();
		
		tag.pop();
		
		return result;
	}
};

class ModifyRecorder{
private:
	valueType size;
	
	ValueVector data;
	
public:
	ModifyRecorder(valueType N) : size(N), data(N, 0){};
	
	valueType add(valueType pos, valueType value) {
		data[pos] = std::max(data[pos], value);
		
		return data[pos];
	}
	
	valueType add(valueType pos, valueType value, Recorder &rec) {
		if(data[pos] < value) {
			data[pos] = value;
			
			rec.push(pos);
		}
		
		return data[pos];
	}
	
	valueType query(valueType pos) const {
		return data[pos];
	}
	
	void restore(Recorder &rec) {
		while(!rec.empty())
			data[rec.pop()] = 0;
	}
};

int main() {
	valueType N, Q;
	
	std::cin >> N >> Q;
	
	valueType const block = std::ceil(std::sqrt(N)), K = std::ceil((long double) N / block);
	
	ValueVector source(N + 1), leftBound(block + 10, 0), rightBound(block + 10, 0);
	belong.resize(N + 1);
	
	for(int i = 0; i < K; ++i)
		rightBound[i] = (leftBound[i] = i * block + 1) + block - 1;
	
	leftBound[K - 1] = K * block - block + 1;
	rightBound[K - 1] = N;
	
	source[0] = INT_MIN;
	for(int i = 1; i <= N; ++i) {
		std::cin >> source[i];
		belong[i] = (i - 1) / block;
	}
	
	ValueVector point(source);
	
	std::sort(point.begin(), point.end());
	point.erase(std::unique(point.begin(), point.end()), point.end());
	point.shrink_to_fit();
	
	valueType const S = point.size();
	
	for(int i = 1; i <= N; ++i)
		source[i] = std::distance(point.begin(), std::lower_bound(point.begin(), point.end(), source[i]));
	
	QueryVector query(Q);
	
	for(int i = 0; i < Q; ++i) {
		std::cin >> query[i].l >> query[i].r;
		
		query[i].id = i;
	}
	
	ValueVector ans(Q, 0);
	
	std::sort(query.begin(), query.end());
	
	ModifyRecorder temp(S + 10), modify(S + 10);
	
	int nowL = 1, nowR = 0, nowBlock = -1;
	valueType result = 0;
	Recorder record;
	
	for(auto const &iter : query) {
		if(belong[iter.l] == belong[iter.r]) {
			Recorder tempRec;
			
			for(int i = iter.r; i >= iter.l; --i)
				ans[iter.id] = std::max(ans[iter.id], temp.add(source[i], i, tempRec) - i);
				
			temp.restore(tempRec);
				
			continue;
		}
		
		if(belong[iter.l] != nowBlock) {
			nowBlock = belong[iter.l];
			result = 0;
			
			modify.restore(record);
			
			nowL = rightBound[nowBlock]
		}
		
		while(nowR < iter.r) {
			++nowR;
			
			result = std::max(result, modify.add(source[nowR], point[source[nowR]]));
		}
		
		int tempL = nowL;
		valueType nowResult = result;
		
		while(tempL > iter.l) {
			--tempL;
			
			nowResult = std::max(nowResult, modify.add(source[tempL], point[source[tempL]]));
		}
		
		ans[iter.id] = nowResult;
		
		while(tempL < nowL)
			modify.del(source[tempL++]);
	}
	
	for(int i = 0; i < Q; ++i)
		std::cout << ans[i] << '\n';
		
	std::cout << std::flush;
	
	return 0;
}
