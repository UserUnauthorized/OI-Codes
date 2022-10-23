//HZ - 20.4
//Luogu - P2216
#include<bits/stdc++.h>

using namespace std;

int a, b, n, ans;

int s[1002][1002], xmin[1002][1002], xmax[1002][1002], ymin[1002][1002], ymax[1002][1002];

deque<int> que;

void init();
void build();
void emptyQue();

int main() {
    init();
    build();
    //printf("AA:%d\n\n",ymin[3][3]);
    ans = 0x7fffffff;
    for (int i = 1; i <= a - n + 1; ++i)
        for (int j = 1; j <= b - n + 1; ++j)
            ans = min(ans, ymax[i][j] - ymin[i][j]);
    printf("%d", ans);
    return 0;
}

void init() {
    memset(s, 0, sizeof(s));
    memset(xmin, 0, sizeof(xmin));
    memset(xmax, 0, sizeof(xmax));
    memset(ymin, 0, sizeof(ymin));
    memset(ymax, 0, sizeof(ymax));
    scanf("%d%d%d", &a, &b, &n);
    for (int i = 1; i <= a; ++i)
        for (int j = 1; j <= b; ++j)
            scanf("%d", &s[i][j]);
}

void build() {
    for (int i = 1; i <= a; ++i) {
        for (int j = b; j > b - n + 1; --j) {
            while (!que.empty() && s[i][que.back()] >= s[i][j]) que.pop_back();
            que.push_back(j);
        }
        for (int j = b - n + 1; j >= 1; --j) {
            while (!que.empty() && s[i][que.back()] >= s[i][j]) que.pop_back();
            que.push_back(j);
            while (que.front() > j + n - 1) que.pop_front();
            xmin[i][j] = s[i][que.front()];
        }
        emptyQue();
    }
    emptyQue();

    for (int i = 1; i <= a; ++i) {
        for (int j = b; j > b - n + 1; --j) {
            while (!que.empty() && s[i][que.back()] <= s[i][j]) que.pop_back();
            que.push_back(j);
        }
        for (int j = b - n + 1; j >= 1; --j) {
            while (!que.empty() && s[i][que.back()] <= s[i][j]) que.pop_back();
            que.push_back(j);
            while (que.front() > j + n - 1) que.pop_front();
            xmax[i][j] = s[i][que.front()];
        }
        emptyQue();
    }
    emptyQue();

    for (int i = 1; i <= b; ++i) {
        for (int j = a; j > a - n + 1; --j) {
            while (!que.empty() && xmin[que.back()][i] >= xmin[j][i]) que.pop_back();
            que.push_back(j);
        }
        for (int j = a - n + 1; j >= 1; --j) {
            while (!que.empty() && xmin[que.back()][i] >= xmin[j][i]) que.pop_back();
            que.push_back(j);
            while (que.front() > j + n - 1) que.pop_front();
            ymin[j][i] = xmin[que.front()][i];
        }
        emptyQue();
    }
    emptyQue();

    for (int i = 1; i <= b; ++i) {
        for (int j = a; j > a - n + 1; --j) {
            while (!que.empty() && xmax[que.back()][i] <= xmax[j][i]) que.pop_back();
            que.push_back(j);
        }
        for (int j = a - n + 1; j >= 1; --j) {
            while (!que.empty() && xmax[que.back()][i] <= xmax[j][i]) que.pop_back();
            que.push_back(j);
            while (que.front() > j + n - 1) que.pop_front();
            ymax[j][i] = xmax[que.front()][i];
        }
        emptyQue();
    }
    emptyQue();
}

void emptyQue() {
    deque<int> empty;
    que.swap(empty);
}
