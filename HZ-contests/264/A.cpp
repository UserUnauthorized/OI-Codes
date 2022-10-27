//HZ -264.1
#include <bits/stdc++.h>

using namespace std;
string source;
string s1, s2, s3, s4;
int ans(0);

int main() {
    freopen("ma.in", "r", stdin);
    freopen("ma.out", "w", stdout);

    cin >> source;

    for (char &iter: source) {
        if ('a' <= iter && iter <= 'z')
            s1.push_back(iter);
        else if ('A' <= iter && iter <= 'Z')
            s2.push_back(iter);
        else if ('0' <= iter && iter <= '9')
            s3.push_back(iter);
        else
            s4.push_back(iter);
    }

    if (!s1.empty())++ans;
    if (!s2.empty())++ans;
    if (!s3.empty())++ans;
    if (!s4.empty())++ans;

    printf("password level:%d\n", ans);
    if (s1.empty())
        cout << "(Null)" << endl;
    else
        cout << s1 << endl;

    if (s2.empty())
        cout << "(Null)" << endl;
    else
        cout << s2 << endl;

    if (s3.empty())
        cout << "(Null)" << endl;
    else
        cout << s3 << endl;

    if (s4.empty())
        cout << "(Null)" << endl;
    else
        cout << s4 << endl;
    fclose(stdin);
    fclose(stdout);
    return 0;
}