//HZ - 51.6
//Luogu - P3810
//LOJ - 112
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
typedef int sizeType;
typedef std::vector<valueType> ValueVector;

class TreeArray{
private:
	ValueVector data;
	
	ValueVector tree;
	
	sizeType size;

	static valueType lowBit(valueType x) {
		return x & -x;
	}

public:
	TreeArray() : data(0, 0), tree(0, 0), size(0) {};
	
	void resize(sizeType N) {
		size = N;
		
		data.resize(size, 0);
		tree.resize(size, 0);
	}
	
	void set(sizeType pos, valueType key) {
		valueType const difference = key - data[pos];
		
		if(difference == 0)
			return;
		
		data[pos] = key;
		
		while(pos < size) {
			tree[pos] += difference;
			pos += lowBit(pos);
		}
	}
	
	void insert(sizeType pos, valueType key) {
		data[pos] += key;
		
		while(pos < size) {
			tree[pos] += key;
			pos += lowBit(pos);
		}
	}
	
	valueType sum(sizeType pos) const {
		valueType result = 0;
		
		while(pos > 0) {
			result += tree[pos];
			pos -= lowBit(pos);;
		}

		return result;
	}
};

class ReversibleTreeArray{
public:
	typedef TreeArray container;
	typedef std::queue<sizeType> Queue;
	
private:
	container data;
	Queue tag;
	
public:
	ReversibleTreeArray() : data(), tag() {};
	
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

ReversibleTreeArray exist;

struct Element {
	valueType a, b, c, count, result;
	
	Element() = default;
	
	Element(valueType _a_, valueType _b_, valueType _c_) : a(_a_), b(_b_), c(_c_) {};
	
	Element(valueType _a_, valueType _b_, valueType _c_, valueType cnt) : a(_a_), b(_b_), c(_c_), count(cnt) {};
		
	bool operator==(Element const &e) {
		return a == e.a && b == e.b && c == e.c;
	}
	
	bool operator!=(Element const &e) {
		return a != e.a || b != e.b || c != e.c;
	}
	
	friend std::ostream &operator<<(std::ostream &os, Element const &e) {
		os << e.a << ' ' << e.b << ' ' << e.c << std::endl;
		
		return os;
	}
};

typedef const Element &ElementReference;

const std::function<bool(ElementReference, ElementReference)> compareA = [](ElementReference a, ElementReference b) ->bool {
	if(a.a != b.a)
		return a.a < b.a;
		
	if(a.b != b.b)
		return a.b < b.b;
	
	return a.c < b.c;
};

const std::function<bool(ElementReference, ElementReference)> compareB = [](ElementReference a, ElementReference b) ->bool {
	if(a.b != b.b)
		return a.b < b.b;
	
	return a.c < b.c;
};

typedef std::vector<Element> ElementVector;

valueType N_, K_, M_;

valueType const &N = N_, &K = K_, &M = M_;

ElementVector element;

void solve(sizeType l, sizeType r);

int main() {
	std::cin >> N_ >> K_;
	
	ElementVector source(N);
	exist.resize(K + 10);
	
	for(auto &iter : source)
		std::cin >> iter.a >> iter.b >> iter.c;
		
	std::sort(source.begin(), source.end(), compareA);
	element.reserve(N);

	for(auto iter : source) {
		if(element.empty() || iter != element.back())
			element.push_back(iter);
		
		++element.back().count;
		
		element.back().result = 0;
	}
	
	M_ = element.size();
	element.shrink_to_fit();
	
	solve(0, M - 1);

	ValueVector ans(N, 0);
	
	for(int i = 0; i < M; ++i)
		ans[element[i].result + element[i].count - 1] += element[i].count;
	
	for(auto const &iter : ans)
		std::cout << iter << std::endl;
}

void solve(sizeType l, sizeType r) {
	if(l == r)
		return;
	
	sizeType const mid = (l + r) >> 1;
	
	solve(l, mid);
	solve(mid + 1, r);

	std::sort(element.begin() + l, element.begin() + mid + 1, compareB);
	std::sort(element.begin() + mid + 1, element.begin() + r + 1, compareB);
	
	int left = l;
	int right = mid + 1;

	exist.beginRecord();
		
	while(right <= r) {
		while(left <= mid && element[left].b <= element[right].b) {
			exist.insert(element[left].c, element[left].count);

			++left;
		}
		
		element[right].result += exist.sum(element[right].c);
		
		++right;
	}
	
	exist.endRecord();
}
