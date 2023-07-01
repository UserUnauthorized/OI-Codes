//HZ - 48.2
//Luogu - P3312
#include <bits/stdc++.h>

typedef unsigned long long valueType;
typedef std::vector<valueType> ValueVector;
constexpr valueType maxN = 1e5 + 5;
constexpr valueType MOD = (valueType) 1 << 31;

class TreeArray {
public:
    typedef int sizeType;

private:
    sizeType size;

    ValueVector data;

    ValueVector tree;


    static const sizeType constexpr shifting = 0;

    static sizeType lowBit(sizeType x) {
        return x & -x;
    }

public:
    TreeArray() : size(0), data(0, 0), tree(0, 0) {};

    explicit TreeArray(sizeType N) : size(N + shifting), data(size, 0), tree(size, 0) {};

    void resize(sizeType N) {
        size = N + shifting;

        data.resize(size, 0);
        tree.resize(size, 0);
    }

    void insert(sizeType pos, valueType key) {
        pos = pos + shifting;

        data[pos] += key;

        while (pos < size) {
            tree[pos] += key;
            pos += lowBit(pos);
        }
    }

    valueType sum(sizeType pos) const {
        pos = pos + shifting;

        valueType result = 0;

        while (pos > 0) {
            result = result + tree[pos];
            pos -= lowBit(pos);
        }

        return result;
    }
};

class LineSieve {
public:
    typedef std::vector<valueType> container;
    typedef std::vector<bool> bitset;
    typedef std::pair<valueType, valueType> element;
    typedef std::vector<element> dataSet;
    typedef dataSet::iterator iterator;

private:
    valueType size, A;
    bitset isPrime;
    container primeList;
    container mobius, data, minFactor;
    dataSet sortedData;
    iterator lastEnd;
    TreeArray sum;

public:
    explicit LineSieve(valueType _size_) : size(_size_), A(0), isPrime(_size_ + 1, true), mobius(_size_ + 1),
                                           data(_size_ + 1), minFactor(_size_ + 1), sortedData(),
                                           sum((int) _size_ + 1) {
        primeList.reserve((size_t) std::floor(std::log((long double) (_size_ + 1))));
        sortedData.reserve(size);
        mobius[1] = 1, data[1] = 1;

        sortedData.emplace_back(1, 1);

        for (valueType i = 2; i <= size; ++i) {
            if (isPrime[i]) {
                primeList.push_back(i);
                mobius[i] = -1;
                data[i] = i + 1;
                minFactor[i] = i;
            }

            for (auto const &iter: primeList) {
                valueType const t = i * iter;

                if (t > size)
                    break;

                isPrime[t] = false;

                if (i % iter == 0) {
                    mobius[t] = 0;
                    minFactor[t] = minFactor[i] * iter;

                    if (minFactor[t] == t) {
                        data[t] = data[i] + t;
                    } else {
                        data[t] = data[i / minFactor[i]] * data[minFactor[t]];
                    }

                    break;
                } else {
                    mobius[t] = -mobius[i];
                    minFactor[t] = iter;
                    data[t] = data[i] * data[iter];
                }
            }

            sortedData.emplace_back(data[i], i);
        }

        std::sort(sortedData.begin(), sortedData.end());

        lastEnd = sortedData.begin();
    }

    void push(valueType a) {
        if (a <= A)
            return;

        iterator const newPos = std::upper_bound(lastEnd, sortedData.end(), std::make_pair(a + 1, (valueType) 0));

        for (; lastEnd != newPos; ++lastEnd) {
            valueType const x = lastEnd->second;
            valueType const value = lastEnd->first;

            for (valueType i = 1; i * x <= size; ++i)
                sum.insert((int) (i * x), value * mobius[i]);
        }
    }

    valueType Ans(valueType x) const {
        if (x > size)
            throw std::range_error("Larger than Size.");

        return sum.sum((int) x);
    }
};

struct Query {
    int id;
    valueType n, m;
    int a;

    friend std::istream &operator>>(std::istream &os, Query &object) {
        os >> object.n >> object.m >> object.a;

        return os;
    }

    friend bool operator<(const Query &left, const Query &right) {
        return left.a < right.a;
    }
};

int main() {
    valueType T;

    std::cin >> T;

    LineSieve Euler(maxN);

    typedef std::function<valueType(valueType, valueType)> solveFunction;

    solveFunction solve = [&Euler](valueType N, valueType M) -> valueType {
        if (N > M)
            std::swap(N, M);

        valueType result = 0;

        valueType l = 1, r;

        while (l <= N) {
            r = std::min(N / (N / l), M / (M / l));

            result = result + (Euler.Ans(r) - Euler.Ans(l - 1)) * (N / l) * (M / l);

            l = r + 1;
        }

        return (result % MOD);
    };

    ValueVector ans(T);

    std::vector<Query> query(T);

    for (int i = 0; i < T; ++i) {
        std::cin >> query[i];

        query[i].id = i;
    }

    std::sort(query.begin(), query.end());

    for (auto const &iter: query) {
        if (iter.a <= 0) {
            ans[iter.id] = 0;

            continue;
        }

        Euler.push(iter.a);

        ans[iter.id] = solve(iter.n, iter.m);
    }

    for (auto const &iter: ans)
        std::cout << iter << '\n';

    std::cout << std::flush;

    return 0;
}