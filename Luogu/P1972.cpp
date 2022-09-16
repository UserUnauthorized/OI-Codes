//Luogu - P1972
#include<bits/stdc++.h>
using namespace std;
struct Query{
	int pos;
	int l;
	int r;
} query[1000005];
int num[1000005],n,m,c[1000005],lastDirection[1000005];
void init();
inline int read();
bool cmp_pos(const Query&a,const Query&b);
bool cmp_r(const Query&a,const Query&b);
int main(){
	init();
}
void init(){
	memset(query,0,sizeof(query));
	memset(num,0,sizeof(num));
	memset(c,0,sizeof(c));
	memset(lastDirection,0,sizeof(lastDirection));
}
inline int read(){
	char ch(getchar());
	int x(0);
}
