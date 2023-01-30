//Luogu - P6348
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 5e5 + 5, maxM = 1e5 + 5;
struct EDGE{
	int to;
	int weight;
	
	EDGE():to(0),weight(0){};
	EDGE(int _to_, int _weight_):to(_to_),weight(_weight_){};
};

struct STATUS{
	int dis;
	int u;
	
	STATUS():dis(0),u(0){};
	STATUS(int _dis_, int _u_):dis(_dis_),u(_u_){};
	
	bool operator>(const STATUS &Object) const{
		return this->dis > Object.dis;
	}
};

typedef std::forward_list<EDGE> EdgeArray;
typedef array<unsigned int, (maxN << 3) + (maxM << 1)> ARRAY;

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

EdgeArray edge[(maxN << 3) + (maxM << 1)];
bitset<(maxN << 3) + (maxM << 1)> vis;
ARRAY dis, inId, outId;

int n,m,P;

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
	//cerr << "=====DEBUG BEGIN=====\n";
	
	outTree.build(n,outId);
	inTree.build(n,inId);
	
	int count = maxN << 3;
	for(int i = 0; i < m; ++i){
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		
		outTree.connect(a,b,++count);
		inTree.connect(c,d,count);
		
		outTree.connect(c,d,++count);
		inTree.connect(a,b,count);
	}
	
	//cerr << "=====DEBUG END=====\n";
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
	
	edge[id << 1].emplace_front(id,0);
	edge[id << 1|1].emplace_front(id,0);
	//cerr << (id << 1) << " " << id << " " << 0 << endl;
	//cerr << (id << 1|1) << " " << id << " " << 0 << endl;
}

void OUTTREE::connect(int l, int r, int nodeId){
	this->connect_(1,1,_n_,l,r,nodeId);
}

void OUTTREE::connect_(int id, int l, int r, int queryL, int queryR, int nodeId){
	if(queryL <= l && r <= queryR){
		edge[id].emplace_front(nodeId,1);
		//cerr << (id) << " " << nodeId << " " << 1 << endl;
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
	_base_ = maxN << 2;
	this->build_(1,1,_n_,idArray);
}

void INTREE::build_(int id, int l, int r, ARRAY &pos){
	if(l == r){
		pos[r] = id + _base_;
		edge[id + _base_].emplace_front(id,0);
		
		//cerr << (id + _base_) << " " << id << " " << 0 << endl;
		return;
	}
	
	int mid((l + r) >> 1);
	
	this->build_(id << 1, l, mid, pos);
	this->build_(id << 1|1, mid + 1, r, pos);
	
	edge[id + _base_].emplace_front((id << 1) + _base_, 0);
	edge[id + _base_].emplace_front((id << 1|1) + _base_, 0);
	//cerr << ((id << 1) + _base_) << " " << id + _base_ << " " << 0 << endl;
	//cerr << ((id << 1|1) + _base_) << " " << id + _base_ << " " << 0 << endl;
	//cerr << "DEBUG";
}

void INTREE::connect(int l, int r, int nodeId){
	this->connect_(1,1,_n_,l,r,nodeId);
}

void INTREE::connect_(int id, int l, int r, int queryL, int queryR, int nodeId){
	if(queryL <= l && r <= queryR){
		edge[nodeId].emplace_front(id + _base_, 0);
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
		
		if(vis[s.u]) continue;
		
		vis[s.u] = 1;
		for(EDGE const &e : edge[s.u]){
			if(dis[e.to] > dis[s.u] + e.weight){
				dis[e.to] = dis[s.u] + e.weight;
				if(!vis[e.to])
					que.emplace(dis[e.to],e.to);
			}
		}
		que.pop();
	}
}
