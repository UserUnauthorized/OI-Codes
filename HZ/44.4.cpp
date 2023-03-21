//HZ - 44.4
//Luogu - P3302
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
        if(V < 0){
        	os << '-';
        	V = -V;
		}
		
		if(V > 9)	
			os << V / 10;
		
		os << (int)(V % 10);
		
        return os;
    }

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

typedef int valueType;
constexpr int maxN = 8e4 + 5, maxK = 20;
typedef std::array<valueType, maxN> ARRAY;
typedef std::array<ARRAY, maxK> STArray;
typedef std::vector<valueType> VECTOR;
typedef std::queue<int> QUEUE;
typedef std::bitset<maxN> BITSET;

int L_, R_, N_, M_, K_, Q_, testcase;
const int &L = L_, &R = R_, &N = N_, &M = M_, &Q = Q_, &K = K_;

struct SEGNODE {
    typedef SEGNODE self;
    typedef self *pointer;
    typedef ::valueType valueType;

    pointer leftSon, rightSon;
    self::valueType count;

    SEGNODE() : leftSon(nullptr), rightSon(nullptr), count(0) {};

    void update() {
        this->count = 0;

        if (this->leftSon != nullptr)
            this->count += this->leftSon->count;

        if (this->rightSon != nullptr)
            this->count += this->rightSon->count;
    }
};

struct EDGE {
    int next;
    int to;

    EDGE() : next(0), to(0) {};

    EDGE(int _next_, int _to_) : next(_next_), to(_to_) {}
};

typedef std::array<EDGE, maxN << 1> EdgeArray;
typedef SEGNODE::pointer pointer;
typedef std::array<pointer, maxN> PointerArray;

pointer newNode();

pointer build(valueType l, valueType r);

pointer insert(const pointer &current, valueType nodeL, valueType nodeR, valueType pos);

valueType
query(pointer xNode, pointer yNode, pointer lcaNode, pointer lcaFatherNode, valueType l, valueType r, valueType k);

valueType query(valueType x, valueType y, valueType k);

ARRAY source, father, head, depth, size;
STArray st;
PointerArray tree;
EdgeArray edge;
VECTOR point;
QUEUE que;
BITSET inQueue;

void init();

void dfs(int x, int from);

void merge(int x, int y);

valueType lca(valueType x, valueType y);

int main() {
	#ifdef LOCAL
	freopen("P3302_1.in", "r", stdin);
	freopen("P3302_1.ans", "w", stdout);
	#endif
    init();

	for(int i = 1; i <= N; ++i)
		if(!depth[i])
    		dfs(i, 0);

    int lastAns = 0;
    for (int i = 0; i < Q; ++i) {
    	char order;
    	std::cin >> order;
    	
    	if(order == 'Q'){
    		while(!que.empty()){
    			dfs(que.front(), father[que.front()]);
    			inQueue[que.front()] = false;
    			que.pop();
			}
    		
    		int x = 0, y = 0, k = 0;
        	std::cin >> x >> y >> k;
        	std::cout << (lastAns = point[query(x ^ lastAns, y ^ lastAns, k ^ lastAns)]) << '\n';
		} else if(order == 'L'){
			int x = 0, y = 0;
			std::cin >> x >> y;
			merge(x ^ lastAns, y ^ lastAns);
		}
    }

    return 0;
}

void init() {
    std::cin >> testcase >> N_ >> M_ >> Q_;

    K_ = ceil(log2(N));

    for (int i = 1; i <= N; ++i)
        std::cin >> source[i];

    for (int i = 1; i <= M; ++i) {
        int a = 0, b = 0;
        std::cin >> a >> b;
        edge[i << 1] = EDGE(head[a], b);
        edge[i << 1 | 1] = EDGE(head[b], a);
        head[a] = i << 1;
        head[b] = i << 1 | 1;
    }

    point.assign(source.begin() + 1, source.begin() + N + 1);
    point.push_back(INT_MIN);
    sort(point.begin(), point.end());
    point.erase(unique(point.begin(), point.end()), point.end());

    L_ = 1;
    R_ = (int) point.size() - 1;

    for (int i = 1; i <= N; ++i)
        source[i] = (int) distance(point.begin(), lower_bound(point.begin(), point.end(), source[i]));

    tree[0] = build(L, R);
}

