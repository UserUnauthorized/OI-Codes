//HZ - 43.4
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
constexpr valueType maxN = 1e5 + 5;
valueType L(INT_MAX), R(INT_MIN);

valueType N, M, Q;

array<valueType, maxN> head, ans, source, father, point;

void init();

int find(int x);

void merge(int x, int y);

struct SEGNODE {
    typedef SEGNODE self;
    typedef self *pointer;
    typedef ::valueType valueType;

    int leftBound, rightBound, mid;
    pointer leftSon, rightSon;
    self::valueType data;

    SEGNODE() : leftBound(-1), rightBound(-1), mid(-1), leftSon(NULL), rightSon(NULL), data(0) {};

    void init(self::valueType l, self::valueType r) {
        this->leftBound = l;
        this->rightBound = r;
        this->mid = (this->leftBound + this->rightBound) >> 1;
        this->leftSon = this->rightSon = NULL;
        this->data = 0;
    }

    void update() {
        this->data = 0;

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
            current->data += key;
            return current;
        }

        if (pos <= current->mid)
            current->leftSon = this->insert(current->leftSon, pos, key, l, current->mid);
        else
            current->rightSon = this->insert(current->rightSon, pos, key, current->mid + 1, r);

        current->update();

        return current;
    }

public:
    self::valueType query(self::valueType key) {
        if (key > this->root->data)
            return -1;

        return point[this->query(this->root, key)];
    }

private:
    self::valueType query(pointer current, self::valueType key) {
        if (current->leftBound == current->rightBound)
            return current->rightBound;

        if (current->leftSon == NULL)
            return this->query(current->rightSon, key);

        if (current->leftSon->data < key)
            return this->query(current->rightSon, key - current->leftSon->data);

        return this->query(current->leftSon, key);
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

//valueType N, M, Q;

//array<valueType, maxN> head, ans, source, father, point;
array<TREE, maxN> tree;

void init();

int find(int x);

void merge(int x, int y);

int main() {
    init();

    while (Q--) {
        char order;
        int x, y;
        cin >> order >> x >> y;
        if (order == 'Q')
            cout << tree[find(x)].query(y) << '\n';
        else if (order == 'B')
            merge(x, y);
        else
            exit(1);
    }

    return 0;
}

void init() {
    cin >> N >> M;

    L = 1;
    R = N;

    for (int i = 1; i <= N; ++i) {
        cin >> source[i];
        tree[i].insert(source[i], 1);
        point[source[i]] = i;
    }

    std::iota(father.begin(), father.end(), 0);

    while (M--) {
        int x, y;
        cin >> x >> y;
        merge(x, y);
    }

    cin >> Q;
}

void merge(int x, int y) {
    int rootX(find(x)), rootY(find(y));

    tree[rootX].merge(tree[rootY]);

    father[rootY] = rootX;
}

SEGNODE pool[maxN * 20];

SEGNODE *newNode() {
    static SEGNODE *allocp = pool - 1;

    return ++allocp;
}

int find(int x) {
    if (father[x] == x)return x;
    else return father[x] = find(father[x]);
}
