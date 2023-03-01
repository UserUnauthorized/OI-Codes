//HZ - 42.5 [Splay]
//Luogu - P3391 [Splay]
//LOJ - 105 [Splay]
#include<bits/stdc++.h>

using namespace std;
typedef int valueType;

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

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

#ifndef OI_CODES_SPLAY_H
#define OI_CODES_SPLAY_H
//EDITED
#include<iostream>

struct NODE {
    typedef NODE self;
    typedef self *pointer;
    typedef self &reference;
    typedef ::valueType valueType;

    pointer father;
    pointer leftSon;
    pointer rightSon;
    self::valueType value;
    self::valueType count;
    self::valueType size;
    bool tag = false;

    NODE() : father(NULL), leftSon(NULL), rightSon(NULL), value(0), count(0), size(0), tag(false) {};

    pointer &son(bool _rightSon_) {
        return _rightSon_ ? this->rightSon : this->leftSon;
    }

    bool isRightSon() const {
        return this == (this->father)->rightSon;
    }

    void update() {
        this->size = (this->leftSon != NULL ? (this->leftSon)->size : 0) +
                     (this->rightSon != NULL ? (this->rightSon)->size : 0) + this->count;
    }

    void init() {
        this->leftSon = this->rightSon = this->father = NULL;
        this->value = 0;
        this->count = this->size = 1;
    }

    friend std::ostream &operator<<(std::ostream &output, const self &Object) {
        if (Object.leftSon != NULL) {
            output << Object.value << ' ' << Object.leftSon->value << ' ' << 0 << std::endl;
            output << *(Object.leftSon);
        }

        if (Object.rightSon != NULL) {
            output << Object.value << ' ' << Object.rightSon->value << ' ' << 1 << std::endl;
            output << *(Object.rightSon);
        }
        return output;
    }

    friend std::ostream &operator<<(std::ostream &output, pointer Object) {
        output << *Object;
        return output;
    }

    friend void outData(std::ostream &output, pointer Object) {
        if (Object == NULL)
            return;

        output << Object->value << ' ' << Object->count << ' ' << Object->size << std::endl;

        if (Object->leftSon != NULL)
            outData(output, Object->leftSon);

        if (Object->rightSon != NULL)
            outData(output, Object->rightSon);
    }
};

class SPLAY {
public:
    typedef NODE node;
    typedef node::pointer pointer;
    typedef SPLAY self;
    typedef node::valueType valueType;

private:
    static const self::valueType preNotFoundValue = -1;
    static const self::valueType nextNotFoundValue = -1;
    static const self::valueType minNotFoundValue = INT_MAX;
    static const self::valueType maxNotFoundValue = INT_MIN;

    pointer newNode() {
        return (pointer) malloc(sizeof(NODE));
    }

    void delNode(pointer &p) {
        free(p);
        p = NULL;
    }

public:
    pointer root;

    SPLAY() : root(NULL) {};

    void rotate(const pointer &current) {
        pointer father = current->father;
        bool isRightSon = current->isRightSon();
        father->son(isRightSon) = current->son(!isRightSon);

        if (current->son(!isRightSon) != NULL) {
            (current->son(!isRightSon))->father = father;
        }


        if ((current->father = father->father))
            (current->father)->son(father->isRightSon()) = current;

        father->father = current;
        current->son(!isRightSon) = father;
        father->update();
        current->update();

        if (current->father == NULL)
            this->root = current;
    }

    void splay(const pointer &current, pointer to = NULL) {
        for (pointer father = current->father; (father = current->father) != to; rotate(current))
            if (father->father != to)
                rotate(current->isRightSon() == father->isRightSon() ? father : current);
    }

    void insert(self::valueType key) {
        if (this->root == NULL) {
            this->root = this->newNode();
            this->root->init();
            this->root->value = key;
            return;
        }

        pointer current(this->root), father(NULL);

        for (;; father = current, current = current->son(key > current->value)) {
            if (current == NULL) {
                current = this->newNode();
                current->init();
                current->father = father;
                current->value = key;
                father->son(key > father->value) = current;
                this->splay(current);
                return;
            }

            if (current->value == key) {
                ++current->count;
                this->splay(current);
                return;
            }
        }
    }

    pointer find(self::valueType key) {
        pointer result = this->root;
        push(result);
        while (result != NULL && result->value != key) {
            push(result);
            result = result->son(key > result->value);
        }
        push(result);

        if (result != NULL)
            this->splay(result);

        return result;
    }

    void remove(self::valueType key) {
        pointer current = find(key);

        if (current == NULL)
            exit(1);
        push(current);
        this->splay(current);

        current = this->root;

        if (current->count > 1) {
            --current->count;
            current->update();
            return;
        }

        if (current->leftSon == NULL && current->rightSon == NULL) {
            this->delNode(current);
            this->root = NULL;
            return;
        }

        if (current->leftSon == NULL) {
            this->root = current->rightSon;
            this->root->father = NULL;
            delNode(current);
            return;
        }

        if (current->rightSon == NULL) {
            this->root = current->leftSon;
            this->root->father = NULL;
            delNode(current);
            return;
        }

        pre(current->value);
        current->rightSon->father = this->root;
        this->root->rightSon = current->rightSon;
        delNode(current);
        root->update();
    }

