//HZ - 35.8
#include<bits/stdc++.h>

typedef int valueType;
typedef long double realType;
typedef std::vector<realType> realVector;
typedef std::vector<valueType> valueVector;

int main() {
	int N;
	
	std::cin >> N;
	
	valueVector source(N);
	
	for(auto &iter : source)
		std::cin >> iter;
		
	valueVector point(source);
	
	std::sort(point.begin(), point.end());
	point.erase(std::unique(point.begin(), point.end()), point.end());
	
	for(auto &iter : source)
		iter = std::distance(point.begin(), std::lower_bound(point.begin(), point.end(), iter));
		
	valueVector count(point.size(), 0), sum(point.size());
	
	for(auto const &iter : source)
		++count[iter];
		
	std::partial_sum(count.begin(), count.end(), sum.begin());
}
