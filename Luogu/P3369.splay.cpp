//HZ - 42.4
//Luogu - P3369
#include<bits/stdc++.h>

using namespace std;
typedef long long valueType;
constexpr valueType maxN = 1e5 + 5;

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

    NODE() : father(NULL), leftSon(NULL), rightSon(NULL), value(0), count(0), size(0) {};

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
            output << Object.value << ' ' << Object.leftSon->value << ' ' << 0 << endl;
            output << *(Object.leftSon);
        }

        if (Object.rightSon != NULL) {
            output << Object.value << ' ' << Object.rightSon->value << ' ' << 1 << endl;
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

        output << Object->value << ' ' << Object->count << ' ' << Object->size << endl;

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

    void splay(const pointer &current) {
        for (pointer father = current->father; (father = current->father) != NULL; rotate(current))
            if (father->father != NULL)
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

        while (result != NULL && result->value != key)
            result = result->son(key > result->value);

        if (result != NULL)
            this->splay(result);

        return result;
    }

    void remove(self::valueType key) {
        pointer current = find(key);

        if (current == NULL)
            exit(1);

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

            return -1;
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

            return -1;
        }

        for (current = current->rightSon; current->leftSon != NULL; current = current->leftSon);

        if (newNodeCreated)
            remove(key);

        this->splay(current);

        return current->value;
    }

    friend std::ostream &operator<<(std::ostream &output, const self &Object) {
        output << "TREE BEGIN\n";
        if (Object.root != NULL)
            cerr << Object.root;
        output << "TREE END\n";
        output << "==========\n";
        output << "DATA BEGIN\n";
        if (Object.root != NULL)
            outData(output, Object.root);
        output << "DATA END\n";
        return output;
    }
} tree;

int main() {
    int n;
    cin >> n;
    while (n--) {
        int opt, x;
        cin >> opt >> x;

        if (opt == 1)
            tree.insert(x);
        else if (opt == 2)
            tree.remove(x);
        else if (opt == 3)
            cout << tree.rank(x) << '\n';
        else if (opt == 4)
            cout << tree.kth(x) << '\n';
        else if (opt == 5)
            cout << tree.pre(x) << '\n';
        else if (opt == 6)
            cout << tree.next(x) << '\n';
    }

    return 0;
}
