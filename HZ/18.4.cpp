//HZ - 18.4
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100005;
struct Tree{
	int l,r;
	unsigned long long sum;
	int lazy;
}tree[MAXN<<2];
int n,m,a[MAXN];
void init();
void build(int,int,int);
void insert(int,int,int,int);
long long query(int,int,int);
int main(){
	init();
	build(1,1,n);
	for(int i=0;i<m;++i){
		char order(getchar());
		while(order!='A'&&order!='S')order=getchar();
		getchar();getchar();
		if(order=='A'){
			int l,r,key;
			scanf("%d%d%d",&l,&r,&key);
			insert(1,l,r,key);
		}else if(order=='S'){
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",query(1,l,r));
		}
	}
	return 0;
}
void init(){
	memset(tree,0,sizeof(tree));
	memset(a,0,sizeof(a));
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",a+i);
	}
	scanf("%d",&m);
}
void build(int id,int l, int r){
	tree[id].l=l;
	tree[id].r=r;
	
	if(l==r){
		tree[id].sum=a[l];
		return;
	}
	
	int mid=(l+r)>>1;
	build(id<<1,l,mid);
	build(id<<1|1,mid+1,r);
	
	tree[id].sum=tree[id<<1].sum+tree[id<<1|1].sum;
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
