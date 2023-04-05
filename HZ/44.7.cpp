//HZ - 44.7
//Luogu - P2839
#include<bits/stdc++.h>

#include <iostream>
#include <vector>

namespace DEBUG {
    template<typename T>
    inline void _debug(const char *format, T t) {
        std::cerr << format << '=' << t << std::endl;
    }

    template<class First, class... Rest>
    inline void _debug(const char *format, First first, Rest... rest) {
        while (*format != ',') std::cerr << *format++;
        std::cerr << '=' << first << ",";
        _debug(format + 1, rest...);
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &V) {
        os << "[ ";
        for (const auto &vv: V) os << vv << ", ";
        os << "]";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, __int128 V) {
        if (V < 0) {
            os << '-';
            V = -V;
        }

        if (V > 9)
            os << V / 10;

        os << (int) (V % 10);

        return os;
    }

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

namespace HJT {

#include <bits/stdc++.h>

    typedef unsigned int posType;
    typedef int valueType;

    constexpr posType maxN = 2e4 + 5;

    class NODE;

    class POINTER;

    class DATA;

    typedef posType pointer;

    pointer newNode();

    class DATA {
    public:
        DATA() : sum(1), leftMax(1), rightMax(1) {};

        DATA(valueType key) : sum(key), leftMax(key), rightMax(key) {};

    public:
        valueType sum;
        valueType leftMax;
        valueType rightMax;

    public:
        void merge(DATA const &left, DATA const &right);

        friend void merge(DATA &father, DATA const &left, DATA const &right);

        friend DATA merge(DATA const &left, DATA const &right);
    };

    pointer newNode() {
        static posType count = 0;
        return count++;
    }

    class NODE {
    public:
        NODE() : leftSon(), rightSon(), data() {};

    public:
        pointer leftSon;
        pointer rightSon;

    public:
        DATA data;

    public:
        void update();
    };


    void merge(DATA &father, DATA const &left, DATA const &right) {
        father.sum = left.sum + right.sum;

        father.leftMax = std::max(left.leftMax, left.sum + right.leftMax);

        father.rightMax = std::max(right.rightMax, right.sum + left.rightMax);
    }

    DATA merge(DATA const &left, DATA const &right) {
        DATA result;

        merge(result, left, right);

        return result;
    }

    void DATA::merge(DATA const &left, DATA const &right) {
        HJT::merge(*this, left, right);
    }

    std::array<NODE, maxN << 5> tree;

    void NODE::update() {
        this->data.merge(tree[this->leftSon].data, tree[this->rightSon].data);
    }

    pointer build(posType l, posType r) {
        pointer current = newNode();

        if (l == r) {
            tree[current].data = DATA(1);
            return current;
        }

        posType const mid = (l + r) >> 1;

        tree[current].leftSon = build(l, mid);
        tree[current].rightSon = build(mid + 1, r);

        tree[current].update();

        return current;
    }

    pointer insert(const pointer &current, posType nodeL, posType nodeR, posType pos, valueType key) {
        pointer result = newNode();
        tree[result] = tree[current];

        if (nodeL == nodeR) {
            tree[result].data = DATA(key);
            return result;
        }

        posType const mid = (nodeL + nodeR) >> 1;

        if (pos <= mid)
            tree[result].leftSon = insert(tree[current].leftSon, nodeL, mid, pos, key);
        else
            tree[result].rightSon = insert(tree[current].rightSon, mid + 1, nodeR, pos, key);

        tree[result].update();

        return result;
    }

    DATA query(const pointer &current, posType nodeL, posType nodeR, posType queryL, posType queryR) {
        if (queryL > queryR)
            return DATA(0);

        if (queryL <= nodeL && nodeR <= queryR)
            return tree[current].data;

        posType const mid = (nodeL + nodeR) >> 1;

        if (queryR <= mid)
            return query(tree[current].leftSon, nodeL, mid, queryL, queryR);
        else if (queryL > mid)
            return query(tree[current].rightSon, mid + 1, nodeR, queryL, queryR);
        else
            return merge(query(tree[current].leftSon, nodeL, mid, queryL, queryR),
                         query(tree[current].rightSon, mid + 1, nodeR, queryL, queryR));
    }
}


typedef int valueType;
typedef unsigned int posType;

constexpr posType maxN = 2e4 + 5;

typedef std::array<valueType, 4> INPUT;
typedef std::array<valueType, maxN> ARRAY;
typedef std::array<HJT::pointer, maxN> PointerArray;
typedef std::vector<valueType> VECTOR;

valueType N_, Q_, L_, R_, S_;
valueType const &N = N_, &Q = Q_, &L = L_, &R = R_, &S = S_;

ARRAY source;
VECTOR point;
PointerArray tree;
std::vector<std::queue<valueType>> table;

void init();

const INPUT &decrypt(INPUT &data, valueType const &lastAns);

valueType solve(INPUT const &data);

bool check(valueType k, INPUT const &data);

valueType query(valueType k, INPUT const &data);

std::istream &operator>>(std::istream &os, INPUT &v);

int main() {
#ifdef LOCAL
    freopen("middle.in", "r", stdin);
    freopen("middle.out", "w", stdout);
    freopen("middle.err", "w", stderr);
#endif
    init();

    int lastAns = 0;

    for (int i = 0; i < Q; ++i) {
        INPUT data;
        std::cin >> data;

        std::cout << (lastAns = point[solve(decrypt(data, lastAns))]) << '\n';
    }

    return 0;
}

void init() {
    std::cin >> N_;

    for (int i = 1; i <= N; ++i)
        std::cin >> source[i];

    std::cin >> Q_;

    point.assign(source.begin() + 1, source.begin() + N + 1);
    point.push_back(INT_MIN);
    std::sort(point.begin(), point.end());
    point.erase(std::unique(point.begin(), point.end()), point.end());
    S_ = point.size() - 1;
    table.resize(S + 1);

    L_ = 1;
    R_ = N;

    for (int i = 1; i <= N; ++i) {
        source[i] = std::distance(point.begin(), std::lower_bound(point.begin(), point.end(), source[i]));
        table[source[i]].push(i);
    }

    tree[1] = HJT::build(L, R);

    for (int i = 2; i <= S; ++i) {
        tree[i] = HJT::insert(tree[i - 1], L, R, table[i - 1].front(), -1);
        table[i - 1].pop();

        while (!table[i - 1].empty()) {
            tree[i] = HJT::insert(tree[i], L, R, table[i - 1].front(), -1);
            table[i - 1].pop();
        }
    }
}

valueType query(valueType k, INPUT const &data) {
    return HJT::query(tree[k], L, R, data[0], data[1]).rightMax +
           HJT::query(tree[k], L, R, data[1] + 1, data[2] - 1).sum +
           HJT::query(tree[k], L, R, data[2], data[3]).leftMax;
}

valueType solve(INPUT const &data) {
    valueType l = 1, r = S, ans = S;
    while (l <= r) {
        int const mid = (l + r) >> 1;
        if (check(mid, data))
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }

    return ans;
}

const INPUT &decrypt(INPUT &data, valueType const &lastAns) {
    for (int i = 0; i < 4; ++i)
        data[i] = (data[i] + lastAns) % N + 1;

    std::sort(data.begin(), data.end());

    return data;
}

bool check(valueType k, INPUT const &data) {
    return query(k, data) >= 0;
}

std::istream &operator>>(std::istream &os, INPUT &v) {
    os >> v[0] >> v[1] >> v[2] >> v[3];
    return os;
}

