//HZ - 43.5
//Luogu - P3224
#include<bits/stdc++.h>

using namespace std;

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

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

typedef int valueType;
typedef double productType;
constexpr valueType maxN = 4e5 + 5, maxM = 4e5 + 5;
constexpr valueType L = 1, R = 1e9;

valueType N, M;

array<valueType, maxN> head, father;
//vector<valueType> value;

void init();

int find(int x);

void merge(int x, int y);

struct SEGNODE {
    typedef SEGNODE self;
    typedef self *pointer;
    typedef ::valueType valueType;
    typedef ::productType productType;

    struct DATA {
        self::valueType count;
        self::productType product;

        DATA() : count(0), product(1) {};

        DATA(self::valueType _count_, self::productType _product_) : count(_count_), product(log(_product_)) {};

        void operator+=(const DATA &Object) {
            this->count += Object.count;
            this->product += Object.product;
        }
    };

    int leftBound, rightBound, mid;
    pointer leftSon, rightSon;
    DATA data;

    SEGNODE() : leftBound(-1), rightBound(-1), mid(-1), leftSon(NULL), rightSon(NULL), data() {};

    void init(self::valueType l, self::valueType r) {
        this->leftBound = l;
        this->rightBound = r;
        this->mid = (this->leftBound + this->rightBound) >> 1;
        this->leftSon = this->rightSon = NULL;
        this->data = DATA();
    }

    void update() {
        this->data = DATA();

        if (this->leftSon != NULL)
            this->data += this->leftSon->data;

        if (this->rightSon != NULL)
            this->data += this->rightSon->data;
    }
};

SEGNODE *newNode();

class TREE {
public:
    typedef TREE self;
    typedef SEGNODE node;
    typedef node *pointer;
    typedef node::valueType valueType;
    typedef node::productType productType;

    pointer root;

    TREE() : root(NULL) {};

public:
    void insert(self::valueType pos, self::valueType key) {
        this->root = this->insert(this->root, pos, key, L, R);
    }

private:
    pointer insert(pointer current, self::valueType pos, self::valueType key, self::valueType l, self::valueType r) {
        if (current == NULL) {
            current = newNode();
            current->init(l, r);
        }

        if (current->leftBound == current->rightBound) {
            current->data.count += key;
            current->data.product += log(current->leftBound) * (double) key;
            return current;
        }

        if (pos <= current->mid)
            current->leftSon = this->insert(current->leftSon, pos, key, l, current->mid);
        else
            current->rightSon = this->insert(current->rightSon, pos, key, current->mid + 1, r);

        current->update();

        return current;
    }

protected:
    self::valueType countAndDelete(self::valueType l, self::valueType r) {
        return this->countAndDelete(this->root, l, r);
    }

private:
    self::valueType countAndDelete(pointer current, self::valueType l, self::valueType r) {
        if (current == NULL)
            return 0;

        if (l <= current->leftBound && current->rightBound <= r) {
            self::valueType const result = current->data.count;
            current->data = node::DATA();
            return result;
        }

        self::valueType result;

        if (r <= current->mid)
            result = this->countAndDelete(current->leftSon, l, r);
        else if (l > current->mid)
            result = this->countAndDelete(current->rightSon, l, r);
        else
            result = this->countAndDelete(current->leftSon, l, r) + this->countAndDelete(current->rightSon, l, r);

        current->update();

        return result;
    }

public:
    void update(int type, self::valueType key) {
        if (type == 3) {
            self::valueType const count = this->countAndDelete(L, key - 1);
            this->insert(key, count);
        } else if (type == 4) {
            self::valueType const count = this->countAndDelete(key + 1, R);
            this->insert(key, count);
        }
    }

public:
    self::valueType kth(self::valueType key) {
        if (key > this->root->data.count)
            return -1;

        return this->kth(this->root, key);
    }

    self::valueType product() {
        if (this->root == NULL)
            return INT_MIN;

        return this->root->data.product;
    }

    self::valueType size() {
        if (this->root == NULL)
            return 0;

        return this->root->data.count;
    }

private:
    self::valueType kth(pointer current, self::valueType key) {
        if (current->leftBound == current->rightBound)
            return current->rightBound;

        if (current->leftSon == NULL)
            return this->kth(current->rightSon, key);

        if (current->leftSon->data.count < key)
            return this->kth(current->rightSon, key - current->leftSon->data.count);

        return this->kth(current->leftSon, key);
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
            a->data += b->data;
            return a;
        }

        a->leftSon = this->merge(a->leftSon, b->leftSon);
        a->rightSon = this->merge(a->rightSon, b->rightSon);

        a->update();

        return a;
    }
};

struct QUERY {
    int opt;
    valueType a, b;
};

//array<QUERY, maxM> query;
//vector<TREE> tree;
SEGNODE *pool;
array<TREE, maxN> tree;

void init();

void read();

int find(int x);

void merge(int x, int y);

int main() {
    init();

    for (int i = 1; i <= M; ++i) {
        int opt;
        cin >> opt;

        if (opt == 1) {
            valueType x;
            cin >> x;
            tree[++N].insert(x, 1);
        } else if (opt == 2) {
            valueType a, b;
            cin >> a >> b;
            merge(a, b);
        } else if (opt == 3 || opt == 4) {
            valueType a, x;
            cin >> a >> x;
            tree[find(a)].update(opt, x);
        } else if (opt == 5) {
            valueType a, k;
            cin >> a >> k;
            cout << tree[find(a)].kth(k) << '\n';
        } else if (opt == 6) {
            valueType a, b;
            cin >> a >> b;
            cout << (tree[find(a)].product() > tree[find(b)].product()) << '\n';
        } else if (opt == 7) {
            valueType a;
            cin >> a;
            cout << tree[find(a)].size() << '\n';
        } else if (opt == 8) {
            read();
            read();
        } else if (opt == 9) {
            read();
        }
    }

    return 0;
}

void init() {
    cin >> M;

    std::iota(father.begin(), father.end(), 1);
}

void merge(int x, int y) {
    int rootX(find(x)), rootY(find(y));

    tree[rootX].merge(tree[rootY]);

    father[rootY] = rootX;
}

SEGNODE *newNode() {
//    static SEGNODE *allocp = pool;
//
//    return ++allocp;
//	return (SEGNODE*)malloc(sizeof(SEGNODE));
    return new SEGNODE;
}

int find(int x) {
    if (father[x] == x)return x;
    else return father[x] = find(father[x]);
}

void read() {
    int ch(getchar());
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        ch = getchar();
}
