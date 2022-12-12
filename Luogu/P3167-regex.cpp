//regex
#include<bits/stdc++.h>

using namespace std;

constexpr int maxn = 1e5 + 5;

char /*pattern_[maxn],*/ str[maxn];
int T;

int main() {
    string pattern_;
    cin >> (pattern_);
//    pattern_[0] = '^';
//    pattern_[std::strlen(pattern_)] = '$';
    pattern_ = '^' + pattern_ + '$';

    const std::regex pattern(pattern_);
    cerr << "DEBUG" << endl;
    cin >> T;
    while (T--) {
        memset(str, 0, sizeof(str));
        cin >> str;
        cout << ((regex_match(str, pattern)) ? "YES\n" : "NO\n");
    }
}