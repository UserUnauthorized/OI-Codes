//HZ - 44.5
//Luogu - P3722
#include<bits/stdc++.h>
//using namespace std;

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

typedef long long valueType;
typedef int posType;
constexpr int maxN = 2e5 + 5;
typedef std::array<valueType, maxN> ARRAY;

int L_, R_, N_, M_, P1_, P2_;
const int &L = L_, &R = R_, &N = N_, &M = M_, &P1 = P1_, &P2 = P2_;

struct SEGNODE {
    typedef SEGNODE self;
    typedef self *pointer;
    typedef ::valueType valueType;
    typedef ::posType posType;

    pointer leftSon, rightSon;
    self::valueType count;

    SEGNODE() : leftSon(NULL), rightSon(NULL), count(0) {};

    void update() {
        this->count = 0;

        if (this->leftSon != NULL)
            this->count += this->leftSon->count;

        if (this->rightSon != NULL)
            this->count += this->rightSon->count;
    }
};

typedef SEGNODE::pointer pointer;
typedef std::array<pointer, maxN> PointerArray;

pointer newNode();

pointer build(posType l, posType r);

pointer insert(const pointer &current, posType nodeL, posType nodeR, posType pos);

valueType query(pointer leftNode, pointer rightNode, posType nodeL, posType nodeR, posType l, posType r);

valueType query(posType l, posType r, posType k);

ARRAY source;
PointerArray tree;

void init();

valueType solve(posType l, posType r);

int main() {
    init();

    for (int i = 0; i < M; ++i) {
        posType l, r;
        std::cin >> l >> r;

        std::cout << solve(l, r) << '\n';
    }

    return 0;
}

valueType solve(posType l, posType r) {
    if (r - l == 1)
        return P1;

    if (l == r)
        return 0;

    posType const mid = (l + r) >> 1, leftSize = mid - l, rightSize = r - mid;

    valueType const leftRank = query(l, mid, source[mid]), rightRank = query(mid, r, source[mid]);

    valueType const result =
            P2 * ((leftSize - leftRank + 1) * (rightRank - 1) + (rightSize - rightRank + 1) * (leftRank - 1)) +
            P1 * ((leftSize - leftRank + 1) * (rightSize - rightRank + 1));

    return result + solve(l, mid) + solve(mid, r);
}

void init() {
    std::cin >> N_ >> M_ >> P1_ >> P2_;

    for (int i = 1; i <= N; ++i)
        std::cin >> source[i];

    L_ = 1;
    R_ = N;

    tree[0] = build(L, R);

    for (int i = 1; i <= N; ++i)
        tree[i] = insert(tree[i - 1], L, R, source[i]);
}

pointer build(posType l, posType r) {
    pointer current = newNode();

    if (l == r) {
        current->count = 0;
        return current;
    }

    int const mid = (l + r) >> 1;

    current->leftSon = build(l, mid);
    current->rightSon = build(mid + 1, r);

    return current;
}

pointer insert(const pointer &current, posType nodeL, posType nodeR, posType pos) {
    pointer result = newNode();
    *result = *current;

    if (nodeL == nodeR) {
        ++result->count;
        return result;
    }

    int const mid = (nodeL + nodeR) >> 1;

    if (pos <= mid)
        result->leftSon = insert(current->leftSon, nodeL, mid, pos);
    else
        result->rightSon = insert(current->rightSon, mid + 1, nodeR, pos);

    result->update();

    return result;
}

valueType query(posType l, posType r, posType k) {
    if (k == L)
        return 1;

    return query(tree[l - 1], tree[r], L, R, L, k - 1) + 1;
}

valueType query(pointer leftNode, pointer rightNode, posType nodeL, posType nodeR, posType l, posType r) {
    if (leftNode->count == rightNode->count)
        return 0;

    if (l <= nodeL && nodeR <= r)
        return rightNode->count - leftNode->count;

    posType const mid = (nodeL + nodeR) >> 1;

    if (r <= mid)
        return query(leftNode->leftSon, rightNode->leftSon, nodeL, mid, l, r);
    else if (l > mid)
        return query(leftNode->rightSon, rightNode->rightSon, mid + 1, nodeR, l, r);
    else
        return query(leftNode->leftSon, rightNode->leftSon, nodeL, mid, l, r) +
               query(leftNode->rightSon, rightNode->rightSon, mid + 1, nodeR, l, r);
}

pointer newNode() {
    static SEGNODE pool[maxN << 5], *allocp = pool - 1;
    return ++allocp;
}
