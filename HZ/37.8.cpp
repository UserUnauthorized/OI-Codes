//HZ - 37.8
//Luogu - P4824
#include <bits/stdc++.h>
#include <ext/rope>

constexpr int maxN = 1e6 + 5;

std::array<int, maxN> next, prefix, match;
using namespace __gnu_cxx;
int main() {
    std::string text, pattern;

    std::cin >> text >> pattern;

    int const patternLength = (int)pattern.length();
    int const textLength = (int)text.length();
	rope<int> data;
	
    for (int i = 1; i < textLength; ++i)
    	next[i - 1] = i;
	
	for(int i = 0; i < textLength; ++i)
		data.push_back(i);
    
    for (int i = 1; i < patternLength; ++i) {
        int j = prefix[i - 1];

        while (j > 0 && pattern[i] != pattern[j])
            j = prefix[j - 1];

        if (pattern[i] == pattern[j])
            ++j;

        prefix[i] = j;
    }

	int j = 0;

    for (int i = 0; i < textLength; ++i) {

        while (j > 0 && text[i] != pattern[j])
            j = prefix[j - 1];


        if (text[i] == pattern[j])
            ++j;

        match[i] = j;

        if (j == patternLength) {
            auto const nowPos = std::lower_bound(data.begin(), data.end(), i);
            
            if(std::distance(data.begin(), nowPos) <= patternLength)
            	j = 0;
            else
            	j = match[*(nowPos - patternLength)];
            
            data.erase(std::distance(data.begin(), nowPos + 1 - patternLength), (size_t)patternLength);
        }
    }

	for(auto const &iter : data)
		std::cout << text[iter];
		
	std::cout << std::flush;
	
	return 0;
}

/*
Hack:

abaabbaacc
ab
*/
