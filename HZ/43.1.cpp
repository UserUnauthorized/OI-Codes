//HZ - 43.1
//Luogu - P5494
#include<bits/stdc++.h>
using namespace std;

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

//#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
#define debug(...)
}  // namespace DEBUG

using namespace DEBUG;

typedef int valueType;
constexpr valueType maxN = 1e5 + 5, maxK = log2(maxN) + 1, maxD = 1e9;

struct SEGNODE{
	typedef SEGNODE self;
	typedef self* pointer;
	typedef ::valueType valueType;

	struct DATA{
		self::valueType value;
		self::valueType cnt;
		
		DATA(): value(INT_MAX), cnt(0){};
		DATA(self::valueType _value_, self::valueType _cnt_):value(_value_), cnt(_cnt_){};
		
		friend bool operator<(const DATA &a, const DATA &b){
//			debug(a.cnt, a.value);
//			debug(b.cnt, b.value);
//			debug(a.cnt < b.cnt, a.value > b.value);
			if(a.cnt != b.cnt)
				return a.cnt < b.cnt;
				
			return a.value > b.value;
		}
		
		void operator+=(self::valueType key){
			this->cnt += key;
		}
		
		void operator+=(const DATA &Object){
			if(this->value == Object.value)
				this->cnt += Object.cnt;
		}
	};
	
	int leftBound, rightBound, mid;
	pointer leftSon, rightSon;
	DATA data;
	
	SEGNODE():leftBound(-1), rightBound(-1), mid(-1), leftSon(NULL), rightSon(NULL), data(){};
	
	void init(self::valueType l, self::valueType r){
		this->leftBound = l;
		this->rightBound = r;
		this->mid = (this->leftBound + this->rightBound) >> 1;
	}
	
	void update(){
		this->data = DATA();
		
		if(this->leftSon != NULL)
			this->data = std::max(this->data, this->leftSon->data);
		
		if(this->rightSon != NULL)
			this->data = std::max(this->data, this->rightSon->data);
	}
};

SEGNODE* newNode();

class TREE{
public:
	typedef TREE self;
	typedef SEGNODE node;
	typedef node::DATA DATA;
	typedef node* pointer;
	typedef node::valueType valueType;

	pointer root;
	
	TREE():root(NULL){};
	
public:
	void insert(self::valueType pos, self::valueType key){
		this->root = this->insert(this->root, pos, key, 1, maxD);
	}
	
private:
	pointer insert(pointer current, self::valueType pos, self::valueType key, self::valueType l, self::valueType r){
		debug(current == NULL);
		if(current == NULL){
			current = newNode();
			current->init(l, r);
		}
		debug(current->leftBound, current->rightBound);
		if(current->leftBound == current->rightBound){
			current->data.value = current->leftBound;
			current->data += key;
			return current;
		}
		
		if(pos <= current->mid)
			current->leftSon = this->insert(current->leftSon, pos, key, l, current->mid);
		else 
			current->rightSon = this->insert(current->rightSon, pos, key, current->mid + 1, r);
		
		current->update();
		
		return current;
	}

public:
	self::valueType ans(){
		if(this->root == NULL || this->root->data.cnt < 1)
			return 0;
		
		return this->root->data.value;
	}
	
	void merge(const self &Object){
		this->root = this->merge(this->root, Object.root);
	}

private:
	pointer merge(pointer a, pointer b){
		if(a == NULL)
			return b;
		
		if(b == NULL)
			return a;
		
		if(a->leftBound == a->rightBound){
			a->data += b->data;
			return a;
		}
		
		a->leftSon = this->merge(a->leftSon, b->leftSon);
		a->rightSon = this->merge(a->rightSon, b->rightSon);
		
		a->update();
		
		return a;
	}
};

struct EDGE {
    int next;
    int to;

    EDGE():next(-1), to(-1){};

    EDGE(int _next, int _to):next(_next), to(_to){};
};

valueType n, m, cnt(0);

array<valueType, maxN> dfn, father, deep, head, ans;
array<valueType, maxN << 1> source;
array<TREE, maxN> tree;
array<EDGE, maxN << 1> edge;
array<array<valueType, maxN>, maxK> st;

void init();
valueType LCA(valueType a, valueType b);
void dfs(valueType x, valueType from);
valueType MIN(const valueType &a, const valueType &b);
void calc(valueType x, valueType from);

int main(){
	#ifdef LOCAL
	freopen("2.in", "r", stdin);
	freopen("2.ans", "w", stdout);
	freopen("2.err", "w", stderr);
	#endif
	init();
	dfs(1, 0);
	
	deep[0] = INT_MAX;
	
	for(int i = 1; i <= cnt; ++i)
		st[0][i] = source[i];
	
	for (int j = 1; j <= (int) log2(cnt); ++j)
        for (int i = 1; i + (1 << j) <= cnt; ++i)
        	st[j][i] = MIN(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            
    while(m--){
    	int x(0), y(0), z(0);
    	
    	cin >> x >> y >> z;
    	
    	int lca(LCA(x, y));
		debug(x, y, z, lca, father[lca]);
    	tree[x].insert(z, 1);
    	debug(x);
    	tree[y].insert(z, 1);
    	debug(y);
    	tree[lca].insert(z, -1);
    	debug(lca);
    	if(father[lca]);
    		tree[father[lca]].insert(z, -1);
    	debug(father[lca]);
	}

	calc(1, 0);

	for(int i = 1; i <= n; ++i)
//		cout << tree[i].ans() << '\n';
		cout << ans[i] << '\n';
	
	return 0;
}

void init(){
	cin >> n >> m;
	
	for(int i = 1; i < n; ++i){
		int a(0), b(0);
		cin >> a >> b;
		edge[i << 1] = EDGE(head[a], b);
		edge[i << 1|1] = EDGE(head[b], a);
		head[a] = i << 1;
		head[b] = i << 1|1;
	}
}

void dfs(valueType x, valueType from){
	dfn[x] += ++cnt;
	source[cnt] = x;
	deep[x] = deep[from] + 1;
	father[x] = from;
	
	for(int i = head[x]; i != 0; i = edge[i].next){
		const EDGE &e = edge[i];
		
		if(e.to == from)
			continue;
			
		dfs(e.to, x);
		
		source[++cnt] = x;
	}
}

void calc(valueType x, valueType from){
	for(int i = head[x]; i != 0; i = edge[i].next){
		const EDGE &e = edge[i];
		
		if(e.to == from)
			continue;
		calc(e.to, x);
		
		tree[x].merge(tree[e.to]);
	}
	
	ans[x] = tree[x].ans();
}
SEGNODE pool[maxN * 60];
SEGNODE* newNode(){
	static SEGNODE* allocp = pool - 1;
	
	return ++allocp; 
}

valueType MIN(const valueType &a, const valueType &b) {
    if (deep[a] > deep[b])return b;
    else return a;
}

valueType LCA(valueType a, valueType b) {
    int l(dfn[a]), r(dfn[b]);
 
    if (l > r)
        swap(l, r);

    int k(0);

    while ((1 << (k + 1)) <= r - l + 1)
        ++k;

    return MIN(st[k][l], st[k][r - (1 << k) + 1]);
}
