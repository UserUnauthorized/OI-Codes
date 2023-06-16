//Luogu - P3808
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

class AC {
public:
    typedef int valueType;
    typedef size_t sizeType;
    static sizeType const charSetSize = 30;

private:
    static sizeType converter(char c) {
        return c - 'a';
    }

    struct NODE {
        typedef NODE self;
        typedef self *pointer;

        std::array<pointer, charSetSize> trans;

        valueType value;

        pointer fail;

        NODE(valueType v) : trans(), value(v), fail(nullptr) {
            trans.fill(nullptr);
        }

        pointer &transfer(char c) {
            return trans[converter(c)];
        }
    };

    typedef NODE::pointer pointer;

    pointer allocate(valueType v = 0) {
        return new NODE(v);
    }

    static void freeNode(pointer &p) {
        delete p;
    }

    pointer root;

public:
    AC() : root(allocate()) {};

    void insert(const std::string &data) {
        pointer current = this->root;

        for (auto const &iter: data) {
            if (current->transfer(iter) == nullptr) {
                current->transfer(iter) = allocate();

                current = current->transfer(iter);
            } else {
                current = current->transfer(iter);
            }
        }

        ++current->value;

    }

    void build() {
        root->fail = root;

        std::queue<pointer> que;

        for (sizeType i = 0; i < charSetSize; ++i) {
            if (root->trans[i] != nullptr) {
                root->trans[i]->fail = root;
                que.push(root->trans[i]);
            } else {
                root->trans[i] = root;
            }
        }


        while (!que.empty()) {
            pointer current = que.front();
            que.pop();

            for (sizeType i = 0; i < charSetSize; ++i) {
                if (current->trans[i] != nullptr) {
                    current->trans[i]->fail = current->fail->trans[i];

                    que.push(current->trans[i]);
                } else {
                    current->trans[i] = current->fail->trans[i];
                }
            }
        }
    }

    int query(const std::string &data) {
        int result = 0;
        pointer current = root;

        for (auto const &iter: data) {
            current = current->transfer(iter);

            for (pointer i = current; i != nullptr && i->value != -1; i = i->fail) {
                result += i->value;
                i->value = -1;
            }
        }

        return result;
    }
};

int main() {
    int N;

    std::cin >> N;

    AC ac;

    for (int i = 1; i <= N; ++i) {
        std::string str;

        std::cin >> str;

        ac.insert(str);
    }

    ac.build();

    std::string text;

    std::cin >> text;

    int const result = ac.query(text);

    std::cout << result << std::flush;

    return 0;
}
