//HZ - 20.7
#include<bits/stdc++.h>
using namespace std;
deque<int> que;
int n,w,ans,x,y;
void init();
int main(){
	init();
	for(int i=0;i<n;++i){
		scanf("%d%d",&x,&y);
		while(!que.empty() && que.back() > y) que.pop_back();
		if(que.empty() || que.back() < y){
			que.push_back(y);
			if(y)++ans; 
		}
	}
	printf("%d",ans);
	return 0;
}
void init(){
	ans=0;
	scanf("%d%d",&n,&w);
}
