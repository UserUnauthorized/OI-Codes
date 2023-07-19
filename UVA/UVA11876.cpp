//Luogu - UVA11876
#include<bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

constexpr valueType maxN = 1e6 + 5;

class LineSieve {
public:
    typedef ValueVector container;
    typedef std::vector<bool> bitset;

private:
    valueType size;
    bitset isPrime;
    container primeList;
    container minCount, data;

public:
    explicit LineSieve(valueType _size_) : size(_size_), isPrime(_size_ + 1, true),
                                           minCount(_size_ + 1), data(_size_ + 1) {
        primeList.reserve((size_t) std::floor(std::log((long double) (_size_ + 1))));
        data[1] = 1;
        for (valueType i = 2; i <= size; ++i) {
            if (isPrime[i]) {
                primeList.push_back(i);
                minCount[i] = 1;
                data[i] = 2;
            }

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                isPrime[t] = false;

                if (i % iter == 0) {
					minCount[t] = minCount[i] + 1;

                    data[t] = data[i] / (minCount[i] + 1) * (minCount[t] + 1);

                    break;
                } else {
					minCount[t] = 1;

                    data[t] = data[i] * 2;
                }
            }
        }
    }
    
    valueType F(valueType x) const {
        if (x > size)
            throw std::range_error("Larger than Size.");

        if (x < 0)
            throw std::range_error("Too small.");

        return data[x];
    }
};

int main() {
	LineSieve Euler(maxN);
	
	ValueVector N(maxN + 1);
	
	auto end = N.begin();
	
	*end = 1;
	
	while(end != N.end()) {
		valueType const prev = *end;
		
		*(++end) = prev + Euler.F(prev);
		
		if(*end > maxN)
			break;
	}

	valueType T;
	
	std::cin >> T;
	
	for(valueType i = 1; i <= T; ++i) {
		valueType l, r;
		
		std::cin >> l >> r;
		
		valueType const result = std::distance(std::upper_bound(N.begin(), end, l - 1), std::upper_bound(N.begin(), end, r));
		
		std::cout << "Case " << i << ": " << result << '\n';
	}
	
	std::cout << std::flush;
	
	return 0;
}
