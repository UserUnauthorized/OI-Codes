//HZ - 44.2
//Luogu - P3834
//Luogu - SP3946
#include<bits/stdc++.h>

using namespace std;
typedef int valueType;
constexpr int maxN = 2e5 + 5;
typedef array<valueType, maxN> ARRAY;
typedef vector<valueType> VECTOR;

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

int L_, R_, N_, M_;
const int &L = L_, &R = R_, &N = N_, &M = M_;

struct SEGNODE {
    typedef SEGNODE self;
    typedef self *pointer;
    typedef ::valueType valueType;

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
typedef array<pointer, maxN> PointerArray;

pointer newNode();

pointer build(valueType l, valueType r);

pointer insert(const pointer &current, valueType nodeL, valueType nodeR, valueType pos);

valueType query(pointer leftNode, pointer rightNode, valueType l, valueType r, valueType k);

valueType query(valueType l, valueType r, valueType k);

ARRAY source;
PointerArray tree;
VECTOR point;

void init();

int main() {
    init();

    for (int i = 0; i < M; ++i) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << point[query(l, r, k)] << '\n';
    }

    return 0;
}

void init() {
    cin >> N_ >> M_;

    for (int i = 1; i <= N; ++i)
        cin >> source[i];

    point.assign(source.begin() + 1, source.begin() + N + 1);
    point.push_back(INT_MIN);
    sort(point.begin(), point.end());
    point.erase(unique(point.begin(), point.end()), point.end());

    L_ = 1;
    R_ = point.size() - 1;

    for (int i = 1; i <= N; ++i)
        source[i] = distance(point.begin(), lower_bound(point.begin(), point.end(), source[i]));

    tree[0] = build(L, R);

    for (int i = 1; i <= N; ++i)
        tree[i] = insert(tree[i - 1], L, R, source[i]);
}

pointer build(valueType l, valueType r) {
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

pointer insert(const pointer &current, valueType nodeL, valueType nodeR, valueType pos) {
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

valueType query(valueType l, valueType r, valueType k) {
    return query(tree[l - 1], tree[r], L, R, k);
}

valueType query(pointer leftNode, pointer rightNode, valueType l, valueType r, valueType k) {
    if (l == r)
        return r;

    int const mid = (l + r) >> 1;

    int leftCount = 0;

    if (rightNode->leftSon != NULL)
        leftCount += rightNode->leftSon->count;

    if (leftNode->leftSon != NULL)
        leftCount -= leftNode->leftSon->count;

    if (k <= leftCount)
        return query(leftNode->leftSon, rightNode->leftSon, l, mid, k);
    else
        return query(leftNode->rightSon, rightNode->rightSon, mid + 1, r, k - leftCount);
}

pointer newNode() {
    static SEGNODE pool[maxN << 5], *allocp = pool - 1;
    return ++allocp;
}
