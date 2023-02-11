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
	
	Query():l(-1), r(-1){};
	Query(int _l_, int _r_):l(_l_), r(_r_){};
	
	bool operator<(Query const &Object) const{
		if(belong[this->l] != belong[Object.l])
			return this->l < Object.l;
			
		if(belong[this->r] != belong[Object.r])
			return this->r < Object.r;
			
		return this->pos < Object.pos;
	}
};
