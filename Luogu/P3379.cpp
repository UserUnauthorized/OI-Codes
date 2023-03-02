#include<bits/stdc++.h>
using namespace std;

constexpr int maxN = 5e5 + 5;

struct EDGE{
	int next;
	int from;
	int to;
	int LCA;
	
	EDGE():next(-1), from(-1), to(-1), LCA(-1){};
	
	EDGE(int _next_, int _from_, int _to_):next(_next_), from(_from_), to(_to_), LCA(-1){};
};

array<EDGE, maxN << 1> edge, queryEdge;
array<int, maxN> head, queryHead, father;
array<bool, maxN> visited;

void init();
void tarjan(int x);
int find(int x);

int N, M, ROOT;

int main(){
	init();
	
	tarjan(ROOT);

	for(int i = 1; i <= M; ++i)
		cout << queryEdge[i << 1].LCA << '\n';
	
	return 0;
}

void init(){
	cin >> N >> M >> ROOT;
	
	for(int i = 1; i < N; ++i){
		int x, y;
		cin >> x >> y;
		
		edge[i << 1] = EDGE(head[x], x, y);
		edge[i << 1|1] = EDGE(head[y], y, x);
		
		head[x] = i << 1;
		head[y] = i << 1|1;
	}
	
	for(int i = 1; i <= M; ++i){
		int x, y;
		cin >> x >> y;
		
		queryEdge[i << 1] = EDGE(queryHead[x], x, y);
		queryEdge[i << 1|1] = EDGE(queryHead[y], y, x);
		
		queryHead[x] = i << 1;
		queryHead[y] = i << 1|1;
	}
}

void tarjan(int x){
	father[x] = x;
	visited[x] = true;
	
	for(int i = head[x]; i != 0; i = edge[i].next){
		int const to = edge[i].to;
		
		if(visited[to])
			continue;
		
		tarjan(to);
		father[to] = x;
	}
	
	for(int i = queryHead[x]; i != 0; i = queryEdge[i].next){
		int const to = queryEdge[i].to;
		
		if(visited[to])
			queryEdge[i].LCA = queryEdge[i ^ 1].LCA = find(father[to]);
	}
}

int find(int x){
	if(father[x] == x) return x;
	return father[x] = find(father[x]);
}
