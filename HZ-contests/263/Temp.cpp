#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include <D:\OI\OI-Codes\Template\debug.h>

using namespace std;
using namespace DEBUG;

int n;

double a[2022], dp[2022], now[2022];

inline bool find_(int zb)//zb代表指标
{
    memset(dp, 0, sizeof(dp));
    dp[0] = 1.0;
    for (int man = 1; man <= n; man++)//第几个人
    {
        for (int finish = man - 1; finish >= 0; finish--)//完成了第finish个任务时
        {
            if (finish < (zb + 1) / 2)//如果j个任务小于k的一半
            {
                dp[finish + 1] += dp[finish] * (a[man] / 2.0);//如果第man个人可以完成的任务的概率
                dp[finish] = dp[finish] * (1 - (a[man] /
                                                2)); //若不能完成第finish个任务时的概率，相当于now[man][finish]=0+now[man-1][finish]*(1-(a[man]/2)),因为是向前枚举，所以是now[finish]不用加，否则会加上now[i-1][finish]即上一个人完成finish个任务的概率
            } else {
                dp[finish + 1] += dp[finish] * a[man];
                dp[finish] = dp[finish] * (1 - a[man]);
            }
        }
    }
    for (int i = 0; i <= n; ++i) {
        cerr << i << "\t" << dp[i] << endl;
    }
    double num = 0;
    for (int i = 0; i < zb; i++) {
        num += dp[i];
    }
    return (num >= 0.4);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    /*int l = 0, r = n + 1, an = r;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (find_(mid)) {
            r = mid - 1;
            an = mid;
        } else l = mid + 1;
    }
    cout << an << endl;*/
    find_(5);
}