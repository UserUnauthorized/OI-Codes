//Luogu - P3178
//HZ - 40.4

#ifdef LOCAL \ #include<debug.h> \
#else
#define debug(...)
#endif

#include<bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 5;

int n, m, cnt(0), weight[maxn], dfn[maxn], out[maxn], pos[maxn], son[maxn], top[maxn], dep[maxn], father[maxn], size[maxn];
vector<int> edge[maxn];

struct TREE{
	int l, r;
	long long lazy;
	long long sum;
}tree[maxn << 2];

inline int read();
void init();
void initDfs(int x, int from);
void dfs(int x, int TOP);
void build(int id, int l, int r);
void update(int id, int pos, int key);
void update(int id, int l, int r, int key);
long long query(int id, int l, int r);

int main(){
	init();
	initDfs(1, 0);
	dfs(1, 1);
	build(1, 1, n);
	
	while(m--){
		int order(read());
		if(order == 1){
			int x(read()), key(read());
			update(1, dfn[x], key);
		}else if(order == 2){
			int x(read()), key(read());
			update(1, dfn[x], out[x], key);
		}else{
			int x(read());
			long long result(0);
			
			do{
				result += query(1, dfn[top[x]], dfn[x]);
				x = father[top[x]];
			}while(x != 0 && x != 1);
			
			printf("%lld\n", result);
		}
	}
	
	return 0;
}

void init(){
	n = read();
	m = read();
	
	for(int i = 1; i <= n; ++i)
		weight[i] = read();
	
	for(int i = 1; i < n; ++i){
		int u(read()), v(read());
		edge[u].emplace_back(v);
	}
}

void initDfs(int x, int from){
	dep[x] = dep[from] + 1;
	father[x] = from;
	size[x] = 1;
	
	for(const int &iter : edge[x]){
		if(iter == from)
			continue;
			
		initDfs(iter, x);
		
		size[x] += size[iter];
		if(size[iter] > size[son[x]])
			son[x] = iter;
	}
}

void dfs(int x, int TOP){
	top[x] = TOP;
	dfn[x] = ++cnt;
	pos[cnt] = x;
	
	if(son[x]){
		dfs(son[x], TOP);
		
		for(const int &iter : edge[x]){
			if(iter != son[x] && iter != father[x])
				dfs(iter, iter);
		}
	}
		
	out[x] = cnt;
}

void build(int id, int l, int r){
	tree[id].l = l;
	tree[id].r = r;
	
	if(l == r){
		tree[id].sum = (long long)weight[pos[r]];
		return;
	}
	
	int mid((l + r) >> 1);
	
	build(id << 1, l, mid);
	build(id << 1|1, mid + 1, r);
	
	tree[id].sum = tree[id << 1].sum + tree[id << 1|1].sum;
}

void update(int id, int pos, int key){
	if(tree[id].l == tree[id].r){
		tree[id].sum += (long long)key;
		return;
	}
	
	if(tree[id].lazy){
		tree[id << 1].sum += (tree[id << 1].r - tree[id << 1].l + 1) * tree[id].lazy;
		tree[id << 1|1].sum += (tree[id << 1|1].r - tree[id << 1|1].l + 1) * tree[id].lazy;
		tree[id << 1].lazy += tree[id].lazy;
		tree[id << 1|1].lazy += tree[id].lazy;
		tree[id].lazy = 0;
	}
	
	int mid((tree[id].l + tree[id].r) >> 1);
	
	if(pos <= mid)
		update(id << 1, pos, key);
	else 
		update(id << 1|1, pos, key);
		
	tree[id].sum = tree[id << 1].sum + tree[id << 1|1].sum;
}

void update(int id, int l, int r, int key){
	if(l <= tree[id].l && tree[id].r <= r){
		tree[id].sum += (tree[id].r - tree[id].l + 1) * (long long)key;
		tree[id].lazy += (long long)key;
		return;
	}
	
	if(tree[id].lazy){
		tree[id << 1].sum += (tree[id << 1].r - tree[id << 1].l + 1) * tree[id].lazy;
		tree[id << 1|1].sum += (tree[id << 1|1].r - tree[id << 1|1].l + 1) * tree[id].lazy;
		tree[id << 1].lazy += tree[id].lazy;
		tree[id << 1|1].lazy += tree[id].lazy;
		tree[id].lazy = 0;
	}
	
	int mid((tree[id].l + tree[id].r) >> 1);
	
	if(l <= mid)
		update(id << 1, l, r, key);
	if(r > mid) 
		update(id << 1|1, l, r, key);
		
	tree[id].sum = tree[id << 1].sum + tree[id << 1|1].sum;
}

long long query(int id, int l, int r){
	if(l <= tree[id].l && tree[id].r <= r)
		return tree[id].sum;
	
	if(tree[id].lazy){
		tree[id << 1].sum += (tree[id << 1].r - tree[id << 1].l + 1) * tree[id].lazy;
		tree[id << 1|1].sum += (tree[id << 1|1].r - tree[id << 1|1].l + 1) * tree[id].lazy;
		tree[id << 1].lazy += tree[id].lazy;
		tree[id << 1|1].lazy += tree[id].lazy;
		tree[id].lazy = 0;
	}
	
	int mid((tree[id].l + tree[id].r) >> 1);
	
	if(r <= mid)
		return query(id << 1, l, r);
	else if(l > mid) 
		return query(id << 1|1, l, r);
	else
		return query(id << 1, l, r) + query(id << 1|1, l, r);
}

inline int read(){
	int ch(getchar()), result(0);
	bool positive(true);
	
	while((ch < '0' || ch > '9') && ch != '-')
		ch = getchar();
		
	if(ch == '-'){
		positive = false;
		ch = getchar();
	}
	
	while(ch >= '0' && ch <= '9'){
		result = (result << 3) + (result << 1) + (ch & 15);
		ch = getchar();
	} 
	
	return positive ? result : -result;
}
