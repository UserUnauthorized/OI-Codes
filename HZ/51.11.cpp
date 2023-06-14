//HZ - 51.11
//Luogu - P4093
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
typedef std::vector<valueType> ValueVector;

constexpr int maxN = 1e5 + 5;

class TreeArray{
public:
	typedef int sizeType;
	
private:
	ValueVector data;
	
	ValueVector tree;
	
	sizeType size;

	static const sizeType constexpr shifting = 5;

	static valueType lowBit(valueType x) {
		return x & -x;
	}

public:
	TreeArray() : data(0, 0), tree(0, 0), size(0) {};
	
	void resize(sizeType N) {
		size = N + shifting;
		
		data.resize(size, 0);
		tree.resize(size, 0);
	}
	
	void set(sizeType pos, valueType key) {
		pos = pos + shifting;
		
		if(pos < 1)
			return;
		
		data[pos] = key;
		
		while(pos < size) {
			tree[pos] = key;
			pos += lowBit(pos);
		}
	}
	
	void insert(sizeType pos, valueType key) {
		pos = pos + shifting;
		
		if(pos < 1)
			return;
		
		data[pos] = std::max(data[pos], key);
		
		while(pos < size) {
//			tree[pos] += key;
			tree[pos] = std::max(tree[pos], key);
			pos += lowBit(pos);
		}
	}
	
	valueType sum(sizeType pos) const {
		pos = pos + shifting;
		if(pos < 1)
			return 0;
		
		valueType result = 0;
		
		while(pos > 0) {
			result = std::max(result, tree[pos]);
			pos -= lowBit(pos);;
		}

		return result;
	}
};

class ReversibleTreeArray{
public:
	typedef TreeArray container;
	typedef container::sizeType sizeType;
	typedef std::queue<sizeType> Queue;
	
private:
	container data;
	Queue tag;
	
public:
	ReversibleTreeArray() : data(), tag() {};
	
	ReversibleTreeArray(sizeType N) : data(), tag() {
		resize(N);
	};
	
	void resize(sizeType N) {
		data.resize(N);
	}
	
	void beginRecord() {
		while(!tag.empty())
			tag.pop();
	}
	
	void endRecord() {
		while(!tag.empty()) {
			data.set(tag.front(), 0);
			
			tag.pop();
		}
	}
	
	void set(sizeType pos, valueType key) {
		tag.push(pos);
		
		data.set(pos, key);
	}
	
	void insert(sizeType pos, valueType key) {
		tag.push(pos);
		
		data.insert(pos, key);
	}
	
	valueType sum(sizeType pos) const {
		return data.sum(pos);
	}
};

ReversibleTreeArray exist(maxN);

ValueVector source, dp, min, max, value;

typedef std::function<bool(valueType, valueType)> compareFunction;

compareFunction compareS = [] (valueType a, valueType b) ->bool {
	return source[a] < source[b];
};

compareFunction compareMin = [] (valueType a, valueType b) ->bool {
	return min[a] < min[b];
};

compareFunction compareMax = [] (valueType a, valueType b) ->bool {
	return max[a] < max[b];
};

void solve(int l, int r);

int main() {
	valueType N, M;
	
	std::cin >> N >> M;
	
	source.resize(N + 1, 0);
	value.resize(N + 1);
	
	std::iota(value.begin(), value.end(), 0);
	
	for(int i = 1; i <= N; ++i)
		std::cin >> source[i];
		
	min = source;
	max = source;
	
	for(int i = 1; i <= M; ++i) {
		int x, y;
		
		std::cin >> x >> y;
		
		min[x] = std::min(min[x], y);
		max[x] = std::max(max[x], y);
	}

	dp.resize(N + 1, 0);
	dp[1] = 1;
//	debug(dp);
	solve(1, N);
	
	int result = 0;
	
	for(int i = 1; i <= N; ++i)
		result = std::max(result, dp[i]);
		
	std::cout << result << std::flush;
	
	return 0;
}

void solve(int l, int r) {
	if(l == r)
		return;
		
	int const mid = (l + r) >> 1;
	
	solve(l, mid);
	
	std::sort(value.begin() + l, value.begin() + mid + 1, compareS);
	std::sort(value.begin() + mid + 1, value.begin() + r + 1, compareMin);
	
	int left = l;
	int right = mid + 1;
	
	exist.beginRecord();
	
	while(right <= r) {
		while(left <= mid && source[value[left]] <= min[value[right]]) {
			exist.insert(max[value[left]], dp[value[left]]);
			
			++left;
		}
		
		dp[value[right]] = std::max(dp[value[right]], exist.sum(source[value[right]]) + 1);
		
		++right;
	}
	
	exist.endRecord();
	
	std::sort(value.begin() + mid + 1, value.begin() + r + 1);
	
	solve(mid + 1, r);
}
