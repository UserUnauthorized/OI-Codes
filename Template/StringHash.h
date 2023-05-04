#ifndef OI_CODES_STRINGHASH_H
#define OI_CODES_STRINGHASH_H

#include <array>
#include <vector>
#include <string>

typedef std::array<long long, 256> tableType;

constexpr static const tableType HASH_TABLE = {0,
                                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                               0, 0, 0, 0, 1, 2, 3, 4, 5, 6,
                                               7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                                               17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
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
                                               0, 0, 0, 0, 0, };

constexpr static const size_t HASH_CNT = 3;
constexpr static const std::array<long long, HASH_CNT> HASH_MOD = {1000000007, 1000000009, 1000000021};
constexpr static const std::array<long long, HASH_CNT> HASH_BASE = {31, 1331, 87481};

class stringHash {
public:
    typedef std::string dataType;
    typedef long long hashType;
    typedef size_t sizeType;
    typedef std::vector<hashType> hashListType;

protected:
    dataType data;
    std::array<hashListType, HASH_CNT> hash;
    std::array<hashListType, HASH_CNT> pow;

public:
    stringHash() = default;

    explicit stringHash(dataType _data_) : data(std::move(_data_)) {
        sizeType const size = data.size();

        for (sizeType i = 0; i < HASH_CNT; ++i) {
            pow[i].resize(size + 1);
            pow[i][0] = 1;

            for (sizeType j = 0; j < size; ++j)
                pow[i][j + 1] = pow[i][j] * HASH_BASE[i] % HASH_MOD[i];
        }

        for (sizeType i = 0; i < HASH_CNT; ++i) {
            hash[i].resize(size + 1);
            hash[i][0] = 0;
            for (sizeType j = 0; j < size; ++j) {
                hash[i][j + 1] = (hash[i][j] * HASH_BASE[i] + HASH_TABLE[data[j]]) % HASH_MOD[i];
            }
        }
    }

    hashType getSubHash(sizeType i) const {
        return hash[i][this->size()];
    }

    hashType getSubHash(sizeType l, sizeType r, sizeType i) const {
//        assert(0 < l && l <= r && r <= this->size());
        return (hash[i][r] - hash[i][l - 1] * pow[i][r - l + 1] % HASH_MOD[i] + HASH_MOD[i]) % HASH_MOD[i];
    }

    sizeType size() const {
        return data.size();
    }

    bool check(sizeType pos, const stringHash &str) const {
        sizeType const size = str.size();

        if (pos + size - 1 > this->size())
            return false;

        for (sizeType i = 0; i < HASH_CNT; ++i) {
            if (getSubHash(pos, pos + size - 1, i) != str.getSubHash(i)) {
                return false;
            }
        }
        return true;
    }
};

#endif //OI_CODES_STRINGHASH_H
