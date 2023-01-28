//HZ - 31.4
//Luogu - P3451
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 2e4 + 5, maxM = 2e5 + 5, maxS = 1 << 20;

struct EDGE{
	int to;
	int next;
	int weight;
	
	EDGE():to(0),next(0),weight(0){};
	EDGE(int _to_, int _next_, int _weight_):to(_to_),next(_next_),weight(_weight){};
} edge[maxM << 1];

int n,m,K;
int head[maxN];
int dp[maxN][maxS];
int limit
