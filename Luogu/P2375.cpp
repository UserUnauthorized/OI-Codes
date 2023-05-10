//HZ - 37.7
//Luogu - P2375
#include<bits/stdc++.h>

namespace DEBUG {
    template<typename T>
    inline void _debug(const char *format, T t) {
        std::cerr << format << '=' << t << std::endl;
    }

    template<class First, class... Rest>
    inline void _debug(const char *format, First first, Rest... rest) {
        while (*format != ',') std::cerr << *format++;
        std::cerr << '=' << first << ",";
        _debug(format + 1, rest...);
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &V) {
        os << "[ ";
        for (const auto &vv: V) os << vv << ", ";
        os << "]";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, __int128 V) {
        if (V < 0) {
            os << '-';
            V = -V;
        }

        if (V > 9)
            os << V / 10;

        os << (int) (V % 10);

        return os;
    }

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

typedef long long valueType;

constexpr valueType maxN = 1e6 + 5, MOD = 1e9 + 7;

std::array<int, maxN> next, num;

int main() {
    valueType n;

    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::string data;

        std::cin >> data;

//		data.insert(data.begin(), ' ');

        valueType const length = data.length();

        next.fill(0);
        num.fill(0);
        num[1] = 1;
//		int j = 0;

        for (int i = 1; i < length; ++i) {
            int j = next[i - 1];

            while (j > 0 && data[i] != data[j])
                j = next[j - 1];

            if (data[i] == data[j])
                ++j;

            next[i] = j;
            num[i] = num[j] + 1;
        }

        valueType ans = 1;

        for (int i = 1; i < length; ++i) {
//            valueType t = 1;

            int j = next[i];

            valueType const pos = (i + 1) >> 1;

            while (j > pos)
                j = next[j - 1];

//            while (j > 0) {
//                ++t;
//                j = next[j - 1];
//            }

            ans = (ans * (num[j] + 1)) % MOD;
        }

        std::cout << ans << '\n';
    }

    std::cout << std::flush;

    return 0;
}
