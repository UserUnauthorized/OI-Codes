//HZ - 20.1
//Luogu - P1886
#include<bits/stdc++.h>
using namespace std;
deque<int> que,empty;
int a[1000005];
int n,k;
void init();
int main(){
	init();
	for(int i=1;i<k;++i){
		while(!que.empty() && a[que.back()]>=a[i]) que.pop_back();
		que.push_back(i);
	}
	for(int i=k;i<=n;++i){
		while(!que.empty() && a[que.back()]>=a[i]) que.pop_back();
		que.push_back(i);
		while(que.front() <= i-k) que.pop_front();
		printf("%d ",a[que.front()]);
	}
	
	cout<<endl;
	que.swap(empty);
	
	for(int i=1;i<k;++i){
		while(!que.empty() && a[que.back()]<=a[i]) que.pop_back();
		que.push_back(i);
	}
	for(int i=k;i<=n;++i){
		while(!que.empty() && a[que.back()]<=a[i]) que.pop_back();
		que.push_back(i);
		while(que.front() <= i-k) que.pop_front();
		printf("%d ",a[que.front()]);
	}
}
void init(){
	memset(a,0,sizeof(a));
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i){
		scanf("%d",a+i);
	}
}
