//Luogu - P1790
//Luogu - P1817
//Luogu - P4537
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

constexpr int maxN = 10;

typedef unsigned int BitType;
typedef std::vector<BitType> BitArray;
typedef std::bitset<maxN> BitNum;
typedef std::bitset<maxN * maxN> BITSET;
typedef std::array<BITSET, maxN * maxN> BitMaritx;
typedef std::array<int, maxN> Array;

int N_, M_, ans = 0, S_;
int const &N = N_, &M = M_, &S = S_;

bool existBlack_ = false, existWhite_ = false;
bool const &existBlack = existBlack_, &existWhite = existWhite_;

BitArray status, bit;
Array row;
BitMaritx compatible;
BITSET whiteBorder, blackBorder;

void dfs(int x, int now);

bool check();

int main() {
    freopen("P4537.err", "w", stderr);
    std::cin >> N_ >> M_;

    bit.resize(N + 1);

    bit[0] = 0;
    bit[1] = 1;
    for (int i = 2; i <= N; ++i)
        bit[i] = bit[i - 1] << 1 | 1;

    status.push_back(0);

    for (int i = 1; i <= N; ++i)
        for (int j = 0; j + i <= N; ++j)
            status.push_back(bit[i] << j);

    S_ = status.size() - 1;

    debug(status, S);

    for (int i = 0; i <= S; ++i) {
        BitNum now(status[i]);

        if (now[0] || now[N - 1])
            blackBorder[i] = true;

        if ((now[0] == false || now[N - 1] == false))
            whiteBorder[i] = true;

        debug(i, status[i], blackBorder[i], whiteBorder[i]);
    }

    for (int i = 1; i <= S; ++i)
        for (int j = i; j <= S; ++j)
            if (status[i] & status[j])
                compatible[i][j] = compatible[j][i] = true;

    for (int i = 0; i <= S; ++i)
        compatible[i][0] = compatible[0][i] = true;
    compatible[0][0] = true;

    for (int i = 0; i <= S; ++i)
        dfs(1, i);

    std::cout << ans / 2;
}

void dfs(int x, int now) {
    if (!compatible[row[x - 1]][now]/* && x != 1 && x != M*/)
        return;

    row[x] = now;

    bool const flag1 = existBlack, flag2 = existWhite;

    if (now > 0)
        existBlack_ = true;

    if (now < S)
        existWhite_ = true;

    if (x == M) {
//		debug(now, existBlack, existWhite);
        if (check()) {
            ++ans;
            std::cerr << "No." << ans << '\n';
            for (int i = 1; i <= M; ++i)
                std::cerr << BitNum(status[row[i]]).to_string().substr(maxN - N, N) << '\n';
        }


        row[x] = 0;

        existBlack_ = flag1;
        existWhite_ = flag2;

        return;
    }

    for (int i = 0; i <= S; ++i)
        dfs(x + 1, i);

    row[x] = 0;

    existBlack_ = flag1;
    existWhite_ = flag2;
}

bool check() {
    bool existW = false, existB = false, borderW = false, borderB = false;

    for (int i = 1; i <= M; ++i) {
        existW = existW || (row[i] != S);
        existB = existB || (row[i] != 0);
        borderW = borderW || whiteBorder[row[i]];
        borderB = borderB || blackBorder[row[i]];

        if (borderW && borderB && existW && existB)
            return true;
    }

    return borderW && borderB && existW && existB;
}
