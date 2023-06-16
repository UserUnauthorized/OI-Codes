//HZ - 38.6
//Luogu - P4052
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

typedef int valueType;

constexpr valueType MOD = 1e4 + 7;

class AC {
public:
    typedef int valueType;
    typedef size_t sizeType;
    static sizeType const charSetSize = 26;
    typedef std::vector<valueType> Vector;

private:
    static sizeType converter(char c) {
        return c - 'A';

        throw std::range_error("");
    }

    struct NODE {
        typedef NODE self;
        typedef self *pointer;

        std::array<pointer, charSetSize> trans;

        bool isEnd;

        std::array<valueType, 2> ans, count;

        std::array<bool, 2> visited;

        pointer fail;

        NODE() : trans(), isEnd(false), ans(), count(), visited(), fail(nullptr) {
            trans.fill(nullptr);
            visited.fill(false);
            ans.fill(0);
            count.fill(0);
        }

        pointer &transfer(char c) {
            return trans[converter(c)];
        }
    };

    typedef NODE::pointer pointer;

    pointer allocate() {
        return new NODE();
    }

    sizeType size;

    pointer root;

public:
    AC(sizeType s) : size(s), root(allocate()) {};

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

            for (sizeType i = 0; i < charSetSize; ++i) {
                if (current->trans[i] != nullptr) {
                    current->trans[i]->fail = current->fail->trans[i];

                    que.push(current->trans[i]);
                } else {
                    current->trans[i] = current->fail->trans[i];
                }
            }

            if (current->isEnd)
                continue;

            pointer from = current->fail;

            while (from != root && from->isEnd == false)
                from = from->fail;

            current->isEnd = current->isEnd || from->isEnd;
        }
    }

private:
    void push(const pointer &current, int tag) {
        current->visited[tag] = true;
        current->visited[tag ^ 1] = false;

        for (sizeType i = 0; i < charSetSize; ++i) {
            pointer to = current->trans[i];

            to->visited[tag ^ 1] = false;

            if (to->isEnd || current->isEnd) {
                to->ans[tag] = (to->ans[tag] + current->ans[tag ^ 1] + current->count[tag ^ 1]) % MOD;
            } else {
                to->ans[tag] = (to->ans[tag] + current->ans[tag ^ 1]) % MOD;

                to->count[tag] = (to->count[tag] + current->count[tag ^ 1]) % MOD;
            }

            if (to->visited[tag])
                continue;

            push(to, tag);
        }

        current->ans[tag ^ 1] = 0;
        current->count[tag ^ 1] = 0;
    }

    valueType calc(const pointer &current, int tag) {
        current->visited[tag ^ 1] = true;
        current->visited[tag] = false;

        valueType result = current->ans[tag];

        for (sizeType i = 0; i < charSetSize; ++i) {
            pointer to = current->trans[i];

            to->visited[tag] = false;

            if (to->visited[tag ^ 1])
                continue;

            result = (result + calc(to, tag)) % MOD;
        }

        return result;
    }

public:
    valueType ans(int x) {
        root->count[0] = 1;

        for (int i = 1; i <= x; ++i) {
            push(root, i & 1);
        }

        return calc(root, x & 1);
    }
};

int main() {
    int N, M;

    std::cin >> N >> M;

    AC ac(N);

    std::string text;

    text.reserve(50);

    for (int i = 0; i < N; ++i) {
        std::cin >> text;

        ac.insert(text);
    }

    ac.build();

    std::cout << ac.ans(M) << std::flush;

    return 0;
}
