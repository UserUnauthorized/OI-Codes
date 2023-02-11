//HZ - 36.9
//Luogu - P2709
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 5e4 + 5;
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
array<valueType, maxN> out;

void init();
inline void add(int x);
inline void del(int x);

int N_, M_, K_, block_, ans(0);
int const &N = N_, &M = M_, &K = K_, &block = block_;

int main(){
	init();
	
	int nowL(1), nowR(0);
	
	for(int i = 0; i < M; ++i){
		int const &l = query[i].l, &r = query[i].r;
		
		while(nowL < l)
			del(source[nowL++]);
		while(nowL > l)
			add(source[--nowL]);
		while(nowR > r)
			del(source[nowR--]);
		while(nowR < r)
			add(source[++nowR]);
			
		out[query[i].pos] = ans;
	}
	
	for(int i = 0; i < M; ++i)
		cout << out[i] << '\n';
	
	return 0;
}

void init(){
	cin >> N_ >> M_ >> K_;
	
	block_ =sqrt(N);
	
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

void add(int x){
	++ans += 2 * cnt[x]++;
}

void del(int x){
	++ans -= 2 * cnt[x]--;
}
