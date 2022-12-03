//HZ - 37.1
#include <bits/stdc++.h>

#ifdef LOCAL

#include<debug.h>

#else
#define debug(...)
#endif
using namespace std;
constexpr int maxW = 1e4 + 5, maxT = 1e6 + 5;
constexpr unsigned long long mod = 212370440130137957;

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

unsigned long long hashT[maxT], hashW[maxW];
char strT[maxT], strW[maxW];
int T, lenT, lenW;
constexpr int base = 29;
unsigned long long pB[maxT];

int main() {
    pB[0] = 1;
    for (int i = 1; i < maxT; ++i)
        pB[i] = pB[i - 1] * (unsigned long long) base;

    read(&T);

    while (T--) {
        init();

        int ans(0);
        for (int i = 0; i + lenW <= lenT; ++i)
            if (hashT[i + lenW] - hashT[i] * pB[lenW] == hashW[lenW])
                ++ans;

        printf("%d\n", ans);
    }

    return 0;
}

void init() {
    scanf("%s", strW + 1);
    scanf("%s", strT + 1);

    lenT = (int) strlen(strT + 1);
    lenW = (int) strlen(strW + 1);

    for (int i = 1; i <= lenT; ++i)
        hashT[i] = hashT[i - 1] * base + (strT[i] - 'A' + 1);

    for (int i = 1; i <= lenW; ++i)
        hashW[i] = hashW[i - 1] * base + (strW[i] - 'A' + 1);
}