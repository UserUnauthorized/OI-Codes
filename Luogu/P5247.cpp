//Luogu - P5247
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

constexpr int maxN = 5005, maxM = 5e5 + 5;

typedef int valueType;

constexpr valueType MAX = INT_MAX >> 1;

class LCT {
public:
    struct NODE {
        typedef NODE self;
        typedef self *pointer;
        typedef unsigned int posType;

        pointer father;
        pointer leftSon;
        pointer rightSon;

        bool tag;
        valueType value;
        valueType size;
        valueType min;
        valueType add;

        posType nodeId;

        pointer &son(bool _rightSon_) {
            return _rightSon_ ? this->rightSon : this->leftSon;
        }

        bool isRightSon() const {
            return this == (this->father)->rightSon;
        }

        void update() {
            this->push();

            this->size = (this->leftSon != nullptr ? (this->leftSon)->size : 0) +
                         (this->rightSon != nullptr ? (this->rightSon)->size : 0) + 1;
            this->min = std::min({(this->leftSon != nullptr ? (this->leftSon)->min : MAX),
                                  (this->rightSon != nullptr ? (this->rightSon)->min : MAX), this->value});
        }

        void init() {
            this->leftSon = this->rightSon = this->father = nullptr;
            this->value = 0;
            this->size = 1;
            this->tag = false;
            this->add = 0;
        }

        void init(valueType key) {
            this->leftSon = this->rightSon = this->father = nullptr;
            this->value = key;
            this->size = 1;
            this->tag = false;
            this->add = 0;
        }

        void init(valueType key, posType id) {
            this->leftSon = this->rightSon = this->father = nullptr;
            this->value = key;
            this->size = 1;
            this->nodeId = id;
            this->tag = false;
            this->add = 0;
        }

        bool isRoot() {
            return this->father == nullptr || (this->father->leftSon != this && this->father->rightSon != this);
        }

        void push() {
            if (this->tag) {
                if (this->leftSon != nullptr) {
                    std::swap(this->leftSon->leftSon, this->leftSon->rightSon);
                    this->leftSon->tag = !this->leftSon->tag;
                }

                if (this->rightSon != nullptr) {
                    std::swap(this->rightSon->leftSon, this->rightSon->rightSon);
                    this->rightSon->tag = !this->rightSon->tag;
                }

                this->tag = false;
            }

            if (this->add != 0) {
                if (this->leftSon != nullptr) {
                    this->leftSon->value = this->leftSon->value + this->add;
                    this->leftSon->min = this->leftSon->min + this->add;
                    this->leftSon->add = this->leftSon->add + this->add;
                }

                if (this->rightSon != nullptr) {
                    this->rightSon->value = this->rightSon->value + this->add;
                    this->rightSon->min = this->rightSon->min + this->add;
                    this->rightSon->add = this->rightSon->add + this->add;
                }

                this->add = 0;
            }
        }

        friend std::ostream &operator<<(std::ostream &output, pointer Object) {
            if (Object == nullptr)
                return output;

            output << "nodeId:" << Object->nodeId;
            output << "\tisRoot:" << Object->isRoot() << std::endl;
            output << Object->value << ' ' << Object->min << ' ';
            output << "leftSon:" << (Object->leftSon != nullptr ? Object->leftSon->nodeId : 0) << "\trightSon:"
                   << (Object->rightSon != nullptr ? Object->rightSon->nodeId : 0) << "\tfather:"
                   << (Object->father != nullptr ? Object->father->nodeId : 0) << std::endl << std::endl << std::endl;

            return output;
        }
    };

    typedef NODE::pointer pointer;

    typedef NODE::posType posType;

protected:
    size_t _size_;

    std::vector<pointer> node;

public:
    LCT() : _size_(0) {};

    LCT(size_t size) : _size_(size), node(_size_ + 1) {
        node[0] = this->newNode();
        node[0]->init(MAX);
    };

