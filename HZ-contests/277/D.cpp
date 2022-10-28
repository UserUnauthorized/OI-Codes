//HZ - 277.4
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 6;

struct NODE {
	int pos;
	int san;
	int deep;
	int unique;
	int size;
	bool song;
	bool kong;
	bool minSan[5];

	NODE():pos(-1),san(-1),deep(-1),unique(-1),size(-1),song(false),kong(false) {
		memset(minSan,0,sizeof(minSan));
	}

	NODE(int _pos,int _san):pos(_pos),san(_san),deep(-1),unique(-1),size(-1),song(false),kong(false) {
		memset(minSan,0,sizeof(minSan));
	}
} node[maxn];

struct EDGE {
	int next;
	int to;

	EDGE():next(-1),to(-1) {};

	EDGE(int _next,int _to):next(_next),to(_to) {};
} edge[maxn];

inline void init();
inline int read();
//inline void write(int *);
//inline bool posCmp(const NODE &,constNODE &);
//inline bool sanCmp(const NODE &,constNODE &);
void dfs(int,int);

int n,k,q,ans(0),head[maxn],parent[maxn<<2];

int main() {
//	freopen("ex_coc3.in","r",stdin);
//	freopen("ex.out","w",stdout);

	init();
	
	dfs(1,0);

	for(int i=1; i<=n; ++i)
		if(!node[i].kong && !node[i].song)
			++ans;

	printf("%d",ans);

//	fclose(stdin);
//	fclose(stdout);

	return 0;
}

inline void init() {
	memset(head,0xff,sizeof(head));
	memset(parent,0xff,sizeof(parent));

	scanf("%d%d%d",&n,&k,&q);
	k += maxn;

	for(int i = 1; i <= n; ++i)
		node[i]=NODE(i,read() + maxn);

	for(int i = 2; i <= n; ++i) {
		int u = read();
		edge[i] = EDGE(head[u],i);
		head[u] = i;
	}
}

inline int read() {
	int result(0),ch(getchar());
	bool positive(true);
	while((ch < '0' || ch > '9') && ch != '-')
		ch = getchar();
	if(ch == '-') {
		positive = false;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		result = (result << 3) + (result << 1) + (ch ^ 48);
		ch = getchar();
	}
	if(positive)
		return result;
	else
		return -result;
}

//inline void write(int *) {
//	int ch(getchar());
//	bool positive(true);
//	while((ch < '0' || ch > '9') && ch != '-')
//		ch = getchar();
//	if(ch == '-') {
//		positive = false;
//		ch = getchar();
//	}
//	while(ch >= '0' && ch <= '9') {
//		*result = (*result << 3) + (*result << 1) + (ch ^ 48);
//		ch = getchar();
//	}
//	if(!positive)
//		*result = -*result;
//}

void dfs(int x,int from) {
	node[x].deep = node[from].deep + 1;
	node[x].size = 1;
	parent[node[x].san] = x;

	if(node[x].san<k)
		node[x].minSan[1] = true;

	for(int i = head[x]; i != -1; i = edge[i].next) {
		const EDGE &e = edge[i];
		dfs(e.to,x);

		if(parent[node[x].san] != x)
			--node[x].size;

		parent[node[e.to].san] = x;

		node[x].size += node[e.to].size;
		if(node[e.to].minSan[1])
			node[x].minSan[2] = true;
		if(node[e.to].minSan[2])
			node[x].minSan[3] = true;
	}

	if(node[x].minSan[1] || node[x].minSan[2] || node[x].minSan[3])
		node[x].song = true;

	if(node[x].size >= q)
		node[x].kong = true;
}

//inline bool posCmp(const NODE &a,constNODE &b) {
//	return a.pos < b.pos;
//}
//inline bool sanCmp(const NODE &a,constNODE &b) {
//	if(a.san!=b.san)
//		return a.san<b.san;
//}
