#include<bits/stdc++.h>
using namespace std;
int n,c[92011],d[95011];
int lowbit(const int x);
int getSum(int x);
void add(int x);
void init();
int main(){
	init();
	for(int i=1;i<=n;++i){
		int ttttt,t1;
		scanf("%d%d",&ttttt,&t1);
		++ttttt;
		++d[getSum(ttttt)];
		add(ttttt);
	}
	for(int i=0;i<n;++i){
		printf("%d\n",d[i]);
	}
	return 0;
}
void init(){
	memset(c,0,sizeof(c));
	memset(d,0,sizeof(d));
	scanf("%d",&n);
}
int lowbit(const int x){
	return (x&(-x));
}
int getSum(int x){
	int s=0;
	while(x>0){
		s+=c[x];
		x-=lowbit(x); 
	}
	return s;
}
void add(int x){
	while(x<=32005){
		++c[x];
		x+=lowbit(x);
	}
}
