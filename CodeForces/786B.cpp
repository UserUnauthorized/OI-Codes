//Luogu - CF786B
//CF - 786B
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e5 + 5, maxM = 1e5 + 5;
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

struct EDGE{
	int to;
	int weight;
	
	EDGE():to(0),weight(0){};
	EDGE(int _to_, int _weight_):to(_to_),weight(_weight_){};
};

struct STATUS{
	long long dis;
	int u;
	
	STATUS():dis(0),u(0){};
	STATUS(long long _dis_, int _u_):dis(_dis_),u(_u_){};
	
	bool operator>(const STATUS &Object) const{
		return this->dis > Object.dis;
	}
};

typedef std::vector<EDGE> EdgeArray;
typedef array<long long, (maxN << 3) + (maxM << 2)> ARRAY;

class OUTTREE{
public:
	void build(int n_,ARRAY &idArray);
	void connect(int l, int r, int nodeId, int w);
private:
	int _n_;
	void build_(int id, int l, int r, ARRAY &pos);
	void connect_(int id, int l, int r, int queryL, int queryR, int nodeId, int w);
} outTree;

class INTREE{
public:
	void build(int n_,ARRAY &idArray);
	void connect(int l, int r, int nodeId, int w);
private:
	int _n_;
	const int _base_ = maxN << 2;
	void build_(int id, int l, int r, ARRAY &pos);
	void connect_(int id, int l, int r, int queryL, int queryR, int nodeId, int w);
} inTree;

EdgeArray edge[(maxN << 3) + (maxM << 2)];
bitset<(maxN << 3) + (maxM << 2)> vis;
ARRAY dis, inId, outId;

int n,m,P;

void init();
void dijkstra(int x);

int main(){
	init();
	dijkstra(outId[P]);

	for(int i = 1; i <= n; ++i)
		cout << ((dis[outId[i]] == LONG_LONG_MAX) ? -1 : (dis[outId[i]])) << " ";
	return 0;
}


void init(){
	cin >> n >> m >> P;
	
	outTree.build(n,outId);
	inTree.build(n,inId);
	
	for(int i = 0; i < m; ++i){
		int type(0);
		cin >> type;
		if(type == 1){
			int u,v,w;
			cin >> u >> v >> w;
			edge[outId[u]].emplace_back(inId[v],w);
//			cerr << (outId[u]) << ' ' << (inId[v]) <<  ' ' << w << endl;
		}else if(type == 2){
			int u,l,r,w;
			cin >> u >> l >> r >> w;
			inTree.connect(l,r,outId[u],w);
		}else{
			int v,l,r,w;
			cin >> v >> l >> r >> w;
			outTree.connect(l,r,inId[v],w);
		}
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
	
	edge[id << 1].emplace_back(id,0);
	edge[id << 1|1].emplace_back(id,0);
//	cerr << (id << 1) << ' ' << id <<  ' ' << 0 << endl;
//	cerr << (id << 1|1) << ' ' << id <<  ' ' << 0 << endl;
}

void OUTTREE::connect(int l, int r, int nodeId, int w){
	this->connect_(1,1,_n_,l,r,nodeId,w);
}

void OUTTREE::connect_(int id, int l, int r, int queryL, int queryR, int nodeId, int w){
	if(queryL <= l && r <= queryR){
		edge[id].emplace_back(nodeId,w);
//		cerr << (id) << ' ' << (nodeId) <<  ' ' << w << endl;
		return;
	}
	
	int mid((l + r) >> 1);
	
	if(queryL <= mid)
		this->connect_(id << 1, l, mid, queryL, queryR, nodeId,w);
	if(queryR > mid)
		this->connect_(id << 1|1, mid + 1, r, queryL, queryR, nodeId,w);
}

void INTREE::build(int n_,ARRAY &idArray){
	_n_ = n_;
	this->build_(1,1,_n_,idArray);
}

void INTREE::build_(int id, int l, int r, ARRAY &pos){
	if(l == r){
		pos[r] = id + _base_;
		edge[id + _base_].emplace_back(id,0);
//		cerr << (id + _base_) << ' ' << (id) <<  ' ' << 0 << endl;
		return;
	}
	
	int mid((l + r) >> 1);
	
	this->build_(id << 1, l, mid, pos);
	this->build_(id << 1|1, mid + 1, r, pos);
	
	edge[id + _base_].emplace_back((id << 1) + _base_, 0);
	edge[id + _base_].emplace_back((id << 1|1) + _base_, 0);
	//cerr << (id + _base_) << ' ' << ((id << 1) + _base_) <<  ' ' << 0 << endl;
	//cerr << (id + _base_) << ' ' << ((id << 1|1) + _base_) <<  ' ' << 0 << endl;
}

void INTREE::connect(int l, int r, int nodeId, int w){
	this->connect_(1,1,_n_,l,r,nodeId,w);
}

void INTREE::connect_(int id, int l, int r, int queryL, int queryR, int nodeId, int w){
	if(queryL <= l && r <= queryR){
		edge[nodeId].emplace_back(id + _base_, w);
//		cerr << (nodeId) << ' ' << (id + _base_) <<  ' ' << w << endl;
		return;
	}
	
	int mid((l + r) >> 1);
	
	if(queryL <= mid)
		this->connect_(id << 1, l, mid, queryL, queryR, nodeId,w);
	if(queryR > mid)
		this->connect_(id << 1|1, mid + 1, r, queryL, queryR, nodeId,w);
}

void dijkstra(int x){
	dis.fill(LONG_LONG_MAX);
	priority_queue<STATUS, vector<STATUS>, greater<STATUS> > que;
	
	dis[x] = 0;
	que.emplace(0,x);
	
	while(!que.empty()){
		STATUS const s = que.top();
		que.pop();
		if(vis[s.u]) continue;
		vis[s.u] = 1;
		
		for(EDGE const &e : edge[s.u]){
			if(dis[e.to] > dis[s.u] + e.weight){
				dis[e.to] = dis[s.u] + e.weight;
				if(!vis[e.to])
					que.emplace(dis[e.to],e.to);
			}
		}
	}
}
