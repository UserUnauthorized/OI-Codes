#ifndef OI_CODES_READ_H
#define OI_CODES_READ_H

#include <stdio.h>
#include <initializer_list>

template<typename T>
class read_ {
    typedef T value_type;
    typedef T &reference;
    typedef T *pointer;

    inline value_type operator()() {
        value_type result(0);
        bool positive;
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

#endif //OI_CODES_READ_H
