//HZ - 17.5
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005],c[100005];
int lowbit(int);
void update(int,int);
int sum(int);
void init();
int main(){
	init();
	for(int i=0;i<m;++i){
		int t,x,y;
		scanf("%d%d%d",&t,&x,&y);
		if(t){
			printf("%d\n",sum(y)^sum(x-1));
		}else{
			update(x,y);
		}
	}
	return 0;
}
void init(){
	memset(a,0,sizeof(a));
	memset(c,0,sizeof(c));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		int t;
		scanf("%d",&t);
		update(i,t);
	}
}
int lowbit(int x){
	return x&(-x);
}
void update(int x,int key){
	for(int i=x;i<=n;i+=lowbit(i)){
		c[i]^=a[x];
		c[i]^=key;
	}
	a[x]=key;
}
int sum(int x){
	int result=0;
	while(x>0){
		result^=c[x];
		x-=lowbit(x);
	}
	return result;
}
