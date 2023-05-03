//HZ - 37.3
//Luogu - P4591
#include <bits/stdc++.h>

#include <utility>

class stringHash {
public:
    typedef stringHash self;
    typedef std::string dataType;
    typedef long long hashType;
    typedef size_t sizeType;
    typedef std::vector<hashType> hashListType;
    typedef std::array<hashType, 256> tableType;

    constexpr static const tableType table = {0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 1, 2, 3, 4, 5, 6,
                                              7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                              17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 1, 2, 3, 4,
                                              5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                                              15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
                                              25, 26, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0,};

    constexpr static const size_t HASH_CNT = 3;
    constexpr static const std::array<hashType, HASH_CNT> HASH_MOD = {1000000007, 1000000009, 1000000021};
    constexpr static const std::array<hashType, HASH_CNT> HASH_BASE = {31, 1331, 87481};

protected:
    dataType data;
    std::array<hashListType, HASH_CNT> hash;

public:
    stringHash() = default;

    explicit stringHash(dataType _data_) : data(std::move(_data_)) {
        sizeType const size = data.size();

        for (sizeType i = 0; i < HASH_CNT; ++i) {
            hash[i].resize(size + 1);
            hash[i][0] = 0;
            for (sizeType j = 0; j < size; ++j) {
                hash[i][j + 1] = (hash[i][j] * self::HASH_BASE[i] + self::table[data[j]]) % self::HASH_MOD[i];
            }
        }
    }

    hashType getSubHash(sizeType i) const {
        return hash[i][this->size()];
    }

    hashType getSubHash(sizeType l, sizeType r, sizeType i) const {
        return (hash[i][r] - hash[i][l] * (hashType) pow((double) self::HASH_BASE[i], (double) (r - l)) % self::HASH_MOD[i] +
                self::HASH_MOD[i]) % self::HASH_MOD[i];
    }

    sizeType size() const {
        return data.size();
    }

    bool check(size_t pos, const stringHash &str) const {
        sizeType const size = str.size();

        for (sizeType i = 0; i < HASH_CNT; ++i) {
            if (getSubHash(pos, pos + size, i) != str.getSubHash(i)) {
                return false;
            }
        }
        return true;
    }
};

typedef long long valueType;
constexpr valueType MOD = 1000000007, maxK = 12, maxS = 10005;

std::array<std::array<valueType, maxS>, 2> dp;

valueType K_;
valueType const &K = K_;

int main() {
    std::cin >> K_;

    std::string str;
    std::cin >> str;
    stringHash S(str);
    size_t const size = S.size();

    std::array<std::queue<size_t>, 2> que;

    for (int k = 0; k < K; ++k) {
        size_t const now = k & 1, pre = now ^ 1;

        std::fill(dp[now].begin(), dp[now].end(), 0);

        size_t A;

        std::cin >> A;

        std::vector<stringHash> subStr(A);

        for (size_t i = 0; i < A; ++i) {
            std::string temp;
            std::cin >> temp;
            subStr[i] = stringHash(temp);
        }

        for (size_t pos = 0; pos < size; ++pos)
            for (size_t i = 0; i < A; ++i)
                if (S.check(pos, subStr[i]))
                    dp[now][pos + subStr[i].size()] = (dp[now][pos + subStr[i].size()] + dp[pre][pos]) % MOD;


    }

    std::cout << dp[(K & 1) ^ 1][size];

    return 0;
}