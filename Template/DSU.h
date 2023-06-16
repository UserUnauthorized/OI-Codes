#ifndef OI_CODES_DSU_H
#define OI_CODES_DSU_H

#include<vector>
#include<algorithm>

class DSU {
public:
    typedef int valueType;
    typedef std::vector<valueType> ValueVector;

private:
    valueType N;

    std::vector<int> father, size;

public:
    DSU(valueType n) : N(n), father(N, 0), size(N, 0) {
        std::iota(father.begin(), father.end(), 0);

        std::fill(size.begin(), size.end(), 1);
    }

    void resize(valueType n) {
        N = n;

        father.resize(N, 0);
        size.resize(N);

        std::iota(father.begin(), father.end(), 0);

        std::fill(size.begin(), size.end(), 1);
    }

    int find(int x) {
        return father[x] == x ? x : father[x] = find(father[x]);
    }

    void unite(int x, int y) {
        x = find(x), y = find(y);

        if (x == y) return;

        if (size[x] < size[y]) std::swap(x, y);

        father[y] = x;
        size[x] += size[y];
    }

    void unite(int x, int y, ValueVector &data) {
        x = find(x), y = find(y);

        if (x == y) return;

        if (size[x] < size[y]) std::swap(x, y);

        father[y] = x;
        size[x] += size[y];
        data[x] += data[y];
    }
};

#endif //OI_CODES_DSU_H