    class NoSuchEdgeException : protected std::exception {
    private:
        const char *message;

    public:
        explicit NoSuchEdgeException(const char *msg) : message(msg) {}

        const char *what() const noexcept override { return message; }
    };

    class AlreadyConnectedException : protected std::exception {
    private:
        const char *message;

    public:
        explicit AlreadyConnectedException(const char *msg) : message(msg) {}

        const char *what() const noexcept override { return message; }
    };

private:
    pointer newNode() {
        return (pointer) malloc(sizeof(NODE));
    }

public:
    void set(posType x, valueType key) {
        if (x > this->_size_)
            throw std::range_error("larger than size.");

        if (node[x] == nullptr) {
            node[x] = this->newNode();
            node[x]->init(key, x);
            node[x]->update();
        } else {
            this->splay(node[x]);
            node[x]->value = key;
            node[x]->update();
        }
    }

    posType access(posType x) {
        if (x > this->_size_)
            throw std::range_error("larger than size.");

        return this->access(node[x]);
    }

    void makeRoot(posType x) {
        if (x > this->_size_)
            throw std::range_error("larger than size.");

        this->makeRoot(node[x]);
    }

    void link(posType x, posType y) {
        if (x > this->_size_ || y > this->_size_)
            throw std::range_error("larger than size.");

        this->link(node[x], node[y]);
    }

    void cut(posType x, posType y) {
        if (x > this->_size_ || y > this->_size_)
            throw std::range_error("larger than size.");

        this->cut(node[x], node[y]);
    }

    valueType ans(posType x, posType y) {
        if (x > this->_size_ || y > this->_size_)
            throw std::range_error("larger than size.");

        return this->split(node[x], node[y])->min;
    }

    posType find(posType x) {
        if (x > this->_size_)
            throw std::range_error("larger than size.");

        return this->find(node[x]);
    }

    std::queue<LCT::posType> add(posType x, posType y, valueType key) {
        if (x > this->_size_ || y > this->_size_)
            throw std::range_error("larger than size.");

        pointer current = this->split(node[x], node[y]);
        current->value = current->value + key;
        current->add = current->add + key;
        current->min = current->min + key;
//		current->push();
        current->update();

        std::queue<LCT::posType> result;

        this->check(current, result);

        return result;
    }

protected:
    void check(pointer current, std::queue<LCT::posType> &que) {
        if (current == nullptr || current->min >= 0)
            return;

        current->push();

        check(current->leftSon, que);

        check(current->rightSon, que);

        if (current->value < 0)
            que.push(current->nodeId);
    }

protected:
    void rotate(pointer current) {
        pointer father = current->father;
        bool const isRightSon = current->isRightSon();

        father->son(isRightSon) = current->son(!isRightSon);

        if (current->son(!isRightSon) != nullptr) {
            (current->son(!isRightSon))->father = father;
        }

        if ((current->father = father->father) != nullptr && !father->isRoot())
            (current->father)->son(father->isRightSon()) = current;

        father->father = current;
        current->son(!isRightSon) = father;
        father->update();
        current->update();
    }

    void splay(pointer current) {
        update(current);

        for (pointer father = current->father; !current->isRoot(); rotate(current))
            if (!(father = current->father)->isRoot())
                rotate(current->isRightSon() == father->isRightSon() ? father : current);
    }

    void update(pointer current) {
        if (!current->isRoot())
            update(current->father);

        current->push();
    }

    posType access(pointer current) {

        pointer pre = nullptr;

        for (pre = nullptr; current != nullptr; pre = current, current = current->father) {
            this->splay(current);

            current->rightSon = pre;

            current->update();
        }

        return pre == nullptr ? 0 : pre->nodeId;
    }

    void makeRoot(pointer current) {
        posType const p = this->access(current);

        if (p == 0)
            return;

        current = node[p];

        std::swap(current->leftSon, current->rightSon);

        current->tag = !current->tag;
    }

