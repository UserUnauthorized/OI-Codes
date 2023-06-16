//HZ - 38.4
//Luogu - P2444
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
    static sizeType const charSetSize = 2;
    typedef std::vector<valueType> Vector;

private:
    static sizeType converter(char c) {
        if (c == '0')
            return 0;

        if (c == '1')
            return 1;

        throw std::range_error("");
    }

    struct NODE {
        typedef NODE self;
        typedef self *pointer;

        std::array<pointer, charSetSize> trans;

        std::list<pointer> son;

        bool visited;

        bool inPath;

        bool isEnd;

        pointer fail;

        NODE() : trans(), son(), visited(false), inPath(false), isEnd(false), fail(nullptr) {
            trans.fill(nullptr);
        }

        pointer &transfer(char c) {
            return trans[converter(c)];
        }
    };

    typedef NODE::pointer pointer;

    pointer allocate() {
        return new NODE();
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

        current->isEnd = true;
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

            current->fail->son.push_back(current);

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

    void push(const std::string &data) {
        pointer current = root;

        for (auto const &iter: data)
            current = current->transfer(iter);

        push(current);
    }

    bool check() {
        return check(root);
    }

private:
    void push(const pointer &current) {
        current->isEnd = true;

        for (auto const &iter: current->son)
            if (!iter->isEnd)
                push(iter);
    }

    bool check(const pointer &current) {
        if (current == nullptr)
            return false;

        if (current->isEnd)
            return false;

        if (current->inPath)
            return true;

        current->inPath = true;

        bool result = false;

        if (current->trans[0] != nullptr && !current->trans[0]->visited) {
            result = result || check(current->trans[0]);
            current->trans[0]->visited = true;
        }

        if (current->trans[1] != nullptr && !current->trans[1]->visited) {
            result = result || check(current->trans[1]);
            current->trans[1]->visited = true;
        }

        current->inPath = false;

        return result;
    }
};

int main() {
    int N;

    std::cin >> N;

    AC ac;

    std::vector<std::string> source(N + 1);

    for (int i = 1; i <= N; ++i) {
        std::cin >> source[i];

        ac.insert(source[i]);
    }

    ac.build();

    for (int i = 1; i <= N; ++i)
        ac.push(source[i]);

    bool const result = ac.check();

    std::cout << (result ? "TAK" : "NIE") << std::flush;

    return 0;
}
