//HZ - 43.3
//Luogu - P3605
#include<bits/stdc++.h>

using namespace std;
typedef int valueType;
constexpr valueType maxN = 1e5 + 5;
valueType L(INT_MAX), R(INT_MIN);

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
    self::valueType query(self::valueType l, self::valueType r) {
        if (r < l)
            return 0;

        return this->query(this->root, l, r);
    }

private:
    self::valueType query(pointer current, self::valueType l, self::valueType r) {
        if (current == NULL)
            return 0;

        if (l <= current->leftBound && current->rightBound <= r)
            return current->data;

        if (r <= current->mid)
            return this->query(current->leftSon, l, r);

        if (l > current->mid)
            return this->query(current->rightSon, l, r);

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
            a->data += b->data;
            return a;
        }

        a->leftSon = this->merge(a->leftSon, b->leftSon);
        a->rightSon = this->merge(a->rightSon, b->rightSon);

        a->update();

        return a;
    }
};

struct EDGE {
    int next;
    int to;

    EDGE() : next(-1), to(-1) {};

    EDGE(int _next, int _to) : next(_next), to(_to) {};
};

valueType N;

array<valueType, maxN> head, ans, source_;
vector<valueType> point_;
const vector<valueType> &point = point_;
const array<valueType, maxN> &source = source_;
array<TREE, maxN> tree;
array<EDGE, maxN> edge;

void init();

void calc(valueType x, valueType from);

int main() {
    init();
    calc(1, 0);

    for (int i = 1; i <= N; ++i)
        cout << ans[i] << '\n';

    return 0;
}

void init() {
    cin >> N;

    for (int i = 1; i <= N; ++i)
        cin >> source_[i];

    point_.assign(source.begin() + 1, source.begin() + N + 1);
    sort(point_.begin(), point_.end());
    point_.erase(unique(point_.begin(), point_.end()), point_.end());

    for (int i = 1; i <= N; ++i)
        source_[i] = distance(point.begin(), lower_bound(point.begin(), point.end(), source[i])) + 1;

    L = 1;
    R = point.size();

    for (int i = 2; i <= N; ++i) {
        int x;
        cin >> x;

        edge[i] = EDGE(head[x], i);
        head[x] = i;
    }

    for (int i = 1; i <= N; ++i)
        tree[i].insert(source[i], 1);
}

void calc(valueType x, valueType from) {
    for (int i = head[x]; i != 0; i = edge[i].next) {
        const EDGE &e = edge[i];

        if (e.to == from)
            continue;
        calc(e.to, x);
        tree[x].merge(tree[e.to]);
    }

    ans[x] = tree[x].query(source[x] + 1, R);
}

SEGNODE pool[maxN * 20];

SEGNODE *newNode() {
    static SEGNODE *allocp = pool - 1;

    return ++allocp;
}
