//HZ - 28.7
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn = 5003;
int n,m,cnt = 0,ans = 0,sccnum = 0,head[maxn],dfn[maxn],low[maxn],belong[maxn],degree[maxn];
bool vis[maxn];
struct EDGE{
	int next;
	int to;
	bool use;
	int partner;
}edge[maxn<<2];
void init();
void tarjan(int,int);
void tarjan(int);
void addEdge(int,int);
void delEdge(int);
vector<EDGE> mp;
stack<int> st;
int main(){
	init();
	for(int i=1;i<=n;++i){
		if(!dfn[i]) tarjan(i,i);
	}
	
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	
	for(int i=1;i<=n;++i){
		if(!dfn[i]) tarjan(i);
	}
	
	for(EDGE e : mp){
		++degree[belong[e.to]];
	}
	
	for(int i=1;i<=sccnum;++i){
		if(degree[i] == 1){
			++ans;
		}
	}
	
	printf("%d",(ans + 1)>>1);
	return 0;
}
void init(){
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(edge,0,sizeof(edge));
	memset(vis,0,sizeof(vis));
	memset(belong,0,sizeof(belong));
	memset(degree,0,sizeof(degree));
	
	scanf("%d%d",&n,&m);
	
	for(int i=0;i<m;++i){
		int a,b;
		scanf("%d%d",&a,&b);
		addEdge(a,b);
	}
}
void addEdge(int a,int b){
	edge[++cnt].use = true;
	edge[cnt].next = head[a];
	edge[cnt].to = b;
	edge[cnt].partner = cnt + 1;
	head[a] = cnt;
	
	edge[++cnt].use = true;
	edge[cnt].next = head[b];
	edge[cnt].to = a;
	edge[cnt].partner = cnt - 1;
	head[b] = cnt;
}
void tarjan(int x,int father){
	dfn[x] = low[x] = ++cnt;

	bool first = true;
	for(int i = head[x] ; i ; i = edge[i].next){
		if(first && edge[i].to == father){
			first = false;
			continue;
		}
		if(!dfn[edge[i].to]){
				tarjan(edge[i].to,x);
			low[x] = min(low[x],low[edge[i].to]);
			if(dfn[x] < low[edge[i].to]) delEdge(i);
			} else {
			low[x] = min(low[x],dfn[edge[i].to]);
		}
	}
}
void delEdge(int x){
	edge[x].use = false;
	edge[edge[x].partner].use = false;
	mp.push_back(edge[x]);
	mp.push_back(edge[edge[x].partner]);
}
void tarjan(int x){
	dfn[x] = low[x] = ++cnt;
	st.push(x);
	vis[x] = true;
	
	for(int i = head[x] ; i ; i = edge[i].next){
		if(!edge[i].use) continue;
		if(!dfn[edge[i].to]){
			tarjan(edge[i].to);
			low[x] = min(low[x],low[edge[i].to]);
		}else if(vis[edge[i].to]){
			low[x] = min(low[x],dfn[edge[i].to]);
		}
	}
	
	if(dfn[x] == low[x]){
		++sccnum;
		int y;
		do{
			y = st.top();
			st.pop();
			belong[y] = sccnum;
		} while(y != x);
	}
}
