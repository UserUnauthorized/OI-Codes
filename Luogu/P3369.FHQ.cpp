//Luogu - P3369[FHQ Treap]
#include<bits/stdc++.h>

constexpr unsigned int seed = 22516;
mt19937 getRand(seed);
	
struct NODE {
    typedef NODE self;
    typedef long long valueType;
    typedef self *pointer;
    typedef unsigned int randType;

    pointer leftSon;
    pointer rightSon;
    randType priority;

    self::valueType value;
    self::valueType count;
    self::valueType size;

    NODE() : leftSon(NULL), rightSon(NULL), father(NULL), priority(0), value(0), count(0), size(0) {};

    void init() {
        this->leftSon = this->rightSon = nullptr;
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

class FHQ{
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
    
    void delNode(pointer &p) {
//        free(p);
        p = nullptr;
    }
    
public:
    pointer root;

    TREAP() : root(NULL) {};
    
    
};