pointer build(valueType l, valueType r) {
    pointer current = newNode();

    current->count = 0;

    if (l == r)
        return current;

    int const mid = (l + r) >> 1;

    current->leftSon = build(l, mid);
    current->rightSon = build(mid + 1, r);

    return current;
}

pointer insert(const pointer &current, valueType nodeL, valueType nodeR, valueType pos) {
    pointer result = newNode();
    *result = *current;

    if (nodeL == nodeR) {
        ++result->count;
        return result;
    }

    int const mid = (nodeL + nodeR) >> 1;

    if (pos <= mid)
        result->leftSon = insert(current->leftSon, nodeL, mid, pos);
    else
        result->rightSon = insert(current->rightSon, mid + 1, nodeR, pos);

    result->update();

    return result;
}

void update(const pointer &current, const pointer &preNode, valueType pos, valueType l, valueType r){
	current->count = preNode->count;
	
	if(l == r)
		return;
	
	int const mid = (l + r) >> 1;
	
	if(pos <= mid)
		update(current->leftSon, preNode->leftSon, pos, l, mid);
	else
		update(current->rightSon, preNode->rightSon, pos, mid + 1, r);
	
	current->update();
}

void update(const pointer &current, const pointer &preNode, valueType pos){
	update(current, preNode, pos, L, R);
}

valueType query(valueType x, valueType y, valueType k) {
    valueType const LCA = lca(x, y);
    return query(tree[x], tree[y], tree[LCA], tree[father[LCA]], L, R, k);
}

valueType
query(pointer xNode, pointer yNode, pointer lcaNode, pointer lcaFatherNode, valueType l, valueType r, valueType k) {
    if (l == r)
        return r;

    int const mid = (l + r) >> 1;

    int const preCount = xNode->leftSon->count + yNode->leftSon->count - lcaNode->leftSon->count - lcaFatherNode->leftSon->count;
    
    if (k <= preCount)
        return query(xNode->leftSon, yNode->leftSon, lcaNode->leftSon, lcaFatherNode->leftSon, l, mid, k);
    else
        return query(xNode->rightSon, yNode->rightSon, lcaNode->rightSon, lcaFatherNode->rightSon, mid + 1, r,
                     k - preCount);
}

pointer newNode() {
//    static SEGNODE pool[maxN * 264], *allocp = pool - 1;
//    return ++allocp;
	return new SEGNODE;
}

void dfs(int x, int from) {
	size[x] = 1;
	
    depth[x] = depth[from] + 1;
    
    tree[x] = insert(tree[from], L, R, source[x]);
    	
    st[0][x] = father[x] = from;

    for (int i = 1; i <= K; ++i)
        st[i][x] = st[i - 1][st[i - 1][x]];

    for (int i = head[x]; i; i = edge[i].next) {
        int const to = edge[i].to;

        if (to == from) continue;

        dfs(to, x);
        
        size[x] += size[to];
    }
}

valueType lca(valueType x, valueType y) {
    if (depth[x] < depth[y])
        std::swap(x, y);

    for (int i = K; i >= 0; --i)
        if (depth[st[i][x]] >= depth[y])
            x = st[i][x];

    if (x == y)
        return x;

    for (int i = K; i >= 0; --i)
        if (st[i][x] != st[i][y])
            x = st[i][x], y = st[i][y];

    return father[x];
}


void merge(int x, int y){
	if(size[x] < size[y])	
		std::swap(x, y);
	
	++M_;
	
    edge[M << 1] = EDGE(head[x], y);
    edge[M << 1 | 1] = EDGE(head[y], x);
    head[x] = M << 1;
    head[y] = M << 1 | 1;
        
    dfs(x, father[x]);
//	if(!inQueue[x]){
//		que.push(x);
//		inQueue[x] = true;
//	}
}
