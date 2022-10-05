//HZ - 28.2
//Luogu - P2341
#include<bits/stdc++.h>
using namespace std;
struct EDGE{
	int next;
	int to;
}edge[50004];
int n,m,cnt;
int dfn[10004],low[10004],scc[10004],head[10004];
bool vis[10004];
stack<int> st;
void tarjan(int);
int find(int);
void init();
int main(){
	init();
	for(int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i); 
}
void init(){
	memset(edge,0,sizeof(edge));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(scc,0,sizeof(scc));
	memset(head,0,sizeof(head));
	memset(vis,0,sizeof(vis));
	
	scanf("%d%d",&n,&m);
	
	cnt = 0;
	for(int i=0;i<m;++i){
		int ta,tb;
		scanf("%d%d",&ta,&tb);
		edge[++cnt].next = head[ta];
		head[ta] = cnt;
		edge[cnt].to = tb;
	}
	cnt = 0;
}
void tarjan(int x){
	dfn[x] = low[x] = ++cnt;
	vis[x] = true;
	st.push(x);
	
	for(int i = head[x] ; i ; i = edge[i].next){
		if(!dfn[edge[i].to]){
			tarjan(edge[i].to);
			low[x] = min(low[x],low[edge[i].to]);
		}else if(vis[edge[i].to]){
			low[x] = min(low[x],dfn[edge[i].to]);
		}
	}
}
