//Luogu - P6348
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 6e5 + 5;
typedef array<int, maxN << 2> ARRAY;

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

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

class GRAPH{
public:
	struct _EDGE_{
		int to;
		int next;
		int weight;
	};
private:
	int _cnt_;
	GRAPH::_EDGE_ _edge_[4200010];
	int _head_[maxN << 6];
public:
	GRAPH():_cnt_(0),_edge_(),_head_(){};
	
	void operator()(int _u_, int _v_, int _w_){
		this->_edge_[++_cnt_].to = _v_;
		this->_edge_[_cnt_].next = this->_head_[_u_];
		this->_edge_[_cnt_].weight = _w_;
		this->_head_[_u_] = _cnt_;
	}
	
	int operator()(int _x_) const{
		return this->_head_[_x_];
	}
	
	const GRAPH::_EDGE_& operator[](int _x_) const{
		return this->_edge_[_x_];
	}
} edge;
typedef GRAPH::_EDGE_ EDGE;

struct STATUS{
	int dis;
	int u;
	
	STATUS():dis(0),u(0){};
	STATUS(int _dis_, int _u_):dis(_dis_),u(_u_){};
	
	bool operator>(const STATUS &Object) const{
		return this->dis > Object.dis;
	}
};

class OUTTREE{
public:
	void build(int n_,ARRAY &idArray);
	void connect(int l, int r, int nodeId);
private:
	int _n_;
	void build_(int id, int l, int r, ARRAY &pos);
	void connect_(int id, int l, int r, int queryL, int queryR, int nodeId);
} outTree;

class INTREE{
public:
	void build(int n_,ARRAY &idArray);
	void connect(int l, int r, int nodeId);
private:
	int _n_;
	int _base_;
	void build_(int id, int l, int r, ARRAY &pos);
	void connect_(int id, int l, int r, int queryL, int queryR, int nodeId);
} inTree;

int n,m,P,count;

array<int, maxN << 6> dis;
array<bool, maxN << 6> vis;
ARRAY inId,outId;

void init();
void dijkstra(int x);

int main(){
	init();
	dijkstra(outId[P]);
	for(int i = 1; i <= n; ++i)
		cout << dis[outId[i]] << "\n";
	return 0;
}

void init(){
	cin >> n >> m >> P;
	
	outTree.build(n,outId);
	inTree.build(n,inId);
	
	int count = maxN * 10;
	for(int i = 0; i < m; ++i){
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		
		outTree.connect(a,b,++count);
		inTree.connect(c,d,count);
		
		outTree.connect(c,d,++count);
		inTree.connect(a,b,count);
	}
}

void OUTTREE::build(int n_,ARRAY &idArray){
	_n_ = n_;
	this->build_(1,1,_n_,idArray);
}

void OUTTREE::build_(int id, int l, int r, ARRAY &pos){
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

void OUTTREE::connect(int l, int r, int nodeId){
	this->connect_(1,1,_n_,l,r,nodeId);
}

void OUTTREE::connect_(int id, int l, int r, int queryL, int queryR, int nodeId){
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

void INTREE::build(int n_,ARRAY &idArray){
	_n_ = n_;
	_base_ = maxN * 5;
	this->build_(1,1,_n_,idArray);
}

void INTREE::build_(int id, int l, int r, ARRAY &pos){
	if(l == r){
		pos[r] = id + _base_;
		edge(id + _base_, id, 0);
		return;
	}
	
	int mid((l + r) >> 1);
	
	this->build_(id << 1, l, mid, pos);
	this->build_(id << 1|1, mid + 1, r, pos);
	
	edge((id << 1) + _base_, id + _base_, 0);
	edge((id << 1|1) + _base_, id + _base_, 0);
}

void INTREE::connect(int l, int r, int nodeId){
	this->connect_(1,1,_n_,l,r,nodeId);
}

void INTREE::connect_(int id, int l, int r, int queryL, int queryR, int nodeId){
	if(queryL <= l && r <= queryR){
		edge(nodeId, id + _base_, 0);
		return;
	}
	
	int mid((l + r) >> 1);
	
	if(queryL <= mid)
		this->connect_(id << 1, l, mid, queryL, queryR, nodeId);
	if(queryR > mid)
		this->connect_(id << 1|1, mid + 1, r, queryL, queryR, nodeId);
}

void dijkstra(int x){
	dis.fill(INT_MAX);
	priority_queue<STATUS, vector<STATUS>, greater<STATUS> > que;
	
	dis[x] = 0;
	que.emplace(0,x);
	
	while(!que.empty()){
		STATUS const &s = que.top();
		que.pop();
		if(vis[s.u]) continue;
		
		vis[s.u] = true;
		for(int i = edge(s.u); i != 0; i = edge[i].next){
			EDGE const &e = edge[i];
			
			if(dis[e.to] > dis[s.u] + e.weight){
				dis[e.to] = dis[s.u] + e.weight;
				if(!vis[e.to])
					que.emplace(dis[e.to],e.to);
			}
		}
	}
}
