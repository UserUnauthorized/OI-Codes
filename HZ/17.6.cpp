//HZ - 17.6
#include<bits/stdc++.h>
using namespace std;
int c[1025][1025],s;
void init();
int lowbit(int);
void insert(int,int,int);
int sum(int,int);
int main(){
	init();
	int t;
	scanf("%d",&t);
	while(t!=3){
		if(t==1){
			int x,y,key;
			scanf("%d%d%d",&x,&y,&key);
			++x,++y;
			insert(x,y,key);
		}else if(t==2){
			int l,b,r,T;
			scanf("%d%d%d%d",&l,&b,&r,&T);
			++l;++b;++r;++T;
			printf("%d\n",sum(r,T)-sum(l-1,T)-sum(r,b-1)+sum(l-1,b-1));
		}
		scanf("%d",&t);
	}
	return 0;
}
void init(){
	memset(c,0,sizeof(c));
	int t;
	scanf("%d%d",&t,&s);
}
int lowbit(int x){
	return x&(-x);
}
void insert(int x,int y,int key){
	for(;x<=s;x+=lowbit(x)){
		for(int j=y;j<=s;j+=lowbit(j)){
			c[x][j]+=key;
		}
	}
}
int sum(int x,int y){
	if(x<=0||y<=0)return 0;
	int result=0;
	for(;x>0;x-=lowbit(x)){
		for(int i=y;i>0;i-=lowbit(i)){
			result+=c[x][i];
		}
	}
	return result;
}
