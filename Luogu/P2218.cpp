//HZ - 41.4
//Luogu - P2218
#include <bits/stdc++.h>

using namespace std;
constexpr int maxn = 20004;

inline int read();

struct graphData;
struct NODE;

struct NODE {
    int x;
    int y;
    int color;

    NODE() : x(0), y(0), color(0) {};

    inline bool isIncluded(const graphData &) const;

    void init();
} node[maxn];

struct graphData {
    int maxX;
    int minX;
    int maxY;
    int minY;

    graphData() : maxX(INT_MIN), minX(INT_MAX), maxY(INT_MIN), minY(INT_MAX) {};

    graphData(int _maxX, int _minX, int _maxY, int _minY) : maxX(_maxX), minX(_minX), maxY(_maxY), minY(_minY) {};

    inline void include(const NODE &);

    inline void include(const NODE *);
} sourceData;

int n(read()), l, r;

void init();

bool check(int);

bool dfs(int, int);

inline void print(const graphData &, int);

inline void clear(const graphData &);

int main() {
    init();
    while (l < r) {
        int mid((l + r) >> 1);
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d", l);
    return 0;
}

void init() {
    for (int i = 1; i <= n; ++i)
        node[i].init();

    ::l = 0;
    ::r = max(sourceData.maxX - sourceData.minX, sourceData.maxY - sourceData.minY);
}

void NODE::init() {
    this->x = ::read();
    this->y = ::read();
    sourceData.include(this);
}

inline bool NODE::isIncluded(const graphData &object) const {
    return object.minX <= this->x && this->x <= object.maxX && object.minY <= this->y && this->y <= object.maxY;
}

void graphData::include(const NODE &object) {
    this->maxX = max(this->maxX, object.x);
    this->minX = min(this->minX, object.x);
    this->maxY = max(this->maxY, object.y);
    this->minY = min(this->minY, object.y);
}

void graphData::include(const NODE *object) {
    this->maxX = max(this->maxX, object->x);
    this->minX = min(this->minX, object->x);
    this->maxY = max(this->maxY, object->y);
    this->minY = min(this->minY, object->y);
}

inline int read() {
    int result(0), ch(getchar());
    bool positive(true);
    while ((ch < '0' || ch > '9') && ch != '-')
        ch = getchar();
    if (ch == '-') {
        positive = false;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        result = (result << 3) + (result << 1) + (ch ^ 48);
        ch = getchar();
    }
    if (positive)
        return result;
    else
        return -result;
}

bool check(int ans) {
    clear(sourceData);
    dfs(1, ans);
}

inline void clear(const graphData &object) {
    for (int i = 1; i <= n; ++i)
        if (node[i].isIncluded(object))
            node[i].color = 0;
}

inline void print(const graphData &object, int color) {
    for (int i = 1; i <= n; ++i)
        if (node[i].isIncluded(object))
            node[i].color = color;
}

bool dfs(int cnt, int ans) {
    graphData notPrinted;
    if (cnt > 1)
        for (int i = 1; i <= n; ++i)
            if (node[i].color == 0)
                notPrinted.include(node[i]);
            else
                continue;
    else
        notPrinted = sourceData;


    if (max(notPrinted.maxX - notPrinted.minX, notPrinted.maxY - notPrinted.minY) <= ans)
        return true;
    if (cnt == 3)
        return false;

    graphData toPaint;
    toPaint = graphData(notPrinted.minX + ans, notPrinted.minX, notPrinted.minY + ans, notPrinted.minY);
    print(toPaint, cnt);
    if (dfs(cnt + 1, ans))
        return true;
    else
        clear(toPaint);

    toPaint = graphData(notPrinted.minX + ans, notPrinted.minX, notPrinted.maxY, notPrinted.maxY - ans);
    print(toPaint, cnt);
    if (dfs(cnt + 1, ans))
        return true;
    else
        clear(toPaint);

    toPaint = graphData(notPrinted.maxX, notPrinted.maxX - ans, notPrinted.minY + ans, notPrinted.minY);
    print(toPaint, cnt);
    if (dfs(cnt + 1, ans))
        return true;
    else
        clear(toPaint);

    toPaint = graphData(notPrinted.maxX, notPrinted.maxX - ans, notPrinted.maxY, notPrinted.maxY - ans);
    print(toPaint, cnt);
    if (dfs(cnt + 1, ans))
        return true;
    else
        clear(toPaint);

    return false;
}
