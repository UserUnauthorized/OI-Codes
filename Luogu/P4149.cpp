//HZ - 51.2
//Luogu - P4149
#include<bits/stdc++.h>

namespace DEBUG {
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

    std::ostream &operator<<(std::ostream &os, __int128 V) {
        if (V < 0) {
            os << '-';
            V = -V;
        }

        if (V > 9)
            os << V / 10;

        os << (int) (V % 10);

        return os;
    }

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

typedef int valueType;

constexpr valueType MAX = INT_MAX >> 1;
constexpr valueType maxK = 1e6 + 5, maxN = 2e5 + 5;

valueType N_, K_;
valueType const &N = N_, &K = K_;

typedef std::pair<int, valueType> Edge;
typedef std::list<Edge> OutEdgeList;
typedef std::array<OutEdgeList, maxN> EdgeSet;

std::array<valueType, maxK> exist;
std::array<valueType, maxN> distBuffer, countBuffer, dist, size, weight, count;
valueType ans;
std::bitset<maxN> visited;

EdgeSet edge;

void calcSize(int x, int from, int &root, int const &sum);
void calcDist(int x, int from, int &bufferSize);
void dfs(int x, int from);
void addEdge(int a, int b, int w);

int main() {
	std::cin >> N_ >> K_;
	
	for(int i = 1; i < N; ++i) {
		int a, b, w;
		
		std::cin >> a >> b >> w;

		addEdge(++a, ++b, w);
	}
	
	ans = MAX;
	
	int root = 0;
	
	weight[root] = MAX;
	
	exist.fill(MAX);
	
	calcSize(1, -1, root, N);
	calcSize(root, -1, root, N);
	
	dfs(root, -1);
	
	std::cout << (ans == MAX ? -1 : ans) << std::flush;
	
	return 0;
}

void addEdge(int a, int b, int w) {
	edge[a].emplace_back(b, w);
	edge[b].emplace_back(a, w);
}

void calcSize(int x, int from, int &root, int const &sum) {
	size[x] = 1;
	weight[x] = 0;
	
	for(auto const &iter : edge[x]) {
		int const to = iter.first;
		
		if(to == from || visited[to])
			continue;
			
		calcSize(to, x, root, sum);
		
		size[x] += size[to];
		
		weight[x] = std::max(weight[x], size[to]);
	}
	
	weight[x] = std::max(weight[x], sum - size[x]);
	
	if(weight[x] < weight[root])
		root = x;
}

void calcDist(int x, int from, int &bufferSize) {
	distBuffer[++bufferSize] = dist[x];
	countBuffer[bufferSize] = count[x];
	
	for(auto const &iter : edge[x]) {
		int const to = iter.first;
		
		int const w = iter.second;
		
		if(to == from || visited[to])
			continue;
			
		dist[to] = dist[x] + w;
		count[to] = count[x] + 1;
		
		calcDist(to, x, bufferSize);
	}
}

void dfs(int x, int from) {
	std::queue<valueType> tag;
	
	std::function<void(valueType, valueType)> sure = [&tag] (valueType i, valueType key) mutable {
		if(i >= K)
			return;

		exist[i] = std::min(exist[i], key);
		tag.push(i);
	};
	
	sure(0, 0);
	
	visited[x] = true;
	
	for(auto const &iter : edge[x]) {
		int const to = iter.first;
		
		int const w = iter.second;
		
		if(to == from || visited[to])
			continue;

		count[to] = 1;
		
		dist[to] = w;
		
		int bufferSize = 0;
		
		calcDist(to, x, bufferSize);
		
		for(int i = 1; i <= bufferSize; ++i)
			if(distBuffer[i] <= K)
				ans = std::min(ans, countBuffer[i] + exist[K - distBuffer[i]]);

		for(int i = 1; i <= bufferSize; ++i)
			sure(distBuffer[i], countBuffer[i]);
	}
	
	while(!tag.empty()) {
		exist[tag.front()] = MAX;
		tag.pop();
	}
	
	for(auto const &iter : edge[x]) {
		int const to = iter.first;
		
		if(to == from || visited[to])
			continue;
			
		int sum = size[to];
		
		int root = 0;
		
		weight[root] = MAX;
		
		calcSize(to, x, root, sum);
		calcSize(root, -1, root, sum);
		
		dfs(root, x);
	}
}