    self::valueType rank(self::valueType key) {
        pointer current = find(key);
        bool newNodeCreated = false;

        if (current == NULL) {
            insert(key);
            newNodeCreated = true;
        }

        int result = 1;

        if (root->leftSon != NULL)
            result += (root->leftSon)->size;

        if (newNodeCreated)
            remove(key);
        else
            this->splay(current);

        return result;
    }

    self::valueType kth(self::valueType key) {
        pointer current = this->root;

        while (true) {
            if (current->leftSon != NULL && key <= (current->leftSon)->size) {
                current = current->leftSon;
                continue;
            }

            if (current->leftSon != NULL)
                key -= (current->leftSon)->size;

            key -= current->count;

            if (key <= 0) {
                this->splay(current);
                return current->value;
            }

            current = current->rightSon;
        }
    }

    self::valueType pre(self::valueType key) {
        pointer current = this->find(key);
        bool newNodeCreated = false;

        if (current == NULL) {
            insert(key);
            current = this->root;
            newNodeCreated = true;
        }

        if (current->leftSon == NULL) {
            if (newNodeCreated)
                remove(key);

            return this->preNotFoundValue;
        }

        for (current = current->leftSon; current->rightSon != NULL; current = current->rightSon);

        if (newNodeCreated)
            remove(key);

        this->splay(current);

        return current->value;
    }

    self::valueType next(self::valueType key) {
        pointer current = this->find(key);
        bool newNodeCreated = false;

        if (current == NULL) {
            insert(key);
            current = this->root;
            newNodeCreated = true;
        }

        if (current->rightSon == NULL) {
            if (newNodeCreated)
                remove(key);

            return this->nextNotFoundValue;
        }

        for (current = current->rightSon; current->leftSon != NULL; current = current->leftSon);

        if (newNodeCreated)
            remove(key);

        this->splay(current);

        return current->value;
    }

    bool empty() const {
        return this->root == NULL;
    }

    self::valueType min() {
        if (this->empty())
            return this->minNotFoundValue;

        pointer current = this->root;

        while (current->leftSon != NULL)
            current = current->leftSon;

        this->splay(current);
        return current->value;
    }

    self::valueType max() {
        if (this->empty())
            return this->maxNotFoundValue;

        pointer current = this->root;

        while (current->rightSon != NULL)
            current = current->rightSon;

        this->splay(current);
        return current->value;
    }

    self::valueType size() const {
        if (this->empty())
            return 0;

        return this->root->size;
    }

    void update(self::valueType key) {
        if (this->empty())
            return;

        this->update(this->root, key);
    }


private:
    void update(pointer current, self::valueType key) {
        current->value += key;

        if (current->leftSon != NULL)
            update(current->leftSon, key);

        if (current->rightSon != NULL)
            update(current->rightSon, key);
    }

public:
    friend std::ostream &operator<<(std::ostream &output, const self &Object) {
        output << "TREE BEGIN" << std::endl;
        if (Object.root != NULL)
            output << Object.root;
        output << "TREE END" << std::endl;
        output << "==========" << std::endl;
        output << "DATA BEGIN" << std::endl;
        if (Object.root != NULL)
            outData(output, Object.root);
        output << "DATA END" << std::endl;
        return output;
    }

//TEMP CODE
public:
    pointer findBySize(self::valueType key) {
        pointer current = this->root;

        while (true) {
            push(current);

            if (current->leftSon != NULL && key <= (current->leftSon)->size) {
                current = current->leftSon;
                continue;
            }

            if (current->leftSon != NULL)
                key -= (current->leftSon)->size;

            key -= current->count;

            if (key <= 0) {
                return current;
            }

            current = current->rightSon;
        }
    }

    void build(self::valueType key) {
        this->root = this->newNode();
        this->root->init();
        this->root->value = INT_MIN;

        pointer current = root->rightSon, father = root;
        for (int i = 1; i <= key; ++i, current = current->rightSon, father = father->rightSon) {
            current = this->newNode();
            current->init();
            current->father = father;
            father->rightSon = current;
            father->update();
            current->value = i;
        }

        current = this->newNode();
        current->init();
        current->father = father;
        father->rightSon = current;
        father->update();
        current->value = INT_MAX;

        this->splay(current);
    }

    void reserve(self::valueType l, self::valueType r) {
        pointer current = NULL;
        this->splay(findBySize(l - 1));
        this->splay(current = findBySize(r + 1), this->root);

        current = current->leftSon;

        current->tag ^= 1;
    }

    void outPut() {
        this->out(this->root);
    }

private:
    void out(pointer current) {
        push(current);

        if (current->leftSon != NULL)
            out(current->leftSon);

        std::cout << current->value << ' ';

        if (current->rightSon != NULL)
            out(current->rightSon);
    }

    void push(pointer current) {
        if (current->tag == false)
            return;

        current->tag = false;
        swap(current->leftSon, current->rightSon);

        if (current->leftSon != NULL) {
            current->leftSon->tag ^= 1;
        }

        if (current->rightSon != NULL) {
            current->rightSon->tag ^= 1;
        }
    }
};

#endif //OI_CODES_SPLAY_H

#include<bits/stdc++.h>

using namespace std;

int main() {
    SPLAY tree;
    valueType n, m;

    cin >> n >> m;
    tree.build(n);

    while (m--) {
        valueType l, r;
        cin >> l >> r;
        tree.reserve(l + 1, r + 1);
    }

    tree.remove(INT_MIN);
    tree.remove(INT_MAX);
    tree.outPut();
    return 0;
}