    void link(pointer x, pointer y) {
        this->makeRoot(x);

        this->splay(x);

        if (this->find(y) == x->nodeId)
            throw AlreadyConnectedException("Already Connected");

        x->father = y;
    }

    pointer split(pointer x, pointer y) {
        this->makeRoot(x);

        this->access(y);

        this->splay(y);

        return y;
    }

    void cut(pointer x, pointer y) {
        this->makeRoot(x);

        this->access(y);

        this->splay(y);

        if (this->find(y->nodeId) != x->nodeId)
            throw NoSuchEdgeException("Disconnected");

        this->splay(y);

        if (y->leftSon != x || x->rightSon != nullptr)
            throw NoSuchEdgeException("There are other edges between the nodes.");

        y->leftSon = x->father = nullptr;

        y->update();
    }

    posType find(pointer current) {
        this->access(current);

        this->splay(current);

        current->push();

        while (current->leftSon != nullptr) {
            current = current->leftSon;

            current->push();
        }

        this->splay(current);

        return current->nodeId;
    }

public:
    void out() {
        for (size_t i = 1; i <= _size_; ++i)
            std::cerr << node[i];
    }
};

int N_, M_;
int const &N = N_, &M = M_;

//std::map<std::pair<LCT::posType, LCT::posType>, int> id;
std::array<std::pair<LCT::posType, LCT::posType>, maxM> connection;

constexpr LCT::posType shifting = 100;

int main() {
#ifdef LOCAL
    freopen("ex_negiizhao_3.in", "r", stdin);
    freopen("ex_negiizhao_3.ans", "w", stdout);
    freopen("ex_negiizhao_3.err", "w", stderr);
#endif

    std::cin >> N_ >> M_;
    debug(N, M);
    LCT tree(N + M + shifting);

    for (int i = 0; i <= N; ++i)
        tree.set(i + shifting, MAX);

    for (int i = 1; i <= M; ++i)
        tree.set(N + i + shifting, 0);

    int lastAns = 0;

    for (int i = 1; i <= M; ++i) {
        LCT::posType x, y;
        int op;

        std::cin >> op >> x >> y;
        debug(op, i, x, y);
        x ^= lastAns;
        y ^= lastAns;
        debug(x, y, lastAns);
        if (x > N || y > N)
            throw std::range_error("out of size");

        x += shifting;
        y += shifting;

        if (x == 0 || y == 0)
            throw std::range_error("zero id.");

        debug(i, op, x, y);
        if (op == 0) {
            if (x == y)
//				throw std::range_error("self edge.");
                continue;

//			connection[i] = std::make_pair(x, y);

            if (tree.find(x) == tree.find(y)) {
                tree.add(x, y, 1);
                connection[i] = std::make_pair(x, y);
            } else {
//				debug(x, y, N + i);
                tree.link(x, N + i + shifting);
                tree.link(y, N + i + shifting);
                connection[i] = std::make_pair(x, y);
            }
        } else if (op == 1) {
            std::queue<LCT::posType> que = tree.add(x, y, -1);

            while (!que.empty()) {
                if (que.front() <= (unsigned int) N + shifting)
                    throw std::underflow_error("Not an edge node.");

                LCT::posType const id = que.front() - N - shifting;

                LCT::posType x = connection[id].first, y = connection[id].second;

                debug(id, x, y);
                tree.cut(x, id + N + shifting);
                debug(x, id);
                tree.cut(y, id + N + shifting);
                debug(y, id);

                que.pop();
            }
        } else if (op == 2) {
            bool const connected = tree.find(x) == tree.find(y);

            bool const haveEdge = tree.ans(x, y) >= 0;

            bool const result = connected && haveEdge;

            if (result) {
                std::cout << "Y\n";
                lastAns = x - shifting;
            } else {
                std::cout << "N\n";
                lastAns = y - shifting;
            }
        }
    }
}
