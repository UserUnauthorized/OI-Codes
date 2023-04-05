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
typedef std::array<posType, maxN> PosArray;

int L_, R_, N_, M_, P1_, P2_;
const int &L = L_, &R = R_, &N = N_, &M = M_, &P1 = P1_, &P2 = P2_;

struct SEGNODE {
    typedef SEGNODE self;
    typedef self *pointer;
    typedef ::valueType valueType;
    typedef ::posType posType;

    pointer leftSon, rightSon;
    self::valueType count;
    self::valueType lazy;

    SEGNODE() : leftSon(NULL), rightSon(NULL), count(0), lazy(0) {};

    void update() {
        this->count = this->lazy;

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

pointer insert(const pointer &current, posType nodeL, posType nodeR, posType pos, valueType key);

pointer insert(const pointer &current, posType nodeL, posType nodeR, posType queryL, posType queryR, valueType key);

valueType query(pointer leftNode, pointer rightNode, posType nodeL, posType nodeR, posType queryL, posType queryR);

valueType query(posType l, posType r);

ARRAY source;
PosArray leftBound, rightBound;
PointerArray tree;

void init();

void getBound();

int main() {
    init();

    getBound();

    for (int i = 0; i < M; ++i) {
        posType l, r;
        std::cin >> l >> r;

        std::cout << query(l, r) << '\n';
    }

    return 0;
}

void init() {
    std::cin >> N_ >> M_ >> P1_ >> P2_;

    for (int i = 1; i <= N; ++i)
        std::cin >> source[i];

    source[N + 1] = INT_MAX;
    source[0] = INT_MIN;

    L_ = 1;
    R_ = N;

    tree[0] = build(L, R);
}

void getBound() {
    std::stack<int> st;

    for (int i = 1; i <= N + 1; ++i) {
        while (!st.empty() && source[st.top()] < source[i]) {
            rightBound[st.top()] = i;
            st.pop();
        }

        st.push(i);
    }
}

pointer build(posType l, posType r) {
    pointer current = newNode();

    if (l == r) {
        current->count = current->lazy = 0;
        return current;
    }

    int const mid = (l + r) >> 1;

    current->leftSon = build(l, mid);
    current->rightSon = build(mid + 1, r);

    return current;
}

pointer newNode() {
    static SEGNODE pool[maxN << 6], *allocp = pool - 1;
    return ++allocp;
}
