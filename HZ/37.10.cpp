//HZ - 37.10
#include<bits/stdc++.h>

constexpr int maxN = 5e5 + 5, maxK = maxN, maxS = 1e4 + 5;

enum LimitEnum : int {
	EMPTY = -1,
	EQUAL = 1,
	LOWER = 2,
	UPPER = 3
};

typedef std::pair<LimitEnum, int> LimitType;

typedef std::vector<LimitType> LimitSet;

int N_, K_, S_;
int const &N = N_, &K = K_, &S = S_;

int main() {
	std::cin >> N_ >> K_ >> S_;
	
	int const textLength = N, patternLength = K;
	
	std::vector<int> sortedPattern, patternRank(patternLength, -1), lastPos(S + 1, -1), text(textLength), pattern(patternLength);
	
	for(int i = 0; i < textLength; ++i)
		std::cin >> text[i];
		
	for(int i = 0; i < patternLength; ++i)
		std::cin >> pattern[i];
		
	sortedPattern.assign(pattern.begin(), pattern.end());

	std::sort(sortedPattern.begin(), sortedPattern.end());
	
	for(int i = 0; i < patternLength; ++i)
		patternRank[i] = std::distance(sortedPattern.begin(), std::lower_bound(sortedPattern.begin(), sortedPattern.end(), pattern[i])) + 1;
		
	for(int i = 1; i < patternLength; ++i) {
		if(lastPos[pattern[i]])
	}
}
