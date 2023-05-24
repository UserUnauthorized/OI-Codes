//HZ - 43.7
//Luogu - P4577
#include<bits/stdc++.h>

typedef long long valueType;
typedef size_t sizeType;

constexpr valueType maxN = 2e5 + 5, MIN = INT_MIN >> 1;

struct NODE{
	typedef NODE self;
	typedef self* pointer;
	typedef ::valueType valueType;
	typedef ::sizeType sizeType;
	
	sizeType left, right, mid;
	pointer leftSon, rightSon;
	valueType data, lazy;
	
	NODE() : left(0), right(0), mid(0), leftSon(nullptr), rightSon(nullptr), data(MIN), lazy(0) {};
	
	NODE(sizeType l, sizeType r) : left(l), right(r), mid((l + r) >> 1),  leftSon(nullptr), rightSon(nullptr), data(MIN), lazy(0) {};
	
	NODE(sizeType l, sizeType r, valueType data) : left(l), right(r), mid((l + r) >> 1),  leftSon(nullptr), rightSon(nullptr), data(data), lazy(0) {};
	
	bool isLeaf() const {
		return left == right;
	}
	
	void push() {
		if(this->lazy != 0) {
			if(this->leftSon != nullptr) {
				leftSon->data = leftSon->data + this->lazy;
				leftSon->lazy = leftSon->lazy + this->lazy;
			}
			
			if(this->rightSon != nullptr) {
				rightSon->data = rightSon->data + this->lazy;
				rightSon->lazy = rightSon->lazy + this->lazy;
			}
			
			this->lazy = 0;
		}
	}
	
	void update() {
		if(isLeaf())
			return;
		
		this->data = std::max((leftSon != nullptr ? leftSon->data : MIN), (rightSon != nullptr ? rightSon->data : MIN));
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
	if(l > r)
		return;
	
	if(current == nullptr)
		current = allocate(l, r);
	
	if(l == r) {
		current->data = std::max(current->data, data);
		return;
	}
	
	if(pos <= current->mid)
		insert(current->leftSon, pos, data, l, current->mid);
	else
		insert(current->rightSon, pos, data, current->mid + 1, r);
		
	current->update();
}

valueType query(const pointer &current, sizeType l, sizeType r) {
	if(l <= current->left && current->right <= r)
		return current->data;
		
	if(r <= current->mid)
		return query(current->leftSon, l, r);
	
	if(l > current->mid)
		return query(current->rightSon, l, r);
	
	return std::max(query(current->leftSon, l, r), query(current->rightSon, l, r));
}

pointer merge(const pointer &left, const pointer &right, valueType &leftMax, valueType &rightMax) {
	if(left == nullptr && right == nullptr)
		return nullptr;
	
	if(left == nullptr && right != nullptr) {
		rightMax = std::max(rightMax, right->data);
		
		right->data = right->data + leftMax;
		right->lazy = right->lazy + leftMax;
		
		return right;
	}
	
	if(right == nullptr && left != nullptr) {
		leftMax = std::max(leftMax, left->data);
		
		left->data = left->data + rightMax;
		left->lazy = left->lazy + rightMax;
		
		return left;
	}
	
	left->push();
	right->push();
	
	left->leftSon = merge(left->leftSon, right->leftSon, leftMax, rightMax);
	left->rightSon = merge(left->rightSon, right->rightSon, leftMax, rightMax);
	
	left->update();
	
	return left;
}

pointer merge(const pointer &left, const pointer &right) {
	valueType leftMax = 0, rightMax = 0;
	
	return merge(left, right, leftMax, rightMax);
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
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	valueType N;
	
	std::cin >> N;
	
	isLeaf.set();
	
	for(int i = 1; i <= N; ++i) {
		std::cin >> source[i];
		
		if(isLeaf[i])
			point.emplace_back(source[i]);
	}
	
	for(int i = 2; i <= N; ++i) {
		int fa;
		
		std::cin >> fa;
		
		isLeaf[fa] = false;
		
		son[fa].emplace_back(i);
	}
	
	point.reserve(N + 1);
	
	
		
	point.emplace_back(INT_MIN);
	std::sort(point.begin(), point.end());
	point.erase(std::unique(point.begin(), point.end()), point.end());
	point.shrink_to_fit();
	
	L_ = 1;
	R_ = point.size();
	
	for(int i = 1; i <= N; ++i)
		source[i] = std::distance(point.begin(), std::lower_bound(point.begin(), point.end(), source[i]));
			
	dfs(1);
	
	valueType const ans = tree[1]->data;
	
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
			tree[x] = merge(tree[x], tree[iter]);
		}
	}
	
	insert(tree[x], source[x], query(tree[x], L, source[x] - 1) + 1, L, R);
}
