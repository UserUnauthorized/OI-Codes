//HZ - 28.10
//Luogu - P5025
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 5e5 + 5, MOD = 1e9 + 7;
typedef long long posType;
typedef unsigned int numType;
array<posType,maxN << 3> leftBound,rightBound;
array<numType,maxN> inId,outId;
array<numType,maxN << 3> belong,size;
array<bool,maxN << 3> vis;

vector<int> edge[maxN << 3];

struct NODE{
	posType pos;
	posType left;
	posType right;
	
	NODE():pos(LONG_LONG_MAX),left(LONG_LONG_MIN),right(LONG_LONG_MAX){};
	NODE(int _pos_, int _left_, int _right_):pos(_pos_),left(_left_),right(_right_){};
} node[maxN];

class OUTREE{
public:
	void build(int n_, array<numType,maxN> &idArray);
	void build_(int id, int l, int r, array<numType,maxN> &pos);
private:
	int _n_;
} outTree;

class INTREE{
public:
	void build(int n_, array<numType,maxN> &idArray);
	void build_(int id, int l, int r, array<numType,maxN> &pos);
	void connect(int l, int r, int nodeId);
	void connect_(int id, int l, int r, int queryL, int queryR, int nodeId);
private:
	int _n_;
	static const int _base_ = maxN << 2;
} inTree;

int N;

void init();
void tarjan(int x);
void dfs(int x);

int main(){
	init();
}

void init(){
	cin >> n;
	
	outTree.build(n,outId);
	inTree.build(n,inId);
}

void OUTREE::build(int n_, array<numType,maxN> &idArray){
	this->_n_ = n_;
	this->build_(1,1,_n_,idArray);
}

void OUTREE::build_(int id, int l, int r, array<numType,maxN> &pos){
	if(l == r){
		pos[r] = id;
		return;
	}
	
	int mid((l + r) >> 1);
	
	this->build_(id << 1, l, mid, pos);
	this->build_(id << 1|1, mid + 1, r, pos);
	
	edge[id << 1].emplace_back(id);
	edge[id << 1|1].emplace_back(id);
}

void INTREE::build(int n_,ARRAY &idArray){
	_n_ = n_;
	this->build_(1,1,_n_,idArray);
}

void INTREE::build_(int id, int l, int r, ARRAY &pos){
	if(l == r){
		pos[r] = id + _base_;
		edge[id + _base_].emplace_back(id,0);
		return;
	}
	
	int mid((l + r) >> 1);
	
	this->build_(id << 1, l, mid, pos);
	this->build_(id << 1|1, mid + 1, r, pos);
	
	edge[id + _base_].emplace_back((id << 1) + _base_, 0);
	edge[id + _base_].emplace_back((id << 1|1) + _base_, 0);
}

void INTREE::connect(int l, int r, int nodeId){
	this->connect_(1,1,_n_,l,r,nodeId);
}

void INTREE::connect_(int id, int l, int r, int queryL, int queryR, int nodeId){
	if(queryL <= l && r <= queryR){
		edge[nodeId].emplace_back(id + _base_, 0);
		return;
	}
	
	int mid((l + r) >> 1);
	
	if(queryL <= mid)
		this->connect_(id << 1, l, mid, queryL, queryR, nodeId);
	if(queryR > mid)
		this->connect_(id << 1|1, mid + 1, r, queryL, queryR, nodeId);
}
