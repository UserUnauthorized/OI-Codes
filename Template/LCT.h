#ifndef OI_CODES_LCT_H
#define OI_CODES_LCT_H

#include<bits/stdc++.h>

typedef int valueType;

class LCT {
public:
    struct NODE {
        typedef NODE self;
//        typedef std::shared_ptr<self> pointer;
        typedef self *pointer;
        typedef unsigned int posType;

        pointer father;
        pointer leftSon;
        pointer rightSon;

        bool tag;
        valueType value;
        valueType size;
        valueType sum;

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
            this->sum = (this->leftSon != nullptr ? (this->leftSon)->sum : 0) +
                        (this->rightSon != nullptr ? (this->rightSon)->sum : 0) + this->value;
        }

        NODE() : father(nullptr), leftSon(nullptr), rightSon(nullptr), tag(false), value(0), size(0), sum(0),
                 nodeId(0) {};

        NODE(valueType key, posType id) : father(nullptr), leftSon(nullptr), rightSon(nullptr), tag(false), value(key),
                                          size(1), sum(key), nodeId(id) {};

        bool isRoot() {
            return this->father == nullptr ||
                   (this->father->leftSon != this && this->father->rightSon != this);
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
        }

        friend std::ostream &operator<<(std::ostream &output, const pointer &Object) {
            if (Object == nullptr)
                return output;

            output << "nodeId:" << Object->nodeId;
            output << "\tisRoot:" << Object->isRoot() << std::endl;
            output << Object->value << ' ' << Object->sum << ' ';
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

private:
    static pointer allocateNode() {
//        return std::make_shared<NODE>();
        return new NODE();
    }

    static pointer allocateNode(valueType key, posType id) {
//        return std::make_shared<NODE>(key, id);
        return new NODE(key, id);
    }

public:
    LCT() : _size_(0) {};

    explicit LCT(size_t size) : _size_(size), node(_size_ + 1) {
        node[0] = allocateNode(0, 0);
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

public:
    void set(posType x, valueType key) {
        if (node[x] == nullptr) {
            node[x] = allocateNode(key, x);
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
        return this->split(node[x], node[y])->sum;
    }

    posType find(posType x) {
        return this->find(node[x]);
    }

    bool check(posType x, posType y) {
        return this->find(x) == this->find(y);
    }

protected:
    void rotate(const pointer &current) {
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

    void splay(const pointer &current) {
        update(current);

        for (pointer father = current->father; !current->isRoot(); rotate(current))
            if (!(father = current->father)->isRoot())
                rotate(current->isRightSon() == father->isRightSon() ? father : current);
    }

    void update(const pointer &current) {
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

    void link(const pointer &x, const pointer &y) {
        this->makeRoot(x);

        this->splay(x);

        if (this->find(y) == x->nodeId)
            throw AlreadyConnectedException("Already Connected");

        x->father = y;
    }

    pointer split(pointer x, const pointer &y) {
        this->makeRoot(std::move(x));

        this->access(y);

        this->splay(y);

        return y;
    }

    void cut(const pointer &x, const pointer &y) {
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

#endif //OI_CODES_LCT_H
