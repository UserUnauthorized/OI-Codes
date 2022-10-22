//HZ - 263.3
#include <bits/stdc++.h>
//#include <D:\OI\OI-Codes\Template\debug.h>

using namespace std;
//using namespace DEBUG;

constexpr int maxn = 1003;

int n;

double p[maxn], dp[maxn];

void init();
bool check(int);

int main() {
    init();
    /*int l(1), r(n);
    //debug(l,r);
    while (l < r) {
        int mid = (l + r) >> 1;
        //debug(l, r, mid, check(mid));
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d", l);*/
    for (int i = 0; i <= n; ++i)
        if (check(i)) {
            printf("%d", i);
            break;
        }
    return 0;
}

void init() {
    memset(p, 0, sizeof(p));
    memset(dp, 0, sizeof(dp));

    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
        scanf("%lf", p + i);
    //debug(p[1], p[2], p[3], p[4], p[5]);
}

bool check(int x) {
    memset(dp, 0, sizeof(dp));
    dp[0] = (1 - p[1] * 0.5);
    //dp[0] = 1.0;
    //dp[0] = 1.0;
    dp[1] = p[1] * 0.5;
    //debug(dp[0], dp[1], dp[2]);
    for (int i = 2; i <= n; ++i) {
        for (int j = n; j >= 1; --j)
            if (j < (x+1)>>1) {
                dp[j] = (p[i] * 0.5 * dp[j - 1]) + (1 - p[i] * 0.5) * dp[j];
            } else if ((double) j ==  ((double)x / 2.0))
                dp[j] = (p[i] * 0.5 * dp[j - 1]) + ((1 - p[i]) * dp[j]);
            else {
                dp[j] = (p[i] * dp[j - 1]) + (1 - p[i]) * dp[j];
            }
        dp[0] *= (1 - p[i] * 0.5);
    }
    //debug(dp[0], dp[1], dp[2]);
    double result(0);
    /*for (int i = x; i <= n; ++i)
        result += dp[i];
    //debug(x, result);
    if (result <= 0.6)return true;
    else return false;*/
    for (int i = 0; i < x; ++i) {
        result += dp[i];
        //
    }
    if (x == 5)
        for (int i = 0; i <= n; ++i) {
            //debug(dp[i]);
            cerr << i << "\t" << dp[i] << endl;
        }
    //cerr << "\t" << x << "\t" << result << endl;
    if (result >= 0.4)return true;
    else return false;
}