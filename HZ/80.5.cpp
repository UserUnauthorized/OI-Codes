//HZ - 80.5

#include <bits/stdc++.h>

class LCT {
public:
    struct NODE {
        typedef NODE self;
//        typedef std::shared_ptr<self> pointer;
        typedef self *pointer;
        typedef unsigned int posType;
        typedef int valueType;

        constexpr static const valueType MAX = INT_MAX;

        pointer father;
        pointer leftSon;
        pointer rightSon;

        bool tag;
        valueType value;
        valueType size;
        valueType min;

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
            this->min = std::min({(this->leftSon != nullptr ? (this->leftSon)->min : MAX),
                        (this->rightSon != nullptr ? (this->rightSon)->min : MAX), this->value});
        }

        NODE() : father(nullptr), leftSon(nullptr), rightSon(nullptr), tag(false), value(0), size(0), min(0),
                 nodeId(0) {};

        NODE(valueType key, posType id) : father(nullptr), leftSon(nullptr), rightSon(nullptr), tag(false), value(key),
                                          size(1), min(key), nodeId(id) {};

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
            output << Object->value << ' ' << Object->min << ' ';
            output << "leftSon:" << (Object->leftSon != nullptr ? Object->leftSon->nodeId : 0) << "\trightSon:"
                   << (Object->rightSon != nullptr ? Object->rightSon->nodeId : 0) << "\tfather:"
                   << (Object->father != nullptr ? Object->father->nodeId : 0) << std::endl << std::endl << std::endl;

            return output;
        }
    };

    typedef NODE::pointer pointer;

    typedef NODE::posType posType;

    typedef NODE::valueType valueType;

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
        return this->split(node[x], node[y])->min;
    }

    posType find(posType x) {
        return this->find(node[x]);
    }
    
    bool check(posType x, posType y) {
    	return find(x) == find(y);
	}

