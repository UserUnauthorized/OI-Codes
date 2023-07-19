//Luogu - P5325
#include<bits/stdc++.h>

typedef long long valueType;

constexpr valueType MOD = 1e9 + 7;

class ID {
public:
	typedef std::vector<valueType> container;
	typedef const container &containerReference;
	
private:
	valueType size, limit;
	
	container less, great, list;
	
public:
	ID(valueType n) : size(n), limit(std::floor(std::sqrt((long double)size))), less(limit + 1), great(limit + 1) {
		for(valueType i = 1; i <= size; i = size / (size / i) + 1)
			list.push_back(n / i);
			
		list.push_back(0);	
		
		std::reverse(list.begin(), list.end());
		
		valueType count = 0;
		
		for(auto const &iter : list) {
			if(iter <= limit)
				less[iter] = ++count;
			else
				great[size / iter] = ++count;
		}
	}
	
	valueType get(valueType n) const {
		return n <= limit ? less[n] : great[size / n];
	}
	
	containerReference data() const {
		return list;
	}
};

class LineSieve {
public:
    typedef std::vector<valueType> container;

private:
    valueType size, primeCount;
    container minFactorList;
    container primeList;
    container primeSum1, primeSum2;

public:
    explicit LineSieve(valueType _size_) : size(_size_), minFactorList(_size_ + 1) {
    	primeList.push_back(0);
    	primeSum1.push_back(0);
    	primeSum2.push_back(0);
    	
        for (valueType i = 2; i <= size; ++i) {
            if (minFactorList[i] == 0) {
                primeList.push_back(i);
                minFactorList[i] = i;
                
                primeSum1.push_back((primeSum1.back() + i) % MOD);
                primeSum2.push_back((primeSum2.back() + i * i) % MOD);
            }

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                minFactorList[t] = iter;

                if (i % iter == 0)
                    break;
            }
        }
        
        primeCount = primeList.size() - 1;
    }

    valueType minFactor(valueType x) const {
        if (x > size)
            throw std::range_error("Larger than Size.");

        if (x < 1)
            throw std::range_error("Too small.");

        return minFactorList[x];
    }

    bool isPrime(valueType x) const {
        if (x > size)
            throw std::range_error("Larger than Size.");

        if (x < 1)
            throw std::range_error("Too small.");

        return minFactorList[x] == x;
    }

	valueType count() const {
		return primeCount;
	}
		
	valueType sum1(valueType n) const {
		return primeSum1[n];
	}
	
	valueType sum2(valueType n) const {
		return primeSum2[n];
	}
	
    const container &getPrime() const {
        return primeList;
    }
};
