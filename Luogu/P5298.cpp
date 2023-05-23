//HZ - 43.10
//Luogu - P5298
#include<bits/stdc++.h>

typedef long long valueType;
typedef size_t sizeType;

constexpr valueType MOD = 998244353, maxN = 3e5 + 5;

const valueType inverse(valueType x) {
	if(x == 1)
		return 1;
	
	return (MOD - MOD / x) * inverse(MOD % x) % MOD;
}

const valueType P = inverse(10000);

struct NODE{
	typedef NODE self;
	typedef self* pointer;
	typedef ::valueType valueType;
	typedef ::sizeType sizeType;
	
	sizeType left, right, mid;
	pointer leftSon, rightSon;
	valueType data, lazy;
	
	NODE() : left(0), right(0), mid(0), leftSon(nullptr), rightSon(nullptr), data(0), lazy(1) {};
	
	NODE(sizeType l, sizeType r) : left(l), right(r), mid((l + r) >> 1),  leftSon(nullptr), rightSon(nullptr), data(0), lazy(1) {};
	
	NODE(sizeType l, sizeType r, valueType data) : left(l), right(r), mid((l + r) >> 1),  leftSon(nullptr), rightSon(nullptr), data(data), lazy(1) {};
	
	bool isLeaf() const {
		return left == right;
	}
	
	void push() {
		if(this->lazy != 1) {
			if(this->leftSon != nullptr) {
				leftSon->data = (leftSon->data * this->lazy) % MOD;
				leftSon->lazy = (leftSon->lazy * this->lazy) % MOD;
			}
			
			if(this->rightSon != nullptr) {
				rightSon->data = (rightSon->data * this->lazy) % MOD;
				rightSon->lazy = (rightSon->lazy * this->lazy) % MOD;
			}
			
			this->lazy = 1;
		}
	}
	
	void update() {
		if(isLeaf())
			return;
		
		this->data = (leftSon != nullptr ? leftSon->data : 0) + (rightSon != nullptr ? rightSon->data : 0);
	}
};

typedef NODE::pointer pointer;

pointer allocate() {
	return new NODE();
}

pointer allocate(sizeType l, sizeType r) {
	return new NODE(l, r);
}

pointer allocate(sizeType l, sizeType r, valueType data) {
	return new NODE(l, r, data);
}

void insert(pointer &current, sizeType pos, valueType data, sizeType l, sizeType r) {
	if(l == r) {
		current = allocate(l, r, data);
		return;
	}
	
	current = allocate(l, r);
	
	if(pos <= current->mid)
		insert(current->leftSon, pos, data, l, current->mid);
	else
		insert(current->rightSon, pos, data, current->mid + 1, r);
		
	current->update();
}

pointer merge(const pointer &left, const pointer &right, valueType &leftSum, valueType &rightSum, const valueType &p) {
	if(left == nullptr && right == nullptr)
		return nullptr;
	
	if(left == nullptr && right != nullptr) {
		rightSum = (rightSum + right->data) % MOD;
		
		right->data = (right->data * ((p * leftSum) + (MOD + 1 - p) * (MOD + 1 - leftSum) % MOD)) % MOD;
		right->lazy = (right->lazy * ((p * leftSum) + (MOD + 1 - p) * (MOD + 1 - leftSum) % MOD)) % MOD;
		
		return right;
	}
	
	if(right == nullptr && left != nullptr) {
		leftSum = (leftSum + left->data) % MOD;
		
		left->data = (left->data * ((p * rightSum) + (MOD + 1 - p) * (MOD + 1 - rightSum) % MOD)) % MOD;
		left->lazy = (left->lazy * ((p * rightSum) + (MOD + 1 - p) * (MOD + 1 - rightSum) % MOD)) % MOD;
		
		return left;
	}
	
	left->push();
	right->push();
	
	left->leftSon = merge(left->leftSon, right->leftSon, leftSum, rightSum, p);
	left->rightSon = merge(left->rightSon, right->rightSon, leftSum, rightSum, p);
	
	left->update();
	
	return left;
}

pointer merge(const pointer &left, const pointer &right, const valueType &p) {
	valueType leftSum = 0, rightSum = 0;
	
	return merge(left, right, leftSum, rightSum, p);
}

sizeType L_, R_;
sizeType const &L = L_, &R = R_;

std::array<pointer, maxN> tree;
std::array<std::list<int>, maxN> son;
std::bitset<maxN> isLeaf;

std::array<valueType, maxN> source;
std::vector<valueType> point;

void dfs(int x);

void calc(const pointer &current, valueType &count, valueType &ans);

int main() {
	valueType N;
	
	std::cin >> N;
	
	isLeaf.set();
	
	for(int i = 1; i <= N; ++i) {
		int fa;
		
		std::cin >> fa;
		
		isLeaf[fa] = false;
		
		son[fa].emplace_back(i);
	}
	
	point.reserve(N + 1);
	
	for(int i = 1; i <= N; ++i) {
		std::cin >> source[i];
		
		if(isLeaf[i])
			point.emplace_back(source[i]);
	}
		
	point.emplace_back(INT_MIN);
	std::sort(point.begin(), point.end());
	point.erase(std::unique(point.begin(), point.end()), point.end());
	point.shrink_to_fit();
	
	L_ = 1;
	R_ = point.size();
	
	for(int i = 1; i <= N; ++i)
		if(isLeaf[i])
			source[i] = std::distance(point.begin(), std::lower_bound(point.begin(), point.end(), source[i]));
		else
			source[i] = (source[i] * P) % MOD;
			
	dfs(1);
	
	valueType count = 0, ans = 0;
	
	calc(tree[1], count, ans);
	
	std::cout << ans << std::flush;
	
	return 0;
}

void dfs(int x) {
	if(isLeaf[x]) {
		insert(tree[x], source[x], 1, L, R);
		
		return;
	}
	
	for(auto const &iter : son[x])
		dfs(iter);
		
	for(auto const &iter : son[x]) {
		if(tree[x] == nullptr) {
			tree[x] = tree[iter];
		} else {
			tree[x] = merge(tree[x], tree[iter], source[x]);
		}
	}
}

void calc(const pointer &current, valueType &count, valueType &ans) {
	if(current == nullptr)
		return;
		
	if(current->isLeaf()) {
		++count;
		
		ans = (ans + (count * point[current->left] * current->data) % MOD * current->data) % MOD;
	
		return;
	}
	
	current->push();
	
	calc(current->leftSon, count, ans);
	calc(current->rightSon, count, ans);
}
