//HZ - 36.10
//Luogu - P1494
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 5e4 + 5;

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

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

typedef long long valueType;
array<valueType, maxN> source, belong, cnt;

struct Query{
	int l;
	int r;
	int pos;

	Query():l(-1), r(-1), pos(-1){};
	Query(int _l_, int _r_, int _pos_):l(_l_), r(_r_), pos(_pos_){};
	
	bool operator<(Query const &Object) const{
		if(belong[this->l] != belong[Object.l])
			return this->l < Object.l;
			
		if(belong[this->r] != belong[Object.r])
			return this->r < Object.r;
			
		return this->pos < Object.pos;
	}
};

array<Query, maxN> query;
array<valueType, maxN> out, now;

void init();
inline void add(valueType x);
inline void del(valueType x);
inline valueType solve(valueType x);

valueType N_, M_, block_, ans(0);
valueType const &N = N_, &M = M_, &block = block_;

int main(){
//	freopen("P1494_1.in", "r", stdin);
//	freopen("P1494_1.ans", "w", stdout);
//	freopen("P1494_1.err", "w", stderr);
	init();
	
	int nowL(1), nowR(0);
	
	for(int i = 0; i < M; ++i){
		int const &l = query[i].l, &r = query[i].r;
		
		if(l == r){
			out[query[i].pos] = 0;
			continue;
		}
		
		while(nowL < l)
			del(source[nowL++]);
		while(nowL > l)
			add(source[--nowL]);
		while(nowR > r)
			del(source[nowR--]);
		while(nowR < r)
			add(source[++nowR]);
		
		now[query[i].pos] = i;
		out[query[i].pos] = ans;
//		debug(query[i].pos, out[query[i].pos]);
	}
	
	for(int i = 0; i < M; ++i){
		valueType a(out[i]), b(solve(query[now[i]].r - query[now[i]].l + 1));
		b = max(b, (valueType)1);
		valueType g = __gcd(a, b);
//		debug(i, a, b, g);
		a /= g;
		b /= g;
		if(a == 0)
			b = 1;
//		debug(a, b);
		cout << a << '/' << b << '\n';
	}
		
	
	return 0;
}

void init(){
	cin >> N_ >> M_;
	
	block_ = sqrt(N);
	
	for(int i = 1; i <= N; ++i){
		cin >> source[i];
		belong[i] = (i - 1) / block + 1;
	}
	
	for(int i = 0; i < M; ++i){
		int l, r;
		cin >> l >> r;
		query[i] = Query(l, r, i);
	}
	
	sort(query.begin(), query.begin() + M);
}

void add(valueType x){
	ans -= solve(cnt[x]);
	ans += solve(++cnt[x]);
}

void del(valueType x){
	ans -= solve(cnt[x]);
	ans += solve(--cnt[x]);
}

valueType solve(valueType x){
	if(x < 2)
		return 0;
	return x * (x - 1) / 2;
}
