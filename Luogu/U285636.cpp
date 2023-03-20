//Luogu - U285636
#include<bits/stdc++.h>

using namespace std;
typedef long long valueType;
constexpr valueType maxN = 2e5 + 5;
valueType L_(INT_MAX), R_(INT_MIN);
const valueType &L = L_, &R = R_;
valueType N_, M_, K_, testcase;
pair<valueType, valueType> ans;
const valueType &N = N_, &M = M_, &K = K_;

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

struct SEGNODE {
    typedef SEGNODE self;
    typedef self *pointer;
    typedef ::valueType valueType;

    int leftBound, rightBound, mid;
    pointer leftSon, rightSon;
    self::valueType count;

    SEGNODE() : leftBound(-1), rightBound(-1), mid(-1), leftSon(NULL), rightSon(NULL), count(0) {};

    void init(self::valueType l, self::valueType r) {
        this->leftBound = l;
        this->rightBound = r;
        this->mid = (this->leftBound + this->rightBound) >> 1;
        this->leftSon = this->rightSon = NULL;
        this->count = 0;
    }

    void update() {
        this->count = 0;

        if (this->leftSon != NULL)
            this->count += this->leftSon->count;

        if (this->rightSon != NULL)
            this->count += this->rightSon->count;
    }
};

SEGNODE *newNode();

class TREE {
public:
    typedef TREE self;
    typedef SEGNODE node;
    typedef node *pointer;
    typedef node::valueType valueType;

    pointer root;

    TREE() : root(NULL) {};

public:
    void insert(self::valueType pos, self::valueType key) {
        this->insert(this->root, pos, key, L, R);
    }

    self::valueType kth(self::valueType key) {
        if (this->root == NULL || key > this->root->count)
            return K + 1;

        return this->kth(this->root, key);
    }

    self::valueType query(self::valueType l, self::valueType r) {
        if (l > r)
            return 0;

        return this->query(this->root, l, r);
    }

private:
    void insert(pointer &current, self::valueType pos, self::valueType key, self::valueType l, self::valueType r) {
        if (current == NULL) {
            current = newNode();
            current->init(l, r);
        }

        if (current->leftBound == current->rightBound) {
            current->count += key;
            return;
        }

        if (pos <= current->mid)
            this->insert(current->leftSon, pos, key, l, current->mid);
        else
            this->insert(current->rightSon, pos, key, current->mid + 1, r);

        current->update();
    }

    self::valueType kth(pointer current, self::valueType key) {
        if (current->leftBound == current->rightBound)
            return current->rightBound;

        if (current->leftSon == NULL)
            return this->kth(current->rightSon, key);

        if (current->leftSon->count < key)
            return this->kth(current->rightSon, key - current->leftSon->count);

        return this->kth(current->leftSon, key);
    }

    self::valueType query(pointer current, self::valueType l, self::valueType r) {
        if (current == NULL)
            return 0;

        if (l <= current->leftBound && current->rightBound <= r)
            return current->count;

        if (r <= current->mid)
            return this->query(current->leftSon, l, r);
        else if (l > current->mid)
            return this->query(current->rightSon, l, r);
        else
            return this->query(current->leftSon, l, r) + this->query(current->rightSon, l, r);
    }

public:
    void merge(const self &Object) {
        this->root = this->merge(this->root, Object.root);
    }

private:
    pointer merge(pointer a, pointer b) {
        if (a == NULL)
            return b;

        if (b == NULL)
            return a;

        if (a->leftBound == a->rightBound) {
            a->count += b->count;
            return a;
        }

        a->leftSon = this->merge(a->leftSon, b->leftSon);
        a->rightSon = this->merge(a->rightSon, b->rightSon);

        a->update();

        return a;
    }
};

array<TREE, maxN> tree;

void init();

int main() {
    init();

    for (int i = 0; i < M; ++i) {
        int opt;
        cin >> opt;
//    	debug(opt);
        if (opt == 1) {
            valueType p, x, q;
            cin >> p >> x >> q;
            tree[p].insert(x, q);
        } else if (opt == 2) {
            valueType p, t;
            cin >> p >> t;
            tree[p].merge(tree[t]);
        } else if (opt == 3) {
            valueType p, x, y;
            cin >> p >> x >> y;
            ans.first ^= tree[p].query(x, y);
        } else if (opt == 4) {
            valueType p, k;
            cin >> p >> k;
            ans.second ^= tree[p].kth(k);
        }
    }

    cout << ans.first << '\n' << ans.second;

    return 0;
}

void init() {
    cin >> testcase;
    cin >> N_ >> M_ >> K_;

    L_ = 1;
    R_ = K;
}

SEGNODE pool[maxN * 60];

SEGNODE *newNode() {
    static SEGNODE *allocp = pool - 1;

    return ++allocp;
}