protected:
    static void rotate(const pointer &current) {
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

//        if (this->find(y) == x->nodeId)
//            throw AlreadyConnectedException("Already Connected");

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

//        if (this->find(y->nodeId) != x->nodeId)
//            throw NoSuchEdgeException("Disconnected");

//        this->splay(y);

//        if (y->leftSon != x || x->rightSon != nullptr)
//            throw NoSuchEdgeException("There are other edges between the nodes.");

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

class PersistentSegmentTree {
public:
    typedef int valueType;
    typedef unsigned int sizeType;
    typedef PersistentSegmentTree self;

private:
    struct NODE {
        typedef NODE self;
//        typedef std::shared_ptr<self> pointer;
        typedef self *pointer;
        typedef PersistentSegmentTree::valueType valueType;

        pointer leftSon, rightSon;
        self::valueType count;

        NODE() : leftSon(nullptr), rightSon(nullptr), count(0) {};


        void update() {
            this->count = 0;

            if (this->leftSon != nullptr)
                this->count += this->leftSon->count;

            if (this->rightSon != nullptr)
                this->count += this->rightSon->count;
        }
    };

    typedef NODE::pointer pointer;

    static pointer allocateNode() {
//        return std::make_shared<NODE>();
        return new NODE();
    }


protected:
    pointer root;

    sizeType L, R;

public:

    PersistentSegmentTree() : root(nullptr), L(0), R(0) {};

    PersistentSegmentTree(sizeType _l_, sizeType _r_) : root(nullptr), L(_l_), R(_r_) {};

    PersistentSegmentTree(pointer _root_, sizeType _l_, sizeType _r_) : root(_root_), L(_l_), R(_r_) {};

    void build() {
        build(this->root, L, R);
    }

    self insert(sizeType pos) {
        return {insert(this->root, L, R, pos), L, R};
    }

    friend valueType query(sizeType l, sizeType r);

    static valueType
    query(const pointer &leftNode, const pointer &rightNode, sizeType nodeL, sizeType nodeR, sizeType l, sizeType r) {
        if (leftNode->count == rightNode->count)
            return 0;

        if (l <= nodeL && nodeR <= r)
            return rightNode->count - leftNode->count;

        sizeType const mid = (nodeL + nodeR) >> 1;

        if (r <= mid)
            return query(leftNode->leftSon, rightNode->leftSon, nodeL, mid, l, r);
        else if (l > mid)
            return query(leftNode->rightSon, rightNode->rightSon, mid + 1, nodeR, l, r);
        else
            return query(leftNode->leftSon, rightNode->leftSon, nodeL, mid, l, r) +
                   query(leftNode->rightSon, rightNode->rightSon, mid + 1, nodeR, l, r);
    }

protected:
    static void build(pointer &current, sizeType l, sizeType r) {
        current = allocateNode();

        if (l == r)
            return;

        sizeType const mid = (l + r) >> 1;

        build(current->leftSon, l, mid);
        build(current->rightSon, mid + 1, r);
    }

    static pointer insert(const pointer &current, sizeType nodeL, sizeType nodeR, sizeType pos) {
        pointer result = allocateNode();
        *result = *current;

        if (nodeL == nodeR) {
            ++result->count;
            return result;
        }

        sizeType const mid = (nodeL + nodeR) >> 1;

        if (pos <= mid)
            result->leftSon = insert(current->leftSon, nodeL, mid, pos);
        else
            result->rightSon = insert(current->rightSon, mid + 1, nodeR, pos);

        result->update();

        return result;
    }
};
typedef PersistentSegmentTree TREE;

typedef int valueType;
constexpr valueType MAX = INT_MAX >> 1;
constexpr valueType maxN = 2e5 + 5;

typedef std::array<valueType, maxN> ARRAY;
typedef std::array<TREE, maxN> TreeArray;

valueType query(PersistentSegmentTree::sizeType l, PersistentSegmentTree::sizeType r);

valueType N_, M_, Q_, type_;
valueType const &N = N_, &M = M_, &Q = Q_, &type = type_;

TreeArray tree;
std::array<std::pair<int, int>, maxN> connection;

valueType read();

int main() {
//    std::ios::sync_with_stdio(false);

//    std::cin >> N_ >> M_ >> Q_ >> type_;
	N_ = read();
	M_ = read();
	Q_ = read();
	type_ = read();
	
	LCT lct(N + M);
	
	for(int i = 1; i <= N; ++i)
		lct.set(i, MAX);
		
	for(int i = 1; i <= M; ++i)
		lct.set(N + i, i);

	
	tree[0] = TREE(0, M);
	tree[0].build();
	
	for(int i = 1; i <= M; ++i) {
//		int a, b;
//		std::cin >> a >> b;
		int a = read(), b = read();
		
		connection[i] = std::make_pair(a, b);
		
		if(a == b) {
			tree[i] = tree[i - 1];
		}else if(!lct.check(a, b)) {
			tree[i] = tree[i - 1].insert(0);
			
			lct.link(a, N + i);
			lct.link(b, N + i);
		} else {
			int const edge = lct.ans(a, b);
			
			lct.cut(connection[edge].first, N + edge);
			lct.cut(connection[edge].second, N + edge);
			
			lct.link(a, N + i);
			lct.link(b, N + i);
			
			tree[i] = tree[i - 1].insert(edge);
//			last[edge] = i;
		}
	}
	
	valueType lastAns = 0;
	
	for(int i = 1; i <= Q; ++i) {
//		valueType l, r;
//		std::cin >> l >> r;
		valueType l = read(), r = read();
		
		if(type == 1) {
			l ^= lastAns;
			r ^= lastAns;
		}
		
		std::cout << (lastAns = N - query(l, r)) << '\n';
	}
	
//	std::cout << std::flush;
	
    return 0;
}

valueType query(TREE::sizeType l, TREE::sizeType r) {
//	if(l > r)
//		std::swap(l, r);
	
	return TREE::query(tree[l - 1].root, tree[r].root, 0, M, 0, l - 1);
}

valueType read() {
	valueType result = 0;
	int input = getchar();
	
	while(input < '0' || input > '9')
		input = getchar();
		
	while(input >= '0' && input <= '9') {
		result = (result << 3) + (result << 1) + (input & 15);
		input = getchar();
	}
	
	return result;
}
