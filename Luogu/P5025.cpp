//HZ - 28.10
//Luogu - P5025
#include<bits/stdc++.h>
#include<array>

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

constexpr int maxN = 5e5 + 5, MOD = 1e9 + 7;
typedef long long posType;
typedef int numType;
posType position[maxN << 2], radius[maxN << 2];
array<numType, maxN> inId, leftN, rightN;
array<numType, maxN << 2> belong, dfn, low, leftBound, rightBound;
array<bool, maxN << 2> vis;
bitset<maxN << 2> isRoot;

list<int> oldEdge[maxN << 2], edge[maxN << 2];
stack<int> st;

class INTREE {
public:
    void build(int n_, array<numType, maxN> &idArray);

    void build_(int id, int l, int r, array<numType, maxN> &pos);

    void connect(int l, int r, int nodeId);

    void connect_(int id, int l, int r, int queryL, int queryR, int nodeId);

private:
    int _n_;
} inTree;

int N(0), cnt(0), sccnum(0), D(0);

void init();

void tarjan(int x);

void build();

void dfs(int x);

int main() {
//	#ifdef LOCAL
//	freopen("bomb9.in", "r", stdin);
//	freopen("bomb9.ans", "w", stdout);
//	#endif
    init();

//    for (int i = 1; i <= N; ++i)
//        if (!dfn[inId[i]])
//            tarjan(inId[i]);
    tarjan(1);

    isRoot.set();
    build();

    int ROOT(0);
    for (int i = 1; i <= sccnum; ++i) {
        if (isRoot[i]) {
            ROOT = i;
            break;
        }
    }

    vis.fill(false);
//    for (int i = 1; i <= sccnum; ++i)
//        if (!vis[i])
//            dfs(i);

    dfs(ROOT);

    unsigned long long ans = 0;
    for (int i = 1; i <= N; ++i) {
        ans += (unsigned long long) i *
               (unsigned long long) (rightBound[belong[inId[i]]] - leftBound[belong[inId[i]]] + 1);
        ans %= MOD;
    }

    cout << ans % MOD;
    return 0;
}

void init() {
    memset(position, 0, sizeof(position));
    memset(radius, 0, sizeof(radius));
    leftBound.fill(INT_MAX);

    cin >> N;

    inTree.build(N, inId);

    for (int i = 1; i <= N; ++i)
        cin >> position[i] >> radius[i];

    position[0] = INT_MAX;
    position[N + 1] = 0;

//	for(int i = 1; i <= N; ++i)
//		debug(i,position[i],radius[i],inId[i]);

    for (int i = 1; i <= N; ++i) {
        int l = distance(position, lower_bound(position + 1, position + N + 1, position[i] - radius[i]));
        int r = distance(position + 1, upper_bound(position + 1, position + N + 1, position[i] + radius[i]));
//		debug(i,l,r);
        inTree.connect(l, r, inId[i]);
//        leftN[inId[i]] = l;
//        rightN[inId[i]] = r;
//		leftN[inId[i]] = rightN[inId[i]] = i;
    }
}

void INTREE::build(int n_, array<numType, maxN> &idArray) {
    _n_ = n_;
    this->build_(1, 1, _n_, idArray);
}

void INTREE::build_(int id, int l, int r, array<numType, maxN> &pos) {
    leftN[id] = l;
    rightN[id] = r;
    D = max(D, id);
    if (l == r) {
        pos[r] = id;
        return;
    }

    int mid((l + r) >> 1);

    this->build_(id << 1, l, mid, pos);
    this->build_(id << 1 | 1, mid + 1, r, pos);

    oldEdge[id].emplace_back(id << 1);
    oldEdge[id].emplace_back(id << 1 | 1);
}

void INTREE::connect(int l, int r, int nodeId) {
    this->connect_(1, 1, _n_, l, r, nodeId);
}

void INTREE::connect_(int id, int l, int r, int queryL, int queryR, int nodeId) {
    if (queryL <= l && r <= queryR) {
        if (id != nodeId)
            oldEdge[nodeId].emplace_back(id);
        return;
    }

    int mid((l + r) >> 1);

    if (queryL <= mid)
        this->connect_(id << 1, l, mid, queryL, queryR, nodeId);
    if (queryR > mid)
        this->connect_(id << 1 | 1, mid + 1, r, queryL, queryR, nodeId);
}

void tarjan(int x) {
    dfn[x] = low[x] = ++cnt;
    vis[x] = true;
    st.push(x);

    for (auto iter: oldEdge[x]) {
        if (!dfn[iter]) {
            tarjan(iter);
            low[x] = min(low[x], low[iter]);
        } else if (vis[iter]) {
            low[x] = min(low[x], dfn[iter]);
        }
    }

    if (dfn[x] == low[x]) {
        ++sccnum;
        int y;
        do {
            y = st.top();
            st.pop();
            vis[y] = false;
            belong[y] = sccnum;
//			debug(y,sccnum,leftBound[sccnum],rightBound[sccnum]);
//			debug(leftN[y],rightN[y]);
            leftBound[sccnum] = min(leftBound[sccnum], leftN[y]);
            rightBound[sccnum] = max(rightBound[sccnum], rightN[y]);
//			debug(leftBound[sccnum],rightBound[sccnum]);
        } while (y != x);
    }
}

void build() {
    for (int i = 1; i <= D; ++i)
        for (auto iter: oldEdge[i])
            if (belong[i] != belong[iter]) {
                isRoot[belong[iter]] = false;
                edge[belong[i]].emplace_back(belong[iter]);
            }


//    for (int i = 1; i <= sccnum; ++i) {
//        vector<int> &iter = edge[i];
//        sort(iter.begin(), iter.end());
//        iter.erase(unique(iter.begin(), iter.end()), iter.end());
//    }
}

void dfs(int x) {
    vis[x] = true;

    for (auto iter: edge[x]) {
        if (!vis[iter])
            dfs(iter);

        leftBound[x] = min(leftBound[x], leftBound[iter]);
        rightBound[x] = max(rightBound[x], rightBound[iter]);
    }
}
