//HZ - 38.5
//Luogu - P2322
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
    typedef long long valueType;
    typedef size_t sizeType;
    static sizeType const charSetSize = 26;
    typedef std::vector<valueType> Vector;

private:
    static sizeType converter(char c) {
        return c - 'a';

        throw std::range_error("");
    }

    static char reConverter(sizeType x) {
        return (char) x + 'a';
    }

    struct NODE {
        typedef NODE self;
        typedef self *pointer;

        std::array<pointer, charSetSize> trans;

        int endId;

        std::vector<bool> visited;

        pointer fail;

        NODE(sizeType size) : trans(), endId(0), visited(size, false), fail(nullptr) {
            trans.fill(nullptr);
        }

        pointer &transfer(char c) {
            return trans[converter(c)];
        }
    };

    typedef NODE::pointer pointer;

    pointer allocate(sizeType siz) {
        return new NODE(siz);
    }

    valueType stateSize;

    sizeType size;

    pointer root;

public:
    AC(sizeType s) : stateSize(1 << s), size(s), root(allocate(stateSize)) {};

    void insert(const std::string &data, int id) {
        pointer current = this->root;
        debug(data);

        for (auto const &iter: data) {
            if (current->transfer(iter) == nullptr) {
                current->transfer(iter) = allocate(stateSize);

                current = current->transfer(iter);
            } else {
                current = current->transfer(iter);
            }

            debug(iter, current, root);
        }

        current->endId |= 1 << id;
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

            pointer from = current->fail;

            while (from != root && from->endId == 0)
                from = from->fail;

            current->endId = current->endId | from->endId;
        }
    }

private:
    struct STATUS {
        pointer current;

        int state;

        int id;

        STATUS() : current(nullptr), state(0), id(0) {};

        STATUS(pointer cur, int sta, int i) : current(std::move(cur)), state(sta), id(i) {};

        friend std::ostream &operator<<(std::ostream &os, STATUS const &sta) {
            os << sta.current << ' ' << sta.state << ' ' << sta.id << std::endl;

            return os;
        }
    };

public:
    std::string ans() {
        sizeType const S = 2500050;

        std::vector<int> from(S, 0);

        std::vector<char> path(S);

        int count = 0;

        int const end = (1 << size) - 1;

        std::queue<STATUS> que;

        que.emplace(root, 0, ++count);

        while (!que.empty()) {
            auto const now = que.front();

            que.pop();

            pointer current = now.current;

            current->visited[now.state] = true;

            for (sizeType i = 0; i < charSetSize; ++i) {
                STATUS next;

                next.current = current->trans[i];
                next.state = now.state | next.current->endId;

                if (next.current->visited[next.state])
                    continue;
                else
                    next.current->visited[next.state] = true;

                next.id = ++count;

                from[count] = now.id;

                path[count] = reConverter(i);

                if (next.state == end)
                    return paint(count, from, path);
                else
                    que.push(next);
            }
        }
    }

private:
    std::string paint(int id, const std::vector<int> &from, const std::vector<char> &path) {
        std::string result;

        while (id > 1) {
            result.push_back(path[id]);

            id = from[id];
        }

        std::reverse(result.begin(), result.end());

        return result;
    }
};

int main() {
    int L, N;

    std::cin >> L >> N;

    AC ac(N);

    for (int i = 0; i < N; ++i) {
        std::string text;

        std::cin >> text;

        ac.insert(text, i);
    }

    ac.build();

    std::cout << ac.ans() << std::flush;

    return 0;
}
