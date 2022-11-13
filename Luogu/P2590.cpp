//HZ - 40.1
//Luogu - P2590
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn = 3e4 + 5;

void initDfs(int x,int from);
void dfs(int x,int TOP);
void init();
inline int read();
void build(int id, int l, int r);
void insert(int id, int )

vector<int> edge[maxn];
int n, q, cnt(0), weight[maxn], dfn[maxn], pos[maxn], size[maxn], son[maxn], dep[maxn], father[maxn];

struct TREE{
	int l, r;
	int maxW ,sum;
}tree[maxn << 2];

int main(){
	init();
	initDfs(1, 0);
	dfs(1, 1);
	tree.build(pos + 1, n);
	
	while(q--){
		string order;
		cin >> order;
		if(order == "CHANGE"){
			
		}
	}
}

void init(){
	memset(weight, 0, sizeof(weight));
	memset(dfn, 0, sizeof(dfn));
	memset(pos, 0, sizeof(pos));
	memset(size, 0, sizeof(size));
	memset(son, 0, sizeof(son));
	memset(dep, 0, sizeof(dep));
	memset(father, 0, sizeof(father));
	
	n = read();
	q = read();
	
	for(int i = 1; i < n; ++i){
		int a(read()), b(read());
		edge[a].emplace_back(b);
		edge[b].emplace_back(a);
	}
}

inline int read(){
	int ch(getdchar()), result(0);
	bool positive(true);
	
	while((ch < '0' || ch > '9') && ch != '-')
		ch = getchar();
		
	if(ch == '-'){
		positive = false;
		ch = getchar();
	}
	
	while(ch >= '0' && ch <= '9'){
		result = (result << 3) + (result << 1) + (ch & 15);
		ch = getchar();
	} 
	
	return positive ? result : -result;
}

void initDfs(int x,int from){
	dep[x] = dep[from] + 1;
	father[x] = from;
	size[x] = 1;
	
	for(const int &iter : edge[x]){
		if(iter == from)
			continue;
		initDfs(iter, x);
		
		size[x] += size[iter];
		
		if(size[iter] > size[son[x]])
			son[x] = iter;
	}
}

void dfs(int x,int TOP){
	top[x] = TOP;
	dfn[x] = ++cnt;
	pos[cnt] = x;
	
	if(!son[x])
		return;
		
	dfs(son[x], TOP);
	
	for(const int &iter : edge[x])
		if(iter != son[x] && iter != father[x])
			dfs(iter, iter);
}
