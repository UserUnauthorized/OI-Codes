//Luogu - P6348
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 5e5 + 5;
typedef array<int, maxN> ARRAY;
class GRAPH{
public:
	struct _EDGE_{
		int to;
		int next;
		int weight;
	};
	typedef GRAPH::_EDGE_ EDGE;
private:
	int _cnt_;
	GRAPH::_EDGE_ _edge_[maxN << 3];
	int _head_[maxN << 3];
public:
	GRAPH():_cnt_(0),_edge_(),_head_(){};
	
	void operator()(int _u_, int _v_, int _w_){
		this->_edge_[++cnt].to = _v_;
		this->_edge_[cnt].next = this->_head_[_u_];
		this->_edge_[cnt].weight = _w_;
		this->_head_[_u_] = cnt;
	}
	
	int operator()(int _x_) const{
		return this->_head_[_x_];
	}
	
	const GRAPH::_EDGE_& operator[](int _x_) const{
		return this->_edge_[_x_];
	}
} edge;

struct STATUS{
	int dis;
	int u;
	
	bool operator>(const STATUS &Object) const{
		return this->dis > Object.dis;
	}
};

class INTREE{
public:
	void build(int n_,ARRAY &idArray);
	void connect(int l, int r, int nodeId);
private:
	int _n_;
	void build_(int id, int l, int r, ARRAY &pos);
	void connect_(int id, int l, int r, int queryL, int queryR, int nodeId);
} inTree;

class OUTTREE{
public:
	void build(int n_,ARRAY &idArray);
	void connect(int l, int r, int nodeId);
private:
	int _n_;
	int _base_;
	void build_(int id, int l, int r, ARRAY &pos);
	void connect_(int id, int l, int r, int queryL, int queryR, int nodeId);
} outTree;

int n,m,P;

array<int, maxN * 10> dis;
array<bool, maxN * 10> vis;
ARRAY inId,outId;

void init();
void dijkstra();

int main(){
	init();
}

void init(){
	cin >> n >> m >> P;
	
	inTree.build(n,inId);
	outTree.build(n,outId);
}

void INTREE::build(int n_,ARRAY &idArray){
	_n_ = n_;
	this->build_(1,1,_n_,idArray);
}

void INTREE::build_(int id, int l, int r, ARRAY &pos){
	if(l == r){
		pos[r] = id;
		return;
	}
	
	int mid((l + r) >> 1);
	
	this->build_(id << 1, l, mid, pos);
	this->build_(id << 1|1, mid + 1, r, pos);
	
	edge(id << 1, id, 0);
	edge(id << 1|1, id, 0);
}

void INTREE::connect(int l, int r, int nodeId){
	this->connect_(1,1,_n_,nodeId);
}

void INTREE::connect_(int id, int l, int r, int queryL, int queryR, int nodeId){
	if(queryL <= l && r <= queryR){
		edge(id, nodeId, 1);
		return;
	}
	
	int mid((l + r) >> 1);
	
	if(queryL <= mid)
		this->connect_(id << 1, l, mid, queryL, queryR, nodeId);
	if(queryR > mid)
		this->connect_(id << 1|1, mid + 1, r, queryL, queryR, nodeId);
}

void OUTTREE::build(int n_,ARRAY &idArray){
	_n_ = n_;
	_base_ = _n_ << 2;
	this->build_(1,1,_n_,idArray);
}

void OUTTREE::build_(int id, int l, int r, ARRAY &pos){
	if(l == r){
		pos[r] = id + _base_;
		edge(id + _base_, id, 0);
		return;
	}
	
	int mid((l + r) >> 1);
	
	this->build_(id << 1, l, mid, pos);
	this->build_(id << 1|1, mid + 1, r, pos);
	
	edge(id << 1 + _base_, id + _base_, 0);
	edge(id << 1|1 + _base_, id + _base_, 0);
}

void OUTTREE::connect(int l, int r, int nodeId){
	this->connect_(1,1,_n_,l,r,nodeId);
}

void OUTTREE::connect_(int id, int l, int r, int queryL, int queryR, int nodeId){
	
}

void dijkstra(){
	
}
