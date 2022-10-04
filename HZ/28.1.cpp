//HZ - 28.1
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn = 200005;
int edge[maxn],dfn[maxn],low[maxn];
bool vis[maxn];
int n,ans=0x7fffffff,cnt;
stack<int> st;
void tarjan(int);
void init();
int main(){
	init();
	tarjan(1);
	printf("%d",ans);
}
void init(){
	memset(edge,0,sizeof(edge));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(vis,0,sizeof(vis));
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",edge+i);
	}
}
void tarjan(int x){
	dfn[x] = low[x] = ++cnt;
	st.push(x);
	vis[x] = true;
	
	if(!dfn[edge[x]]){
		tarjan(edge[x]);
		low[x] = min(low[x],low[edge[x]]);
	}else if(vis[edge[x]]){
		low[x] = min(low[x],dfn[edge[x]]);
	}
	
	if(low[x] == dfn[x]){
		int t,y;
		do{
			y = st.top();
			st.pop();
			vis[y] = false;
			++t;
		} while(y != x);
		
		ans = min(ans,t);
	}
}
