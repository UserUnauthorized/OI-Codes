//HZ - 37.10
#include<bits/stdc++.h>

constexpr int maxN = 5e5 + 5, maxS = 1e4 + 5;

enum LimitEnum : int {
	EMPTY = -1;
	EQUAL = 1;
	LOWER = 2;
	UPPER = 3;
};

typedef std::pair<LimitEnum, int> LimitType;

typedef std::array<LimitType, 2> LimitSet;

std::array<LimitSet, maxS> limit;
std::array<>
