//HZ -37.6
#include <bits/stdc++.h>

using namespace std;
constexpr int maxn = 4e5 + 5;
char str[maxn];
int kmp[maxn], ans[maxn];

int main() {
    while (cin >> (str + 1)) {
        int len = (int) strlen(str + 1);
        int j = 0;
        for (int i = 2; i <= len; ++i) {
            while (j > 0 && str[i] != str[j + 1])j = kmp[j];
            if (str[i] == str[j + 1])j++;
            kmp[i] = j;
        }

        int cnt(0);

        while (len) ans[cnt++] = len, len = kmp[len];
        while (cnt--)
            cout << ans[cnt] << ' ';
        cout << endl;

        memset(ans, 0, sizeof(ans));
        memset(str, 0, sizeof(str));
        memset(kmp, 0, sizeof(kmp));
    }
}