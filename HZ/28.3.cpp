//HZ - 28.3
//Luogu - P3627
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn = 500005;
struct EDGE{
	int next;
	int to;
}edgeOld[maxn],edge[maxn];
int n,m,s,p,ans=0,sccnum=0,cnt=0,headOld[maxn],head[maxn],dis[maxn],vOld[maxn],v[maxn],low[maxn],dfn[maxn],bar[maxn],belong[maxn];
//vector<int> scc[maxn];
stack<int> st;
bool vis[maxn];
void init();
void spfa(int);
void build();
void tarjan(int);
inline void addEdge(int,int);
inline void addOldEdge(int,int);
int main(){
	init();
	for(int i=1;i<=n;++i){
		if(!dfn[i])
			tarjan(i);
	}
	//tarjan(s);
	build();
	spfa(belong[s]);
	for(int i=1;i<=p;++i){
		ans = max(ans,dis[belong[bar[i]]]);
	}
	printf("%d",ans);
	return 0;
}
void init(){
	memset(edgeOld,0,sizeof(edgeOld));
	memset(edge,0,sizeof(edge));
	memset(headOld,0,sizeof(headOld));
	memset(head,0,sizeof(head));
	memset(dis,0,sizeof(dis));
	memset(vOld,0,sizeof(vOld));
	memset(v,0,sizeof(v));
	memset(low,0,sizeof(low));
	memset(dfn,0,sizeof(dfn));
	memset(vis,0,sizeof(vis));
	memset(bar,0,sizeof(bar));
	memset(belong,0,sizeof(belong));
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		addOldEdge(u,v);
	}
	cnt = 0;
	for(int i=1;i<=n;++i){
		scanf("%d",vOld+i); 
	}
	
	scanf("%d%d",&s,&p);
	for(int i=1;i<=p;++i){
		scanf("%d",bar+i); 
	}
}
void tarjan(int x){
	dfn[x] = low[x] = ++cnt;
	vis[x] = true;
	st.push(x);
	
	for(int i = headOld[x] ; i ; i = edgeOld[i].next){
		if(!dfn[edgeOld[i].to]){
			tarjan(edgeOld[i].to);
			low[x] = min(low[x],low[edgeOld[i].to]);
		}else if(vis[edgeOld[i].to]){
			low[x] = min(low[x],dfn[edgeOld[i].to]);
		}
	}
	
	if(dfn[x] == low[x]){
		++sccnum;
		int y;
		do{
			y = st.top();
			st.pop();
			vis[y] = false;
			belong[y] = sccnum;
			//scc[sccnum].push_back(y);
			v[sccnum] += vOld[y];
		} while(y != x);
	}
}
void build(){
	cnt=0;
	/*for(int i=1;i<=sccnum;++i){
		for(auto iter = scc[i].begin();iter != scc[i].end();++iter){
			for(int j=headOld[*iter] ; j ; j=edgeOld[j].next){
				if(i != belong[edgeOld[j].to]){
					addEdge(i,belong[edgeOld[j].to]);
				}
			}
		}
	}*/
	for(int i=1;i<=n;++i){
		for(int j=headOld[i] ; j ; j = edgeOld[j].next){
			if(belong[i] != belong[edgeOld[j].to]){
				addEdge(belong[i],belong[edgeOld[j].to]);
			}
		}
	} 
}
void spfa(int x){
	memset(vis,0,sizeof(vis));
	queue<int> que;
	que.push(x);
	vis[x] = true;
	while(!que.empty()){
		for(int i = head[que.front()] ; i ; i = edge[i].next){
			if(dis[edge[i].to] < v[edge[i].to] + v[que.front()]){
				dis[edge[i].to] = v[edge[i].to] + v[que.front()];
				if(!vis[edge[i].to]){
					que.push(edge[i].to);
					vis[edge[i].to] = true;
				}
			}
		}
		vis[que.front()] = false;
		que.pop(); 
	}
}
inline void addOldEdge(int u,int v){
	edgeOld[++cnt].next = headOld[u];
	headOld[u] = cnt;
	edgeOld[cnt].to = v;
}
inline void addEdge(int u,int v){
	edge[++cnt].next = head[u];
	head[u] = cnt;
	edge[cnt].to = v;
}
