//HZ - 80.2
#include<bits/stdc++.h>

typedef int valueType;

constexpr valueType MIN = INT_MIN >> 1;
constexpr valueType MAX = INT_MAX >> 1;

int N_;
int const &N = N_;

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
        valueType min, max;
        bool reverse;

        posType nodeId;

        pointer &son(bool _rightSon_) {
            return _rightSon_ ? this->rightSon : this->leftSon;
        }

        bool isRightSon() const {
            return this == (this->father)->rightSon;
        }

        void update() {
            this->size = (this->leftSon != nullptr ? (this->leftSon)->size : 0) +
                         (this->rightSon != nullptr ? (this->rightSon)->size : 0) + 1;
            this->max = std::max((this->leftSon != nullptr ? (this->leftSon)->max : MIN),
                                 (this->rightSon != nullptr ? (this->rightSon)->max : MIN));
            this->min = std::min((this->leftSon != nullptr ? (this->leftSon)->min : MAX),
                                 (this->rightSon != nullptr ? (this->rightSon)->min : MAX));

            if (this->nodeId > N) {
                this->max = std::max(this->max, this->value);
                this->min = std::min(this->min, this->value);
            }
        }

        void init() {
            this->leftSon = this->rightSon = this->father = nullptr;
            this->value = 0;
            this->size = 1;
            this->reverse = this->tag = false;
        }

        void init(valueType key) {
            this->leftSon = this->rightSon = this->father = nullptr;
            this->value = key;
            this->size = 1;
            this->reverse = this->tag = false;
        }

        void init(valueType key, posType id) {
            this->leftSon = this->rightSon = this->father = nullptr;
            this->value = key;
            this->size = 1;
            this->nodeId = id;
            this->reverse = this->tag = false;
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

            if (this->reverse) {
                if (this->leftSon != nullptr) {
                    this->leftSon->value = -this->leftSon->value;
                    std::swap(this->leftSon->max, this->leftSon->min);
                    this->leftSon->max = -this->leftSon->max;
                    this->leftSon->min = -this->leftSon->min;
                    this->leftSon->reverse = !this->leftSon->reverse;
                }

                if (this->rightSon != nullptr) {
                    this->rightSon->value = -this->rightSon->value;
                    std::swap(this->rightSon->max, this->rightSon->min);
                    this->rightSon->max = -this->rightSon->max;
                    this->rightSon->min = -this->rightSon->min;
                    this->rightSon->reverse = !this->rightSon->reverse;
                }

                this->reverse = false;
            }
        }

        friend std::ostream &operator<<(std::ostream &output, pointer Object) {
            if (Object == nullptr)
                return output;

            output << "nodeId:" << Object->nodeId;
            output << "\tisRoot:" << Object->isRoot() << std::endl;
            output << Object->value << ' ' << Object->max << ' ';
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
        node[0]->init();
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
        return this->access(node[x]);
    }

    void makeRoot(posType x) {
        this->makeRoot(node[x]);
    }

    void link(posType x, posType y) {
        this->link(node[x], node[y]);
    }

    void cut(posType x, posType y) {
        this->cut(node[x], node[y]);
    }

    valueType ans(posType x, posType y) {
        return this->split(node[x], node[y])->max;
    }

    void reverse(posType x, posType y) {
        pointer const current = this->split(node[x], node[y]);
        current->reverse = !current->reverse;
        current->value = -current->value;

        std::swap(current->min, current->max);
        current->max = -current->max;
        current->min = -current->min;
    }

    posType find(posType x) {
        return this->find(node[x]);
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

int main() {
    std::cin >> N_;

    LCT tree(N << 1);

    for (int i = 1; i <= N; ++i)
        tree.set(i, MIN);

    for (int i = 1; i < N; ++i) {
        LCT::posType a, b;
        int c;

        std::cin >> a >> b >> c;

        tree.set(i + N, c);

        tree.link(a, i + N);
        tree.link(b, i + N);
    }

    std::string order;

    while (std::cin >> order && order != "DONE") {
        if (order == "CHANGE") {
            int i, v;

            std::cin >> i >> v;

            tree.set(N + i, v);
        } else if (order == "NEGATE") {
            int a, b;

            std::cin >> a >> b;

            tree.reverse(a, b);
        } else if (order == "QUERY") {
            int a, b;

            std::cin >> a >> b;

            std::cout << tree.ans(a, b) << '\n';
        }
    }

    return 0;
}
