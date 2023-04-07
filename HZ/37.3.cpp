//HZ - 37.3
//Luogu - P4591

#include<bits/stdc++.h>

typedef unsigned long long hashType;
typedef long long valueType;
constexpr valueType maxK = 103, maxS = 1e4 + 5, maxA = 12;
constexpr hashType base = 1331;

valueType K_;

valueType const &K = K_;

std::array<std::array<valueType, maxS>, maxK> dp;

std::array<std::array<hashType, maxA>, maxK> subHash;

std::array<std::array<std::string, maxA>, maxK> subStr;

std::string source;

std::array<hashType, maxS> sourceHash;

std::array<int, maxK> size;

hashType table(char ch);

void init();

int main() {
	init();
}

void init() {
	std::cin >> K_ >> source;
	
	
}

hashType table(char ch){
	return ch - 'a' + 1;
}
