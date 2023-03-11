//HZ - 44.2
//Luogu - P3834
//Luogu - SP3946
#include<bits/stdc++.h>
using namespace std;
typedef int valueType;
constexpr int maxN = 2e5 + 5;
typedef array<valueType, maxN> ARRAY;
typedef vector<valueType> VECTOR;

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

typedef SEGNODE::pointer pointer;
typedef array<pointer, maxN> PointerArray;

pointer newNode();

pointer build(valueType l, valueType r);
pointer insert(pointer current, valueType nodeL, valueType nodeR, valueType pos, valueType key);
valueType query(pointer leftNode, pointer rightNode, valueType l, valueType r, valueType k);

ARRAY source;
PointerArray tree;
VECTOR point;

void init();

int main(){
	init();
}

void init(){
	cin >> N_ >> M_;
	
	for(int i = 1; i <= N; ++i)
		cin >> source[i];
		
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
	
}

pointer newNode(){
	static SEGNODE pool[maxN << 5], *allocp = pool - 1;
	return ++allocp;
}
