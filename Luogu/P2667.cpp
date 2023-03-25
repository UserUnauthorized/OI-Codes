//Luogu - P2667
#include<bits/stdc++.h>

#include <iostream>
#include <vector>

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

typedef long long valueType;
constexpr valueType MOD = 1e9 + 9, maxN = 1e5 + 5, MAX = LONG_LONG_MAX;

valueType N_, Q_;
valueType const &N = N_, &Q = Q_;

struct SEGNODE{
	int l, r;
	valueType before, after;
	valueType remain;
	
	bool leaf() const {
		return this->l == this->r;
	}
};

typedef std::array<valueType, maxN> ARRAY;
typedef std::bitset<maxN> BITSET;
std::array<SEGNODE, maxN << 2> tree;
ARRAY source, before;
BITSET dead;

void init();
void build(int id, int l, int r);
void attack(int id, int l, int r, valueType key);
void attack(int id, valueType key);
void push(int id);
valueType query(int id, int pos);

int main(){
//	freopen("attack.in", "r", stdin);
//	freopen("attack.out", "w", stdout);
	init();

	build(1, 1, N);
	
	valueType ans = 0;
	
	for(int i = 0; i < Q; ++i){
		char order;
		std::cin >> order;
		
		if(order == 'A'){
			int l, r;
			valueType a;
			std::cin >> l >> r >> a;
			attack(1, l, r, a);
		} else if(order == 'Q'){
			int x;
			std::cin >> x;
			ans += query(1, x);
			ans %= MOD;
		}
	}
	
	std::cout << (ans % MOD);
	
	return 0;
}

void init(){
	std::cin >> N_ >> Q_;
	
	for(valueType i = 1; i <= N; ++i)
		std::cin >> source[i];
}

void build(int id, int l, int r){
	tree[id].l = l;
	tree[id].r = r;
	tree[id].before = tree[id].after = 0;
	
	if(l == r){
		tree[id].remain = source[r];
		return;
	}
	
	int const mid = (l + r) >> 1;
	
	build(id << 1, l, mid);
	build(id << 1|1, mid + 1, r);
	
	tree[id].remain = std::min(tree[id << 1].remain, tree[id << 1|1].remain);
}

void attack(int id, int l, int r, valueType key){
	if(l <= tree[id].l && tree[id].r <= r){
		attack(id, key);
		return;
	}
	
	push(id);
	
	int const mid = (tree[id].l + tree[id].r) >> 1;
	
	if(l <= mid)
		attack(id << 1, l, r, key);
	if(r > mid)
		attack(id << 1|1, l, r, key);
		
	tree[id].remain = std::min(tree[id << 1].remain, tree[id << 1|1].remain);
}

void attack(int id, valueType key){
	if(tree[id].remain == MAX){
		tree[id].after += key;
		return;
	}
	
	if(key < tree[id].remain){
		tree[id].remain -= key;	
		tree[id].before += key;
		tree[id].after += key;
		return;
	}
	
	
	
	if(tree[id].leaf()){
		tree[id].before += key;
		before[tree[id].r] = tree[id].before;
		tree[id].remain = MAX;
		tree[id].after = 0;
		dead[tree[id].r] = true;
		return;
	}
	
	push(id);
	
	attack(id << 1, key);
	attack(id << 1|1, key);
	
	tree[id].remain = std::min(tree[id << 1].remain, tree[id << 1|1].remain);
}

void push(int id){
	tree[id << 1].before += tree[id].before;
	tree[id << 1|1].before += tree[id].before;
	
	if(tree[id << 1].remain != MAX)
		tree[id << 1].remain -= tree[id].before;
	
	if(tree[id << 1|1].remain != MAX)
		tree[id << 1|1].remain -= tree[id].before;
	
	tree[id << 1].after += tree[id].after;
	tree[id << 1|1].after += tree[id].after;
	tree[id].before = tree[id].after = 0;
}

valueType query(int id, int pos){
	if(tree[id].leaf())
		return dead[tree[id].r] ? before[tree[id].r] + (tree[id].after << 1) : tree[id].before;
		
	push(id);
	
	int const mid = (tree[id].l + tree[id].r) >> 1;
	
	if(pos <= mid)
		return query(id << 1, pos);
	else 
		return query(id << 1|1, pos);
}
