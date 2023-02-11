//HZ - 36.8
//Luogu - P4396
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e5 + 5, maxM = 1e6 + 5;
array<int, maxN> belongN, source, cnt;

struct Query{
	int l;
	int r;
	int a;
	int b;
	int pos;
	
	Query():l(-1),r(-1),a(-1),b(-1),pos(-1){};
	
	Query(int _l_, int _r_, int _a_, int _b_, int _pos_):l(_l_), r(_r_), a(_a_), b(_b_), pos(_pos_){};
	
	bool operator<(Query const &Object) const{
		if(belongN[this->l] != belongN[Object.l])
			return this->l < Object.l;
			
		if(belongN[this->r] != belongN[Object.r])
			return this->r < Object.r;
			
		return this->pos < Object.pos;
	}
};

array<Query, maxM> query;

void init();
/*inline void add(int pos);
inline void del(int pos);
inline void update(int pos, NODE x);
inline int lowBit(int x);
NODE getSum(int pos);*/

int N_, M_,/* D_,*/ block_;
int const &N = N_, &M = M_, &D = N_, &block = block_;

int main(){
	init();
	
	int nowL(1), nowR(0);
	
	for(int i = 0; i < M; ++i){
		int const &l = query[i].l, &r = query[i].r, &a = query[i].a, &b = query[i].b;
		
		while(nowL > l)
			add(source[--nowL]);
		while(nowL < l)
			del(source[nowL++]);
		while(nowR < r)
			add(source[++nowR]);
		while(nowR > r)
			del(source[nowR]--);
			
	}
	
	for(int i = 0; i < M; ++i)
		cout << ans[i].sum << ' ' << ans[i].cnt << '\n';
	
	return 0;
}

void init(){
	cin >> N_ >> M_;
	
	block_ = sqrt(N);
	
	for(int i = 1; i <= N; ++i){
		cin >> source[i];
		belongN[i] = (i - 1) / block + 1;
		D_ = max(D, source[i]);
	}
	
	for(int i = 0; i < M; ++i){
		int l, r, a, b;
		cin >> l >> r >> a >> b;
		query[i] = Query(l, r, a, b, i);
	}
	
	sort(query.begin(), query.begin() + M);
}
