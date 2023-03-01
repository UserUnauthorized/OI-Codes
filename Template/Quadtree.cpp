#include<bits/stdc++.h>

using namespace std;

void build(int id, int x, int y, int r);

int query(int id, int x, int y, int r, int queryX, int queryY);

inline bool checkPositive(int a, int b);

int main() {
    build(int
    0, int
    0, int
    0, int
    N);
}

void build(int id, int x, int y, int r) {
    if (r == 1) {
        tree[id].data = source[x][y] + source[x + 1][y] + source[x][y + 1] + source[x + 1][y + 1];
        return;
    }

    int mid(r >> 1);

    build((id << 2) | 1, x + mid, y + mid, mid);
    build((id << 2) | 2, x - mid, y + mid, mid);
    build((id << 2) | 3, x + mid, y - mid, mid);
    build((id << 2) + 4, x - mid, y - mid, mid);
}

int query(int id, int x, int y, int r, int queryX, int queryY) {
    if (checkPositive(x, queryX) && abs(x) + r <= abs(queryX) &&
        checkPositive(y, queryY) && abs(y) + r <= abs(queryY))
        return tree[id].data;

    int mid(r >> 1);


    int result(query((id << 2) | 3, x + mid, y - mid, mid, queryX, queryY));
    if (queryX > x && queryY > y)
        result += query((id << 2) | 1, x + mid, y + mid, mid, queryX, queryY);
    if (queryX > x)
        result += query((id << 2) + 4, x - mid, y - mid, mid, queryX, queryY);
    if (queryY > y)
        result += query((id << 2) | 2, x - mid, y + mid, mid, queryX, queryY);

    return result;
}

inline bool checkPositive(int a, int b) {
    return (a > 0 && b > 0) || (a < 0 && b < 0);
}
