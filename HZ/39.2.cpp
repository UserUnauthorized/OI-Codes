//HZ - 39.2
#include<bits/stdc++.h>
#define lid (id<<1)
#define rid (id<<1|1)
using namespace std;
constexpr int maxn = 1000006;
struct Tree{
	int l,r;
	long long sum;
	int lazy;
}tree[maxn<<2];
struct EDGE{
	int next;
	int to;
}edge[maxn<<1];
int n,m,root,cnt = 0,value[maxn],seg[maxn],head[maxn],dfn[maxn],last[maxn];
void init();
void build(int,int,int);
void addEdge(int,int);
//void update(int,int,int);
void insert(int,int,int,int);
long long query(int,int,int);
void dfs(int,int);
int main(){
	//freopen("145_2.in","r",stdin);
	//freopen("145_aaa.out","w",stdout);
	init();
	dfs(root,-1);
	build(1,1,n);
	int order;
	for(int i = 0;i < m;++i){
		scanf("%d",&order);
		if(order == 1){
			int pos,key;
			scanf("%d%d",&pos,&key);
			insert(1,dfn[pos],last[pos],key);
		}else if(order == 2){
			int pos;
			scanf("%d",&pos);
			printf("%lld\n",query(1,dfn[pos],last[pos]));
		}
	}
	return 0;
}
void init(){
	memset(tree,0,sizeof(tree));
	memset(edge,0,sizeof(edge));
	memset(head,0,sizeof(head));
	memset(dfn,0,sizeof(dfn));
	memset(last,0,sizeof(last));
	memset(value,0,sizeof(value));
	memset(seg,0,sizeof(seg));
	
	scanf("%d%d%d",&n,&m,&root);
	for(int i = 1;i <= n;++i){
		scanf("%d",value + i);
	}
	
	int a,b;
	for(int i = 1;i < n;++i){
		scanf("%d%d",&a,&b);
		addEdge(a,b);
	}
	
	cnt = 0;
}
void addEdge(int a,int b){
	edge[++cnt].next = head[a];
	edge[cnt].to = b;
	head[a] = cnt;
	
	edge[++cnt].next = head[b];
	edge[cnt].to = a;
	head[b] = cnt;
}
void dfs(int x,int fa){
	dfn[x] = last[x] = ++cnt;
	seg[cnt] = value[x];
	
	for(int i = head[x] ; i ; i = edge[i].next){
		int to = edge[i].to;
		if(to != fa){
			dfs(to,x);
			last[x] = max(last[x],last[to]);
		}
	}
}
void build(int id,int l,int r){
	tree[id].l=l;
	tree[id].r=r;
	
	if(l==r){
		tree[id].sum=seg[l];
		return;
	}
	
	int mid=(l+r)>>1;
	build(lid,l,mid);
	build(rid,mid+1,r);
	
	tree[id].sum=tree[lid].sum+tree[rid].sum;
}
/*void update(int id,int pos,int key){
	if(tree[id].l==tree[id].r){
		tree[id].sum+=key;
		return;
	}
	
	int mid=(tree[id].l+tree[id].r)>>1;
	if(pos<=mid) update(lid,pos,key);
	else update(rid,pos,key);
	
	tree[id].sum = tree[lid].sum + tree[rid].sum;
}*/
long long query(int id,int l,int r){
	if(tree[id].l>=l && r>= tree[id].r){
		return tree[id].sum;
	}
	
	if(tree[id].lazy){
		tree[id<<1].lazy += tree[id].lazy;
		tree[id<<1|1].lazy += tree[id].lazy;
		tree[id<<1].sum += tree[id].lazy * (tree[id<<1].r-tree[id<<1].l+1);
		tree[id<<1|1].sum += tree[id].lazy * (tree[id<<1|1].r-tree[id<<1|1].l+1);
		tree[id].lazy=0;
	}
	
	int mid=(tree[id].l+tree[id].r)>>1;
	if(r<=mid)return query(id<<1,l,r);
	else if(l>mid)return query(id<<1|1,l,r);
	else return query(id<<1,l,r)+query(id<<1|1,l,r);
}
void insert(int id,int l,int r,int key){
	if(l<=tree[id].l && tree[id].r<=r){
		tree[id].lazy += key;
		tree[id].sum += key * (tree[id].r-tree[id].l+1);
		return;
	}
	
	if(tree[id].lazy && tree[id].l!=tree[id].r){
		tree[id<<1].lazy += tree[id].lazy;
		tree[id<<1|1].lazy += tree[id].lazy;
		tree[id<<1].sum += tree[id].lazy * (tree[id<<1].r-tree[id<<1].l+1);
		tree[id<<1|1].sum += tree[id].lazy * (tree[id<<1|1].r-tree[id<<1|1].l+1);
		tree[id].lazy=0;
	}
	
	int mid = (tree[id].l + tree[id].r)>>1;
	if(l<=mid) insert(id<<1,l,r,key);
	if(r>mid) insert(id<<1|1,l,r,key);
	
	tree[id].sum=tree[id<<1].sum + tree[id<<1|1].sum;
}
