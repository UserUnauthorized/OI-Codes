//HZ - 31.4
//Luogu - P3451
#include<bits/stdc++.h>
#include<vector>
using namespace std;
constexpr int maxN = 2e4 + 5, maxM = 2e5 + 5, maxS = 1 << 20, maxK = 22;

/*namespace DEBUG {
    template<typename T>
    inline void _debug(const char *format, T t) {
        std::cerr << format << '=' << t << std::endl;
    }

    template<class First, class... Rest>
    inline void _debug(const char *format, First first, Rest... rest) {
        while (*format != ',') std::cerr << *format++;
        std::cerr << '=' << first << ",";
        _debug(format + 1, rest...);
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &V) {
        os << "[ ";
        for (const auto &vv: V) os << vv << ", ";
        os << "]";
        return os;
    }

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;*/
#define debug(...)

struct EDGE{
	int to;
	int next;
	int weight;
	
	EDGE():to(0),next(0),weight(0){};
	EDGE(int _to_, int _next_, int _weight_):to(_to_),next(_next_),weight(_weight_){};
} edge[maxM << 1];

int n,m,K;
int head[maxN];
unsigned int dp[maxK][maxS];
unsigned int dis[maxK][maxN];
unsigned int limit[maxK];
bool vis[maxN];

void init();
void spfa(int x);

int main(){
	init();
	
	for(int i = 1; i <= K + 1; ++i)
		spfa(i);
	
	if(K == 0){
		cout << dis[1][n];
		return 0;
	}
	
	const int S = 1 << K;
	
	dp[0][0] = 0;
	
	for(int k = 1; k <= K; ++k)
		if(!limit[k + 1]){
			dp[k][1 << (k - 1)] = dis[1][k + 1];
			debug(k,limit[k + 1],dis[1][k + 1]);
		}
			
	
	for(int i = 1; i < S; ++i){
		for(int k = 1; k <= K; ++k){
			if(~i & 1 << (k - 1)) continue;
			if((i & limit[k + 1]) != limit[k + 1]) continue;
			debug(i,k);
			for(int x = 1; x <= K; ++x){
				if((x == k) || (~i & 1 << (x - 1))) continue;
				debug(i,k,x,dp[k][i],dp[x][i ^ (1 << (k - 1))] + dis[k + 1][x + 1],i ^ (1 << (k - 1)));
				dp[k][i] = min(dp[k][i], dp[x][i ^ (1 << (k - 1))] + dis[k + 1][x + 1]);
			}
		}
	}
	
	unsigned int ans(INT_MAX);
	for(int i = 1; i <= K; ++i){
		debug(i,ans,dp[i][(1 << K) - 1] + dis[i + 1][n],(1 << K) - 1);
		ans = min(ans, dp[i][(1 << K) - 1] + dis[i + 1][n]);
	}
		
		
	cout << ans;
	return 0;
}

void init(){
	memset(head,0,sizeof(head));
	memset(dp,0x7f,sizeof(dp));
	memset(dis,0x7f,sizeof(dis));
	memset(limit,0,sizeof(limit));
	
	cin >> n >> m >> K;
	
	for(int i = 1; i <= m; ++i){
		int a,b,w;
		cin >> a >> b >> w;
		
		edge[i << 1] = EDGE(b, head[a], w);
		edge[i << 1|1] = EDGE(a, head[b], w);
		
		head[a] = i << 1;
		head[b] = i << 1|1;
	}
	
	int t;
	cin >> t;
	while(t--){
		int x,y;
		cin >> x >> y;
		limit[y] += 1 << (x - 2);
	}
}

void spfa(int x){
	queue<int> que;
	memset(vis,0,sizeof(vis));
	
	dis[x][x] = 0;
	vis[x] = true;
	que.push(x);
	
	while(!que.empty()){
		int k = que.front();
		for(int i = head[k]; i != 0; i = edge[i].next){
			EDGE const &e = edge[i];
			if(dis[x][k] + e.weight < dis[x][e.to]){
				dis[x][e.to] = dis[x][k] + e.weight;
				if(!vis[e.to]){
					vis[e.to] = true;
					que.push(e.to);
				}
			}
		}
		que.pop();
		vis[k] = false;
	}
}
