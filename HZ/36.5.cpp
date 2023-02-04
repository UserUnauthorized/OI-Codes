//HZ - 36.5
//HZ - 36.6
//Luogu - P1903
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 133333 + 5, maxD = 1e6 + 5;;
typedef int valueType;
array<int, maxN> belong;
array<valueType, maxN> source, value;
array<valueType, maxD> cnt;

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
	
	void apply(){
		del(this->pre);
		add(this->now);
		source[this->pos] = this->now;
	}
	
	void revoke(){
		del(this->now);
		add(this->pre);
		source[this->pos] = this->pre;
	}
	
	Modify():pos(-1), pre(-1), now(-1){};
	Modify(int _pos_, int _pre_, int _now_):pos(_pos_), pre(_pre_), now(_now_){};
};

array<Query, maxN> query;
array<Modify, maxN> modify;

int N_, M, K_, block_ queryCount(0), modifyType(0), ans(0);
int const &N = N_, &K = K_, &block = block_;

void init();
inline void add(int x);
inline void del(int x);

int main(){
	init();
	
	add(source[1]);
	int nowL(1), nowR(1), modifyStamp(0);
	for(int i = 1; i <= queryCount; ++i){
		while()
	}
}

void init(){
	cin >> N_ >> M;
	
	block_ = sqrt(n);
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
			query[++queryCount] = Query(l, r,/* TAG */ queryCount, modifyCount);
		} else {
			int pos, x;
			cin >> pos >> x;
			modify[++modifyCount] = Modify(pos, value[pos], value[pos] = x);
		}
	}
	
	sort(query + 1, query + queryCount + 1);
}

void add(int x){
	if(cnt[x]++)
		++ans;
}

void del(int x){
	if(--cnt[x])
		--ans;
}
