//HZ - 51.7
//Luogu - P4390
#include<bits/stdc++.h>

typedef int valueType;
typedef int sizeType;
typedef std::vector<valueType> ValueVector;

constexpr sizeType maxN = 2e5 + 5;

class TreeArray{
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
		pos = pos + shifting;
		
		if(pos < 1)
			return;
		
		data[pos] += key;
		
		while(pos < size) {
			tree[pos] += key;
			pos += lowBit(pos);
		}
	}
	
	valueType sum(sizeType pos) const {
//		pos = pos + shifting;
		if(pos < 1)
			return 0;
		
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

struct Operate {
	int type;
	
	valueType x;
	valueType y;
	valueType stamp;
	valueType value;
	valueType id;
	
	Operate() = default;
	
	Operate(int _type_, valueType _x_, valueType _y_, valueType s, valueType v, valueType i) : type(_type_), x(_x_), y(_y_), stamp(s), value(v), id(i){};
};

typedef const Operate &OperateReference;
typedef std::function<bool(OperateReference, OperateReference)> Comparator;
typedef std::vector<Operate> OperVector;

Comparator compare = [](OperateReference a, OperateReference b) -> bool {
	if(a.x != b.x)
		return a.x < b.x;
	
	if(a.y != b.y)
		return a.y < b.y;
		
	if(a.stamp != b.stamp)
		return a.stamp < b.stamp;
		
	return a.value < b.value; /* TAG */
};

valueType W_;
valueType const &W = W_;

OperVector operate;

void solve(int l, int r);

int main() {
	int zero;
	
	std::cin >> zero >> W_;
	
	operate.reserve(maxN);
	
	int Count = 0, QueryCount = 0, ModifyCount = 0;
	
	while(true) {
		int order;
		
		std::cin >> order;
		
		if(order == 3)
			break;
			
		++Count;
		
		if(order == 1) {
			++ModifyCount;
			
			valueType x, y, a;
			
			std::cin >> x >> y >> a;
			
			operate.emplace_back(0, x, y, ModifyCount, a, ModifyCount);
		} else if (order == 2) {
			++QueryCount;
			
			valueType x1, y1, x2, y2;
			
			std::cin >> x1 >> y1 >> x2 >> y2;
			
			operate.emplace_back(1, x2, y2, ModifyCount, 0, QueryCount);
			operate.emplace_back(-1, x1 - 1, y2, ModifyCount, 0, QueryCount);
			operate.emplace_back(-1, x2, y1 - 1, ModifyCount, 0, QueryCount);
			operate.emplace_back(1, x1 - 1, y1 - 1, ModifyCount, 0, QueryCount);
		}
	}
	
	operate.shrink_to_fit();
	std::sort(operate.begin(), operate.end(), compare);
	
	int const M = operate.size();
	
	solve(0, M - 1); 
}

void solve(int l, int r) {
	
}
