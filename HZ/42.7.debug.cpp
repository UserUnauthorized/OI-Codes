//42.7
//DEBUG
#include<bits/stdc++.h>

using namespace std;

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &V) {
    for (const auto &vv: V)
        os << vv << ' ';

    os << '\n';
    return os;
}

int main() {
    freopen("1.in", "r", stdin);
    freopen("1.debug", "w", stdout);
    int n;
    cin >> n;

    vector<int> source;

    for (int i = 1; i <= n; ++i) {
        int t;
        cin >> t;
        source.insert(source.begin() + t, i);
        cout << source;
        if (i & 1024)
            cerr << i << '\n';
    }

    return 0;
}
