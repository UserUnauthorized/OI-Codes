//Luogu - P5656
#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct read_ {
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
            result = (result << 3) + (result << 1) + (input & 15);
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
    void operator()(Args...args) {
        this->operator()(std::initializer_list<pointer>{args...});
    }

    void operator()(std::initializer_list<pointer> args) {
        for (pointer iter: args)
            *iter = this->operator()();
    }
};

read_<long long> read;
read_<int> readInt;

int T;

long long exGcd(long long a, long long b, long long &x, long long &y);

int main() {
    readInt(T);
    while (T--) {
        long long a(0), b(0), c(0), x0(0), y0(0);
        read(&a, &b, &c);

        int const d = exGcd(a, b, x0, y0);

        if (c % d != 0) {
            cout << "-1\n";
            continue;
        }

        long long const x1 = x0 * c / d, y1 = y0 * c / d;

        long long const k1 = b / d, k2 = a / d;

        int const lowerS = ceil(((double) -x1 + 1.0) / (double) k1), upperS = floor(((double) y1 - 1.0) / (double) k2);

        if (lowerS > upperS) {
            cout << x1 + k1 * lowerS << ' ' << y1 - k2 * upperS << '\n';
            continue;
        }

        cout << upperS - lowerS + 1 << ' ' << x1 + k1 * lowerS << ' ' << y1 - k2 * upperS << ' ' << x1 + k1 * upperS
             << ' ' << y1 - k2 * lowerS << '\n';
    }
}

long long exGcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long const d = exGcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}