//HZ - 40.2
//Luogu - P2486
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5+5, maxp = 25;

struct NODE{
	int count;
	int left,right;
	
	NODE():count(0), left(0), right(0){};
	
	NODE(int _color):count(1), left(_color), right(_color){};
	
	NODE(int _left, int _right):left(_left), right(_right){};
	
	NODE(int _count, int _left, int _right):count(_count), left(_left), right(_right){};
	
	NODE operator+ (const NODE &object) const{
		return NODE(this->right == object.left ? this->count + object.count -1 : this->count + object.count, this->left, object.right);
	}
	
	friend NODE merge(const NODE &left, const NODE &right){
		return NODE(left.right == right.left ? left.count + right.count - 1 : left.count + right.count, left.left, right.right);
	}
};

void initDfs(int x,int from);
void dfs(int x,int TOP);
void init();
inline int read();
void build(int id, int l, int r);
void update(int id, int l, int r, int color);
NODE query(int id, int l, int r);
int LCA(int a, int b);

vector<int> edge[maxn];
int n, Q, p, cnt(0), color[maxn], dfn[maxn], pos[maxn], size[maxn], son[maxn], dep[maxn], top[maxn], father[maxp][maxn];

struct TREE{
	int l, r;
	NODE data;
	bool lazy;
	TREE():l(0), r(0), lazy(false){};
}tree[maxn << 2];

int main(){
	init();
	initDfs(1, 0);
	dfs(1, 1);
	build(1, 1, n);
	
	while(Q--){
		int order(getchar());
		while(order != 'C' && order != 'Q')
			order = getchar();
			
		if(order == 'C'){
			int x(read()), y(read()), key(read());
			
			while(top[x] != top[y]){
				if(dep[top[x]] < dep[top[y]])
					swap(x, y);
				update(1, dfn[top[x]], dfn[x], key);
				x = father[0][top[x]];
			}
			
			if(dfn[x] > dfn[y])
				swap(x, y);
			update(1, dfn[x], dfn[y], key);
		}else{
			int x(read()), y(read());
			
			NODE result;
			pair<int, int> where;
			
			while(top[x] != top[y]){
				if(dep[top[x]] < dep[top[y]])
					swap(x, y);
				if(where.second < dfn[top[x]]){
					//result = result + query(1, dfn[top[x]], dfn[x]);
					result = merge(result, query(1, dfn[top[x]], dfn[x]));
					where.second = dfn[x];
				}else{
					//result = query(1, dfn[top[x]], dfn[x]) + result;
					result = merge(query(1, dfn[top[x]], dfn[x]), result);
					where.first = dfn[top[x]];
				}
					
				x = father[0][top[x]];
			}
			
			if(dfn[x] > dfn[y])
				swap(x, y);
				
			if(where.second < dfn[x]){
				//result = result + query(1, dfn[x], dfn[y]);
				result = merge(result, query(1, dfn[x], dfn[y]));
				where.second = dfn[x];
			}else{
				//result = query(1, dfn[x], dfn[y]) + result;
				result = merge(query(1, dfn[x], dfn[y]), result);
				where.first = dfn[y];
			}
			
			printf("%d\n", result.count);
		}
	}
	return 0;
}

void init(){
	memset(color, 0, sizeof(color));
	memset(dfn, 0, sizeof(dfn));
	memset(pos, 0, sizeof(pos));
	memset(size, 0, sizeof(size));
	memset(son, 0, sizeof(son));
	memset(dep, 0, sizeof(dep));
	memset(father, 0, sizeof(father));
	
	n = read();
	Q = read();
	
	p = (int)log2(n);
	
	for(int i = 1; i <= n; ++i)
		color[i] = read();
		
	for(int i = 1; i < n; ++i){
		int a(read()), b(read());
		edge[a].emplace_back(b);
		edge[b].emplace_back(a);
	}
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

void initDfs(int x,int from){
	dep[x] = dep[from] + 1;
	father[0][x] = from;
	size[x] = 1;
	
	for(int i = 1; i <= p; ++i)
		father[i][x] = father[i - 1][father[i - 1][x]];
	
	for(const int &iter : edge[x]){
		if(iter == from)
			continue;
		initDfs(iter, x);
		
		size[x] += size[iter];
		
		if(size[iter] > size[son[x]])
			son[x] = iter;
	}
}

void dfs(int x,int TOP){
	top[x] = TOP;
	dfn[x] = ++cnt;
	pos[cnt] = x;
	
	if(!son[x])
		return;
		
	dfs(son[x], TOP);
	
	for(const int &iter : edge[x])
		if(iter != son[x] && iter != father[0][x])
			dfs(iter, iter);
}

int LCA(int a, int b){
	if(dep[a] > dep[b])
		swap(a, b);
	
	for(int t(dep[b] - dep[a]), j(0); t > 0; ++j, t >>= 1)
		if(t & 1)
			b = father[j][b];
	
	if(a == b)
		return a;
	
	for(int j = p; j >= 0 && a != b; --j){
		if(father[j][a] != father[j][b]){
			a = father[j][a];
			b = father[j][b];
		}
	}
	
	return father[0][a];
}

void build(int id, int l, int r){
	tree[id].l = l;
	tree[id].r = r;
	
	if(l == r){
		tree[id].data = NODE(color[pos[r]]);
		return;
	}
	
	int mid((l + r) >> 1);
	
	build(id << 1, l, mid);
	build(id << 1|1, mid + 1, r);
	
	//tree[id].data = tree[id << 1].data + tree[id << 1|1].data;
	tree[id].data = merge(tree[id << 1].data, tree[id << 1|1].data);
}

NODE query(int id, int l, int r){
	if(l <= tree[id].l && tree[id].r <= r)
		return tree[id].data;
		
	if(tree[id].lazy){
		tree[id << 1].data = tree[id].data;
		tree[id << 1|1].data = tree[id].data;
		tree[id << 1].lazy = true;
		tree[id << 1|1].lazy = true;
		tree[id].lazy = false;
	}
		
	int mid((tree[id].l + tree[id].r) >> 1);
	
	if(r <= mid)
		return query(id << 1, l, r);
	if(l > mid)
		return query(id << 1|1, l, r);
		
	//return query(id << 1, l, r) + query(id << 1|1, l, r);
	return merge(query(id << 1, l, r), query(id << 1|1, l, r));
}

void update(int id, int l, int r, int color){
	if(l <= tree[id].l && tree[id].r <= r){
		tree[id].data = NODE(color);
		tree[id].lazy = true;
		return;
	}
	
	if(tree[id].lazy){
		tree[id << 1].data = tree[id].data;
		tree[id << 1|1].data = tree[id].data;
		tree[id << 1].lazy = true;
		tree[id << 1|1].lazy = true;
		tree[id].lazy = false;
	}
	
	int mid((tree[id].l + tree[id].r) >> 1);
	
	if(l <= mid)
		update(id << 1, l, r, color);
	if(r > mid)
		update(id << 1|1, l, r, color);
		
	//tree[id].data = tree[id << 1].data + tree[id << 1|1].data;
	tree[id].data = merge(tree[id << 1].data, tree[id << 1|1].data);
}
