//Luogu - P2633
#include<bits/stdc++.h>
typedef int valueType;
constexpr int maxN = 1e5 + 5;
typedef std::array<valueType, maxN> ARRAY;
typedef std::vector<valueType> VECTOR;

int L_, R_, N_, M_;
const int &L = L_, &R = R_, &N = N_, &M = M_;

struct SEGNODE{
	typedef SEGNODE self;
	typedef self* pointer;
	typedef ::valueType valueType;
	
	pointer leftSon, rightSon;
	self::valueType count;
	
	SEGNODE():leftSon(NULL), rightSon(NULL), count(0){};
	
	void update(){
		this->count = 0;
		
		if(this->leftSon != NULL)
			this->count += this->leftSon->count;
			
		if(this->rightSon != NULL)
			this->count += this->rightSon->count;
	}
};

struct EDGE {
    int next;
    int to;
    
    EDGE():next(0), to(0){};
    
    EDGE(int _next_, int _to_):next(_next_), to(_to_){};
} edge[maxN];

typedef SEGNODE::pointer pointer;
typedef std::array<pointer, maxN> PointerArray;

pointer newNode();

pointer build(valueType l, valueType r);
pointer insert(const pointer &current, valueType nodeL, valueType nodeR, valueType pos);
valueType query(pointer leftNode, pointer rightNode, valueType l, valueType r, valueType k);
valueType query(valueType l, valueType r, valueType k);

ARRAY source;
PointerArray tree;
VECTOR point;

void init();

int main(){
	init();
	
	for(int i = 0; i < M; ++i){
		int l, r, k;
		std::cin >> l >> r >> k;
		std::cout << point[query(l, r, k)] << '\n';
	}
	
	return 0;
}

void init(){
	std::cin >> N_ >> M_;
	
	for(int i = 1; i <= N; ++i)
		std::cin >> source[i];
		
	point.assign(source.begin() + 1, source.begin() + N + 1);
	point.push_back(INT_MIN);
	sort(point.begin(), point.end());
	point.erase(unique(point.begin(), point.end()), point.end());
	
	L_ = 1;
	R_ = point.size() - 1;
	
	for(int i = 1; i <= N; ++i)
		source[i] = distance(point.begin(), lower_bound(point.begin(), point.end(), source[i]));

	tree[0] = build(L, R);
}

pointer build(valueType l, valueType r){
	pointer current = newNode();
	
	if(l == r){
		current->count = 0;
		return current;
	}
	
	int const mid = (l + r) >> 1;
	
	current->leftSon = build(l, mid);
	current->rightSon = build(mid + 1, r);
		
	return current;
}

pointer insert(const pointer &current, valueType nodeL, valueType nodeR, valueType pos){
	pointer result = newNode();
	*result = *current;

	if(nodeL == nodeR){
		++result->count;
		return result;
	}
	
	int const mid = (nodeL + nodeR) >> 1;
	
	if(pos <= mid)
		result->leftSon = insert(current->leftSon, nodeL, mid, pos);
	else
		result->rightSon = insert(current->rightSon, mid + 1, nodeR, pos);
	
	result->update();
	
	return result;
}

valueType query(valueType l, valueType r, valueType k){
	return query(tree[l - 1], tree[r], L, R, k);
}

valueType query(pointer leftNode, pointer rightNode, valueType l, valueType r, valueType k){
	if(l == r)
		return r;
	
	int const mid = (l + r) >> 1;
	
	int leftCount = 0;
	
	if(rightNode->leftSon != NULL)
		leftCount += rightNode->leftSon->count;
	
	if(leftNode->leftSon != NULL)
		leftCount -= leftNode->leftSon->count;
	
	if(k <= leftCount)
		return query(leftNode->leftSon, rightNode->leftSon, l, mid, k);
	else
		return query(leftNode->rightSon, rightNode->rightSon, mid + 1, r, k - leftCount);
}

pointer newNode(){
	static SEGNODE pool[maxN << 5], *allocp = pool - 1;
	return ++allocp;
}
