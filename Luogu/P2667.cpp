//Luogu - P2667
#include<bits/stdc++.h>

typedef unsigned int valueType;
typedef unsigned int posType;
constexpr valueType MOD = 1e9 + 9, maxN = 1e5 + 5;

struct TREE{
	posType l, r;
	valueType lazy;
	valueType remain;
};

valueType N, Q;

std::array<TREE, maxN << 2> tree;
std::array<valueType, maxN> source;

void build(valueType id, posType l, posType r);
void arrack(valueType id, posType l, posType r, valueType key);
valueType query(valueType id, posType pos);

void init();

int main(){
	init();
}

void init(){
	std::cin >> N >> Q;
	
	for(int i = 1; i <= N; ++i)
		std::cin >> source[i];
}
