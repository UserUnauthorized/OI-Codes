//HZ - 37.10
#include<bits/stdc++.h>

#include <iostream>
#include <vector>

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

std::mt19937 getRand(22516);

struct NODE {
    typedef NODE self;
    typedef int valueType;
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

public:
    static const self::valueType preNotFoundValue = -1;
    static const self::valueType nextNotFoundValue = -1;
    static const self::valueType minValue = INT_MIN;
    static const self::valueType maxValue = INT_MAX;
    static const self::valueType minNotFoundValue = self::minValue;
    static const self::valueType maxNotFoundValue = self::maxValue;

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
};

constexpr int maxN = 5e5 + 5, maxK = maxN, maxS = 1e4 + 5;

enum LimitEnum : int {
    EMPTY = -1,
    EQUAL = 1,
    LOWER = 2,
    UPPER = 3
};

typedef std::pair<LimitEnum, int> LimitType;

typedef std::vector<LimitType> LimitSet;

int N_, K_, S_;
int const &N = N_, &K = K_, &S = S_;

int main() {
    std::cin >> N_ >> K_ >> S_;

    int const textLength = N, patternLength = K;

    std::vector<int> lastPos(S + 1, -1), text(textLength), pattern(patternLength);
    std::vector<LimitSet> limit(patternLength);

    for (int i = 0; i < textLength; ++i)
        std::cin >> text[i];

    for (int i = 0; i < patternLength; ++i)
        std::cin >> pattern[i];

    TREAP tree;

    tree.insert(pattern[0]);

    lastPos[pattern[0]] = 0;

    for (int i = 1; i < patternLength; ++i) {
        if (lastPos[pattern[i]] != -1) {
            limit[i].emplace_back(EQUAL, i - lastPos[pattern[i]]);
        } else {
            int tmp = 0;
            if ((tmp = tree.pre(pattern[i])) != TREAP::preNotFoundValue) {
                limit[i].emplace_back(UPPER, i - lastPos[tmp]);
            }

            if ((tmp = tree.next(pattern[i])) != TREAP::nextNotFoundValue) {
                limit[i].emplace_back(LOWER, i - lastPos[tmp]);
            }

        }

        lastPos[pattern[i]] = i;
        tree.insert(pattern[i]);
    }

    auto const checkText([&limit, &text](int i, int j) -> bool {
        for (auto const &iter: limit[j]) {
            if (iter.first == EQUAL && text[i] != text[i - iter.second]) return false;
            if (iter.first == LOWER && text[i] >= text[i - iter.second]) return false;
            if (iter.first == UPPER && text[i] <= text[i - iter.second]) return false;
        }

        return true;
    });

    auto const checkPattern([&limit, &pattern](int i, int j) -> bool {
        for (auto const &iter: limit[j]) {
            if (iter.first == EQUAL && pattern[i] != pattern[i - iter.second]) return false;
            if (iter.first == LOWER && pattern[i] >= pattern[i - iter.second]) return false;
            if (iter.first == UPPER && pattern[i] <= pattern[i - iter.second]) return false;
        }

        return true;
    });

    std::vector<int> prefix(patternLength);

    for (int i = 1; i < patternLength; ++i) {
        int j = prefix[i - 1];

        while (j > 0 && !checkPattern(i, j))
            j = prefix[j - 1];

        if (checkPattern(i, j))
            ++j;

        prefix[i] = j;
    }

    std::queue<int> ans;

    int j = 0;

    for (int i = 0; i < textLength; ++i) {
        while (j > 0 && !checkText(i, j))
            j = prefix[j - 1];

        if (checkText(i, j))
            ++j;

        if (j == patternLength) {
            ans.push(i - patternLength + 1 + 1);
            j = prefix[j - 1];
        }
    }

    std::cout << ans.size() << '\n';

    while (!ans.empty()) {
        std::cout << ans.front() << '\n';
        ans.pop();
    }

    std::cout << std::flush;

    return 0;
}
