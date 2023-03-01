//HZ - 43.1
//Luogu - P4556
#include<bits/stdc++.h>

using namespace std;

typedef int valueType;
constexpr valueType maxN = 1e5 + 5, maxK = log2(maxN) + 1;
valueType L(INT_MAX), R(INT_MIN);

struct SEGNODE {
    typedef SEGNODE self;
    typedef self *pointer;
    typedef ::valueType valueType;

    struct DATA {
        self::valueType value;
        self::valueType cnt;

        DATA() : value(INT_MAX), cnt(0) {};

        DATA(self::valueType _value_, self::valueType _cnt_) : value(_value_), cnt(_cnt_) {};

        friend bool operator<(const DATA &a, const DATA &b) {
//			debug(a.cnt, a.value);
//			debug(b.cnt, b.value);
//			debug(a.cnt < b.cnt, a.value > b.value);
            if (a.cnt != b.cnt)
                return a.cnt < b.cnt;

            return a.value > b.value;
        }

        void operator+=(self::valueType key) {
            this->cnt += key;
        }

        void operator+=(const DATA &Object) {
            if (this->value == Object.value)
                this->cnt += Object.cnt;
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
    }

    void update() {
        this->data = DATA();

        if (this->leftSon != NULL)
            this->data = std::max(this->data, this->leftSon->data);

        if (this->rightSon != NULL)
            this->data = std::max(this->data, this->rightSon->data);
    }
};

SEGNODE *newNode();

class TREE {
public:
    typedef TREE self;
    typedef SEGNODE node;
    typedef node::DATA DATA;
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
            current->data.value = current->leftBound;
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
    self::valueType ans() {
        if (this->root == NULL || this->root->data.cnt < 1)
            return 0;

        return this->root->data.value;
    }

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

struct QUERYEDGE {
    int next;
    int from;
    int to;
    int LCA;

    QUERYEDGE() : LCA(-1) {};

    QUERYEDGE(int _next, int _from, int _to) : next(_next), from(_from), to(_to), LCA(-1) {};
};

struct QUERY {
    typedef QUERY self;
    typedef ::valueType valueType;

    self::valueType x, y, z;

    QUERY() : x(-1), y(-1), z(-1) {};

    QUERY(int _x_, int _y_, int _z_) : x(_x_), y(_y_), z(_z_) {};
};

valueType n, m, cnt(0);

array<valueType, maxN> father, parent, head, queryHead, ans;
array<bool, maxN> visited;
array<TREE, maxN> tree;
array<EDGE, maxN << 1> edge;
array<QUERYEDGE, maxN << 1> queryEdge;
array<QUERY, maxN> query;

void init();

void dfs(valueType x, valueType from);

void calc(valueType x, valueType from);

int find(int x);

int main() {
    init();
    dfs(1, 0);

    for (int i = 1; i <= m; ++i) {
        const QUERY &q = query[i];
        const int lca(queryEdge[i << 1].LCA);

        tree[q.x].insert(q.z, 1);
        tree[q.y].insert(q.z, 1);
        tree[lca].insert(q.z, -1);
        if (father[lca]);
        tree[father[lca]].insert(q.z, -1);
    }

    calc(1, 0);

    for (int i = 1; i <= n; ++i)
        cout << ans[i] << '\n';

    return 0;
}

void init() {
    cin >> n >> m;

    for (int i = 1; i < n; ++i) {
        int a(0), b(0);
        cin >> a >> b;
        edge[i << 1] = EDGE(head[a], b);
        edge[i << 1 | 1] = EDGE(head[b], a);
        head[a] = i << 1;
        head[b] = i << 1 | 1;
    }

    for (int i = 1; i <= m; ++i) {
        int x(0), y(0), z(0);

        cin >> x >> y >> z;

        L = min(L, z);
        R = max(R, z);

        query[i] = QUERY(x, y, z);

        queryEdge[i << 1] = QUERYEDGE(queryHead[x], x, y);
        queryEdge[i << 1 | 1] = QUERYEDGE(queryHead[y], y, x);
        queryHead[x] = i << 1;
        queryHead[y] = i << 1 | 1;
    }
}

void dfs(valueType x, valueType from) {
    father[x] = from;
    parent[x] = x;
    visited[x] = true;

    for (int i = head[x]; i != 0; i = edge[i].next) {
        int to(edge[i].to);

        if (!visited[to]) {
            dfs(to, x);
            parent[to] = x;
        }
    }

    for (int i = queryHead[x]; i; i = queryEdge[i].next)
        if (visited[queryEdge[i].to])
            queryEdge[i ^ 1].LCA = queryEdge[i].LCA = find(queryEdge[i].to);
}

void calc(valueType x, valueType from) {
    for (int i = head[x]; i != 0; i = edge[i].next) {
        const EDGE &e = edge[i];

        if (e.to == from)
            continue;
        calc(e.to, x);

        tree[x].merge(tree[e.to]);
    }

    ans[x] = tree[x].ans();
}

SEGNODE pool[maxN * 60];

SEGNODE *newNode() {
    static SEGNODE *allocp = pool - 1;

    return ++allocp;
}

int find(int x) {
    if (parent[x] == x)return x;
    else return parent[x] = find(parent[x]);
}
