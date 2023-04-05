//HZ - 44.9
#include<bits/stdc++.h>

typedef int valueType;
typedef unsigned int posType;
constexpr int maxN = 5e4 + 5;

posType L_, R_;
posType const &L = L_, &R = R_;

namespace TREE {
    typedef ::posType pointer;

    constexpr pointer null = 0;

    posType const &L = ::L, &R = ::R;

    class NEWNODE {
    private:
        pointer _count_;

    public:
        pointer operator()() {
            return ++this->_count_;
        }

        void init() {
            this->_count_ = 0;
        }
    } newNode;

    struct SEGNODE {
        pointer leftSon;
        pointer rightSon;
        valueType count;

        SEGNODE() : leftSon(null), rightSon(null), count(0) {};

        void update();
    };

    std::array<SEGNODE, maxN * 60> node;

    void SEGNODE::update() {
        this->count = node[this->leftSon].count + node[this->rightSon].count;
    }

    class TREE {
    private:
        pointer root;

    public:
        void init() {
            this->root = null;
        }

        void insert(posType pos, valueType key) {
            this->insert(this->root, L, R, pos, key);
        }

        valueType

    private:
        void insert(pointer &current, posType nodeL, posType nodeR, posType pos, valueType key) {
            if (current == null)
                current = newNode();

            if (nodeL == nodeR) {
                node[current].count += key;
                return;
            }

            posType const mid = (nodeL + nodeR) >> 1;

            if (pos <= mid)
                this->insert(node[current].leftSon, nodeL, mid, pos);
            else
                this->insert(node[current].rightSon, mid + 1, nodeR, pos);
        }
    };

    void init() {
        node.fill(SEGNODE());
    }

}
