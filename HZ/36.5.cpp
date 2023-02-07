//HZ - 36.5
//HZ - 36.6
//Luogu - P1903
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

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

constexpr int maxN = 133333 + 5, maxD = 1e6 + 5;;
typedef int valueType;
array<int, maxN> belong;
array<valueType, maxN> source, value, out;
array<valueType, maxD> cnt;

inline void add(valueType x);
inline void del(valueType x);

struct Query{
	int l;
	int r;
	int pos;
	int stamp;
	
	Query():l(-1), r(-1), pos(-1), stamp(-1){};
	Query(int _l_, int _r_, int _pos_, int _stamp_):l(_l_), r(_r_), pos(_pos_), stamp(_stamp_){};
	
	bool operator<(const Query &Object){
		if(belong[this->l] != belong[Object.l])
			return this->l < Object.l;
			
		if(belong[this->r] != belong[Object.r])
			return this->r < Object.r;
			
		return this->pos < Object.pos;
	}
};

struct Modify{
	int pos;
	int pre;
	int now;
	
	void apply(int l, int r){
		if(l <= this->pos && this->pos <= r){
			del(this->pre);
			add(this->now);
		}
		
		source[this->pos] = this->now;
	}
	
	void revoke(int l, int r){
		if(l <= this->pos && this->pos <= r){
			del(this->now);
			add(this->pre);
		}
		
		source[this->pos] = this->pre;
	}
	
	Modify():pos(-1), pre(-1), now(-1){};
	Modify(int _pos_, int _now_, int _pre_):pos(_pos_), pre(_pre_), now(_now_){};
};

array<Query, maxN> query;
array<Modify, maxN> modify;

int N_, M, K_, block_, queryCount(0), modifyCount(0), ans(0);
int const &N = N_, &K = K_, &block = block_;

void init();
inline void add(valueType x);
inline void del(valueType x);

int main(){
	init();
	
	int nowL(1), nowR(0), modifyStamp(0);
	for(int i = 1; i <= queryCount; ++i){
//		debug(nowL, nowR, modifyStamp, query[i].l, query[i].r, query[i].pos, query[i].stamp);
		while(nowL > query[i].l)
			add(source[--nowL]);
		while(nowL < query[i].l)
			del(source[nowL++]);
			
		while(nowR < query[i].r)
			add(source[++nowR]);
		while(nowR > query[i].r)
			del(source[nowR--]);
		
		while(modifyStamp < query[i].stamp)
			modify[++modifyStamp].apply(nowL, nowR);
		while(modifyStamp > query[i].stamp)
			modify[modifyStamp--].revoke(nowL, nowR);
		
		out[query[i].pos] = ans;
	}
	
	for(int i = 1; i <= queryCount; ++i)
		cout << out[i] << '\n';

	return 0;
}

void init(){
	cin >> N_ >> M;
	
	block_ = pow(N, (double)2 / (double)3);
	K_ = ceil((double)N / (double)block);
	
	for(int i = 1; i <= N; ++i){
		cin >> source[i];
		value[i] = source[i];
		belong[i] = (i - 1) / block + 1;
	}
	
	for(int i = 0; i < M; ++i){
		char order;
		cin >> order;
		if(order == 'Q'){
			int l, r;
			cin >> l >> r;
			query[++queryCount] = Query(l, r, queryCount, modifyCount);
//			debug(query[queryCount].l, query[queryCount].r, query[queryCount].pos, query[queryCount].stamp, queryCount);
		} else {
			int pos, x;
			cin >> pos >> x;
//			debug(pos, x);
			modify[++modifyCount] = Modify(pos, value[pos] = x, value[pos]);
//			debug(modify[1].pos, modify[1].pre, modify[1].now);
		}
	}
	
	sort(query.begin() + 1, query.begin() + queryCount + 1);
}

void add(valueType x){
//	debug(x, cnt[x], ans);
	if(!cnt[x]++)
		++ans;
//	debug(ans);
}

void del(valueType x){
	if(!--cnt[x])
		--ans;
}
