//Luogu - SP1043
/*UTF-8 : 猫树解法*/
/*GBK : è���ⷨ*/
#include<bits/stdc++.h>

using namespace std;
constexpr int maxN = 3e5 + 5, maxD = 50;

int N, Q, len;
int source[maxN], pos[maxN], Log[maxN];
long long midSum[maxD][maxN], partSum[maxD][maxN];

/* midSum:The maximum sum of sub-segments CONTAINING the midpoint of a segment.
 * partSum:Normal segment maximum field and.
 * */

void init();

void build(int id, int l, int r, int d);

long long query(int l, int r);

int main() {
    init();
    build(1, 1, len, 1);
    cin >> Q;
    while (Q--) {
        int l, r;
        cin >> l >> r;
        cout << query(l, r) << endl;
    }
    return 0;
}

void init() {
    memset(source, 0, sizeof(source));
    memset(pos, 0, sizeof(pos));
    memset(Log, 0, sizeof(Log));
    memset(midSum, 0, sizeof(midSum));
    memset(partSum, 0, sizeof(partSum));

    cin >> N;

    for (int i = 1; i <= N; ++i)
        cin >> source[i];

    /*for(int i = 2; i <= (N << 2); ++i)
        Log[i] = Log[i >> 1] + 1;*/
    for (len = 2; len < N; len <<= 1);
    int l = len << 1;
    for (int i = 2; i <= l; ++i)
        Log[i] = Log[i >> 1] + 1;
}

void build(int id, int l, int r, int d) {
    if (l == r) {
        pos[r] = id;
        return;
    }

    int const mid((l + r) >> 1);

    long long midData, partData;
    midSum[d][mid] = partSum[d][mid] = midData = partData = source[mid];
    partData = max(partData, (long long) 0);

    for (int i = mid - 1; i >= l; --i) {
        midData += source[i];
        partData += source[i];

        midSum[d][i] = max(midSum[d][i + 1], midData);
        partSum[d][i] = max(partSum[d][i + 1], partData);

        partData = max(partData, (long long) 0);
    }

    midSum[d][mid + 1] = partSum[d][mid + 1] = midData = partData = source[mid + 1];
    partData = max(partData, (long long) 0);

    for (int i = mid + 2; i <= r; ++i) {
        midData += source[i];
        partData += source[i];

        midSum[d][i] = max(midSum[d][i - 1], midData);
        partSum[d][i] = max(partSum[d][i - 1], partData);

        partData = max(partData, (long long) 0);
    }

    build(id << 1, l, mid, d + 1);
    build(id << 1 | 1, mid + 1, r, d + 1);
}

long long query(int l, int r) {
    if (l == r)
        return source[r];

    int d = Log[pos[l]] - Log[pos[l] ^ pos[r]];

    return max({partSum[d][l], partSum[d][r], midSum[d][l] + midSum[d][r]});
}
