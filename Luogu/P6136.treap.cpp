//Luogu - P6136 [Treap]
#include<bits/stdc++.h>

using namespace std;

mt19937 getRand(22516);

struct NODE {
    typedef NODE self;
    typedef long long valueType;
    typedef self *pointer;
    typedef unsigned int randType;

    pointer leftSon;
    pointer rightSon;
    pointer father;
    randType priority;

    self::valueType value;
    self::valueType count;
    self::valueType size;

    NODE() : leftSon(NULL), rightSon(NULL), father(NULL), priority(0), value(0), count(0), size(0) {};

    void init() {
        this->leftSon = this->rightSon = this->father = NULL;
        this->priority = ::getRand();
        this->value = 0;
        this->count = this->size = 1;
    }

    pointer &son(bool _rightSon_) {
        return _rightSon_ ? this->rightSon : this->leftSon;
    }

    pointer &son(self::valueType key) {
        return key > this->value ? this->rightSon : this->leftSon;
    }

    bool isRightSon() const {
        return this == (this->father)->rightSon;
    }

    void update() {
        this->size = (this->leftSon != NULL ? (this->leftSon)->size : 0) +
                     (this->rightSon != NULL ? (this->rightSon)->size : 0) + this->count;
    }

    friend void outPath(std::ostream &output, pointer Object) {
        if (Object->leftSon != NULL) {
            output << Object->value << ' ' << Object->leftSon->value << ' ' << 0 << std::endl;
            outPath(output, Object->leftSon);
        }

        if (Object->rightSon != NULL) {
            output << Object->value << ' ' << Object->rightSon->value << ' ' << 1 << std::endl;
            outPath(output, Object->rightSon);
        }
    }

    friend void outData(std::ostream &output, pointer Object) {
        if (Object == NULL)
            return;

        output << Object->value << ' ' << Object->count << ' ' << Object->size << ' ' << Object->priority << std::endl;

        if (Object->leftSon != NULL)
            outData(output, Object->leftSon);

        if (Object->rightSon != NULL)
            outData(output, Object->rightSon);
    }
};

class TREAP {
public:
    typedef NODE node;
    typedef node::pointer pointer;
    typedef TREAP self;
    typedef node::valueType valueType;

private:
    static const self::valueType preNotFoundValue = -1;
    static const self::valueType nextNotFoundValue = -1;
    static const self::valueType minValue = INT_MIN;
    static const self::valueType maxValue = INT_MAX;
    static const self::valueType minNotFoundValue = self::minValue;
    static const self::valueType maxNotFoundValue = self::maxValue;

    pointer newNode() {
        return (pointer) malloc(sizeof(NODE));
    }

    void delNode(pointer &p) {
        free(p);
        p = NULL;
    }

public:
    pointer root;

    TREAP() : root(NULL) {};

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

    void treap(const pointer &current) {
        while (current->father != NULL && current->father->priority > current->priority)
            this->rotate(current);
    }

    void insert(self::valueType key) {
        if (this->root == NULL) {
            this->root = this->newNode();
            this->root->init();
            this->root->value = key;
            return;
        }

        pointer current = this->root;
        pointer father = NULL;

        while (current != NULL && key != current->value) {
            ++current->size;
            father = current;
            current = current->son(key);
        }

        if (current == NULL) {
            current = this->newNode();
            current->init();
            current->value = key;
            current->father = father;
            if (father != NULL)
                father->son(key) = current;

            this->treap(current);
        } else {
            ++current->count;
            ++current->size;
        }
    }

    void remove(self::valueType key) {
        pointer current = this->root;

        while (/*current != NULL &&*/ key != current->value) {
            --current->size;
            current = current->son(key);
        }

        /*if(currnet == NULL)
            exit(1)*/
        --current->size;
        --current->count;

        if (current->count > 0)
            return;

        while (current->leftSon != NULL && current->rightSon != NULL) {
            pointer son = current->son(current->leftSon->priority > current->rightSon->priority);
            this->rotate(son);
        }

        if (current->leftSon != NULL) {
            current->leftSon->father = current->father;

            if (current->father != NULL) {
                bool const isRightSon = current->isRightSon();
                current->father->son(isRightSon) = current->leftSon;
                current->father->update();
            } else {
                this->root = current->leftSon;
            }
        } else if (current->rightSon != NULL) {
            current->rightSon->father = current->father;

            if (current->father != NULL) {
                bool const isRightSon = current->isRightSon();
                current->father->son(isRightSon) = current->rightSon;
                current->father->update();
            } else {
                this->root = current->rightSon;
            }

        } else {
            if (current->father != NULL)
                current->father->son(current->isRightSon()) = NULL;
            else
                this->root = NULL;
        }

        this->delNode(current);
    }

    self::valueType rank(self::valueType key) const {
        pointer current = this->root;
        self::valueType result(1);

        while (current != NULL) {
            while (current != NULL && key <= current->value)
                current = current->leftSon;

            while (current != NULL && key > current->value) {
                result += current->count;

                if (current->leftSon != NULL)
                    result += current->leftSon->size;

                current = current->rightSon;
            }
        }

        return result;
    }

    self::valueType kth(self::valueType key) const {
        pointer current = this->root;

        while (true) {
            if (current->leftSon != NULL && key <= (current->leftSon)->size) {
                current = current->leftSon;
                continue;
            }

            if (current->leftSon != NULL)
                key -= (current->leftSon)->size;

            key -= current->count;

            if (key <= 0)
                return current->value;

            current = current->rightSon;
        }
    }

    self::valueType pre(self::valueType key) const {
        pointer current = this->root;
        self::valueType result = this->minValue;

        while (current != NULL) {
            while (current != NULL && current->value >= key)
                current = current->leftSon;

            while (current != NULL && current->value < key) {
                result = std::max(result, current->value);
                current = current->rightSon;
            }
        }

        if (result == this->minValue)
            return this->preNotFoundValue;

        return result;
    }

    self::valueType next(self::valueType key) const {
        pointer current = this->root;
        self::valueType result = this->maxValue;

        while (current != NULL) {
            while (current != NULL && current->value <= key)
                current = current->rightSon;

            while (current != NULL && current->value > key) {
                result = std::min(result, current->value);
                current = current->leftSon;
            }
        }

        if (result == this->maxValue)
            return this->nextNotFoundValue;

        return result;
    }

public:
    friend std::ostream &operator<<(std::ostream &output, const self &Object) {
        output << "TREE BEGIN" << std::endl;
        if (Object.root != NULL)
            outPath(output, Object.root);;
        output << "TREE END" << std::endl;
        output << "==========" << std::endl;
        output << "DATA BEGIN" << std::endl;
        if (Object.root != NULL)
            outData(output, Object.root);
        output << "DATA END" << std::endl;
        return output;
    }
} tree;

int main() {
    int n, m;
    long long lastAns = 0;
    long long ans = 0;

    cin >> n >> m;

    while (n--) {
        long long t;
        cin >> t;
        tree.insert(t);
    }

    while (m--) {
        long long opt, x;
        cin >> opt >> x;
        x ^= lastAns;

        if (opt == 1)
            tree.insert(x);
        else if (opt == 2)
            tree.remove(x);
        else if (opt == 3)
            ans ^= (lastAns = tree.rank(x));
        else if (opt == 4)
            ans ^= (lastAns = tree.kth(x));
        else if (opt == 5)
            ans ^= (lastAns = tree.pre(x));
        else if (opt == 6)
            ans ^= (lastAns = tree.next(x));
    }

    cout << ans;

    return 0;
}
