//Luogu - P2667
#include<bits/stdc++.h>
typedef long long valueType;
constexpr valueType MOD = 1e9 + 9, maxN = 1e5 + 5;

valueType N_, Q_;
valueType const &N = N_, &Q = Q_;

struct SEGNODE{
	int l, r;
	valueType lazy;
	valueType remain;
};

typedef std::array<valueType, maxN> ARRAY;
ARRAY source;

namespace before{
	std::array<::SEGNODE, maxN << 2> tree;
	ARRAY const &source = ::source;
	
	void build(int id, int l, int r){
		tree[id].l = l;
		tree[id].r = r;
		
		if(l == r){
			tree[id].remain = 
		}
		
		int const mid = (l + r) >> 1;
	}
}
