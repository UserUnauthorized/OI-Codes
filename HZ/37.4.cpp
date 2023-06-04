//HZ - 37.4
//Luogu - P3167
#include <bits/stdc++.h>

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
                                               0, 0, 0, 0, 0,};

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

class ModStr {
public:
    typedef ModStr self;
    typedef stringHash hash;
    typedef size_t sizeType;

    enum strType : int {
        EMPTY = -1, PLAIN = 0, SIMPLE = 1, WILDCARD = 2
    };

    typedef std::pair<strType, hash> dataType;
    typedef std::vector<dataType> container;

private:
    container data;

public:
    ModStr(std::string str) {
        data.emplace_back(EMPTY, hash());

        std::string::iterator now = str.begin(), last = str.begin();

        while (now != str.end()) {
            sizeType pos = std::distance(str.begin(), now);

            if (*now == '*' || *now == '?') {
                if (now != last)
                    data.emplace_back(PLAIN,
                                      hash(str.substr(std::distance(str.begin(), last), std::distance(last, now))));

                data.emplace_back(*now == '*' ? WILDCARD : SIMPLE, hash());
                last = ++now;
            } else {
                ++now;
            }
        }

        if (last != str.end())
            data.emplace_back(PLAIN, hash(str.substr(std::distance(str.begin(), last), std::distance(last, now))));
    }

    bool check(const hash &str) const {
        return dfs(0, 0, str);
    }

protected:
    bool dfs(sizeType thisPos, sizeType strPos, const hash &str) const {
        if (thisPos == data.size() - 1)
            return strPos == str.size();

        if (strPos == str.size())
            return false;

        ++thisPos;
        strType const nowType = data[thisPos].first;

        if (nowType == SIMPLE) {
            return dfs(thisPos, strPos + 1, str);
        } else if (nowType == PLAIN) {
            if (str.check(strPos + 1, data[thisPos].second))
                return dfs(thisPos, strPos + data[thisPos].second.size(), str);
            else
                return false;
        } else {
            for (int i = str.size(); i >= (int) strPos; --i)
                if (dfs(thisPos, i, str))
                    return true;
        }

        return false;
    }
};

int main() {
    std::string tempModStr;

    std::cin >> tempModStr;

    ModStr const mod(tempModStr);

    int n;

    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::string t;

        std::cin >> t;

        std::cout << (mod.check(stringHash(t)) ? "YES\n" : "NO\n");
    }

    std::cout << std::flush;

    return 0;
}
