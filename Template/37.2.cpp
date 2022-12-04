//HZ - 37.2
//Luogu - P3667
#ifdef LOCAL

#include<debug.h>

#else
#define debug(...)
#endif

#include <bits/stdc++.h>

using namespace std;
constexpr int maxN = 505, base = 5;
typedef unsigned long long hash_type;

template<typename T>
class read_ {
public:
    typedef T value_type;
    typedef T &reference;
    typedef T *pointer;

    inline value_type operator()() {
        value_type result(0);
        bool positive(true);
        int input(getchar());

        while (input < '0' || input > '9') {
            positive = true;
            while ((input < '0' || input > '9') && input != '-')
                input = getchar();

            if (input == '-') {
                positive = false;
                input = getchar();
            }
        }

        while (input >= '0' && input <= '9') {
            result = (result << 3) + (result << 1) + (input & _n_);
            input = getchar();
        }

        return positive ? result : -result;
    }

    inline void operator()(reference object) {
        object = this->operator()();
    }

    inline void operator()(pointer object) {
        *object = this->operator()();
    }

    template<class ... Args>
    void operator()(pointer first, Args...args) {
        this->operator()(std::initializer_list<pointer>{first, args...});
    }

    void operator()(std::initializer_list<pointer> args) {
        for (pointer iter: args)
            *iter = this->operator()();
    }

private:
    static constexpr int _n_ = 15;
};

read_<int> read;

void init();

bool check(int len);

int n, m, ans;
array<array<char, maxN>, maxN> strA, strB;
array<array<hash_type, maxN>, maxN> hashA, hashB;
array<hash_type, maxN> bin;
array<int, 256> table;

int main() {
    init();

    int l(1), r(m);

    while (l <= r) {
        const int mid((l + r) >> 1);
        if (check(mid)) {
            r = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }

    printf("%d", ans);
    return 0;
}

void init() {
    table['A'] = 1;
    table['C'] = 2;
    table['T'] = 3;
    table['G'] = 4;

    read(&n, &m);

    for (int i = 1; i <= n; ++i)
        scanf("%s", strA[i].begin() + 1);
    for (int i = 1; i <= n; ++i)
        scanf("%s", strB[i].begin() + 1);

    bin[0] = 1;
    for (int i = 1; i <= m; ++i)
        bin[i] = bin[i - 1] * base;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            hashA[i][j] = hashA[i][j - 1] * base + (table[strA[i][j]]);
            hashB[i][j] = hashB[i][j - 1] * base + (table[strB[i][j]]);
        }
    }
}

bool check(int len) {
    for (int i = 0; i + len <= m; ++i) {
        map<unsigned long long, bool> vis;

        for (int j = 1; j <= n; ++j)
            vis[hashA[j][i + len] - hashA[j][i] * bin[len]] = true;

        bool flag(false);
        for (int j = 1; j <= n; ++j) {
            if (vis.count(hashB[j][i + len] - hashB[j][i] * bin[len])) {
                flag = true;
                break;
            }
        }

        if (flag)
            continue;
        else
            return true;
    }
    return false;
}
