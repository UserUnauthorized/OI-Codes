//HZ - 36.8
//Luogu - P4396
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e5 + 5;
array<int, maxN> belong, source;

struct Query{
	int l;
	int r;
	int a;
	int b;
	int pos;
	
	Query():l(-1),r(-1),a(-1),b(-1),pos(-1){};
	
	Query(int _l_, int _r_, int _a_, int _b_, int _pos_):l(_l_), r(_r_), a(_a_), b(_b_), pos(_pos_){};
	
	bool operator<(Query const &Object) const{
		if(belong[this->l] != belong[Object.l])
			return this->l < Object.l;
			
		if(belong[this->r] != belong[Object.r])
			return this->r < Object.r;
			
		return this->pos < Object.pos;
	}
};

struct NODE{
	int sum;
	int cnt;
	
	NODE():sum(0),cnt(0){};
	NODE(int _sum_, int _cnt_):sum(_sum_),cnt(_cnt_){};
	
	NODE operator+(NODE const &Object) const{
		return NODE(this->sum + Object.sum, this->cnt + Object.cnt);
	}
	
	void operator+=(NODE const &Object){
		*this = *this + Object;
	}
};

array<Query, maxN> query;
array<NODE, maxN> tree;

void insert(int pos, int key);
NODE getSum(int pos);
void init();

int N_, M, D_;
int const &N = N_, &D = D_;

int main(){
	init();
}

void init(){
	
}
