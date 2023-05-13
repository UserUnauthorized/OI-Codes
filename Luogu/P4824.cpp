//wrongAnswer
//HZ - 37.8
//Luogu - P4824
#include <bits/stdc++.h>

namespace DEBUG {
template<typename T>
inline void _debug(const char *format, T t) {
    std::cerr << format << '=' << t << std::endl;
}

template<class First, class... Rest>
inline void _debug(const char *format, First first, Rest... rest) {
    while (*format != ',')
        std::cerr << *format++;

    std::cerr << '=' << first << ",";
    _debug(format + 1, rest...);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &V) {
    os << "[ ";

    for (const auto &vv : V)
        os << vv << ", ";

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

    os << (int)(V % 10);

    return os;
}

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

constexpr int maxN = 1e6 + 5;

std::array<int, maxN> next, prefix, match;

int main() {
    std::string text, pattern;

    std::cin >> text >> pattern;

    int const patternLength = (int)pattern.length();
    int const textLength = (int)text.length();

    for (int i = 1; i <= textLength; ++i)
        next[i - 1] = i;

    for (int i = 1; i < patternLength; ++i) {
        int j = prefix[i - 1];

        while (j > 0 && pattern[i] != pattern[j])
            j = prefix[j - 1];

        if (pattern[i] == pattern[j])
            ++j;

        prefix[i] = j;
    }

    int matchTimes = 0, j = 0, start = 0;

    for (int i = 0; i < textLength; i = next[i]) {
        //      if(j != 0 && text[i] != pattern[j])
        //          matchTimes = 0;

        while (j > 0 && text[i] != pattern[j])
            j = prefix[j - 1];


        if (text[i] == pattern[j])
            ++j;
        else
            matchTimes = 0;

        match[i] = j;

        if (j == patternLength) {
            ++matchTimes;

            //            debug(i, j, matchTimes);
            if (i - matchTimes * patternLength < start) {
                //              debug(start);
                start = i + 1;
                continue;
            }

            next[i - matchTimes * patternLength] = i + 1;
            i = i - matchTimes * patternLength;
            //          i = i - matchTimes * patternLength - 1;
            j = match[i];

            //          if(j == 0)
            //              matchTimes = 0;
        }
    }

    for (int i = start; i < textLength; i = next[i])
        std::cout << text[i];
}
