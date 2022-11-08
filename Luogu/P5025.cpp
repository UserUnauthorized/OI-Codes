//Luogu - P5025
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn = 5e5+5 , P = 1e9+7;
struct segTree{
	int l, r;
	segTree(int _l, int _r):l(_l), r(_r){};
}tree[maxn << 2];
int n;
long long treeId[maxn], dis[maxn << 2], pos[maxn], len[maxn];
vector<int> edge[maxn << 2];
void build(int id, int l, int r);
void link(int id, int l, int r, const int &qL, const int &qR, const int &node);
void tarjan(int x);
void init();
int main(){
	init();
	build(1, 1, n);
	for(int i = 1; i <= n; ++i){
		int _L(lower_bound(pos + 1,pos + n + 1,pos[i] - len [i]));
		int _R(upper_bound(pos + 1,pos + n + 1,pos[i] + len [i]));
		link(1, 1, n, _L, _R, id[i]);
	}
}
void init(){
	cin >> n;
	for(int i = 1; i <= n; ++i)
		cin >> pos[i] >> len[i];
	pos[n + 1] = LONG_LONG_MAX;
}

void build(int id,int l, int r){
	if(l == r){
		treeId[r] = id;
		return;
	}
	
	int mid((l+r) >> 1);
	
	build(id << 1, l, mid);
	build(id << 1|1, mid + 1, r);
	
	edge[id].emplace_back(id << 1);
	edge[id].emplace_back(id << 1|1);
}

void link(int id, int l, int r, const int &qL, const int &qR, const int &node);{
	if(qL <= l && r <= qR){
		edge[id].emplace_back(node);
		return;
	}
	
	int mid((l+r) >> 1);
	
	if(qL <= mid)
		link(id << 1, l, mid, qL, qR, node);
	if(qR > mid)
		link(id << 1|1, mid + 1, r, qL, qR, node);
}
