//HZ - 20.3
//Luogu - P2422
#include<bits/stdc++.h>
using namespace std;
deque<int> que,empty;
int n,partialSum[100005],a[100005],l[100005],r[100005];
long long ans;
void getR();
void getL();
void getLR();
void getA();
void init();
int main(){
	init();
	//getR();
	//que.swap(empty);
	//getL();
	getLR();
	//getA();
	//printf("AA%d\n\n",r[1]);
	printf("%lld",ans);
	return 0;
}
void init(){
	memset(partialSum,0,sizeof(partialSum));
	memset(a,0,sizeof(a));
	memset(l,0,sizeof(l));
	memset(r,0,sizeof(r));
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	partial_sum(a,a+n+1,partialSum);
	a[0]=a[n+1]=-1;
}
void getR(){
	for(int i=1;i<=n+1;++i){
		while(!que.empty() && a[que.back()]>a[i]){
			r[que.back()]=i;
			que.pop_back();
		}
		que.push_back(i);
	}
}
void getL(){
	for(int i=n;i>=0;--i){
		while(!que.empty() && a[que.back()]>a[i]){
			l[que.back()]=i;
			que.pop_back();
		}
		que.push_back(i);
	}
}
void getLR(){
	que.push_back(0);
	for(int i=1;i<=n+1;++i){
		while(!que.empty() && a[que.back()]>a[i]){
			int back=que.back();
			que.pop_back();
			ans = max(ans,(long long)(partialSum[i-1]-partialSum[que.back()])*a[back]);
		}
		que.push_back(i);
	}
}
void getA(){
	ans=0;
	for(int i=1;i<=n;++i){
		//printf("%d\t%d\n",i,(a[i])*(partialSum[r[i]-1] - partialSum[l[i]]));
		ans=max(ans,(long long)(a[i])*(long long)(partialSum[r[i]-1] - partialSum[l[i]]));
	}
}
