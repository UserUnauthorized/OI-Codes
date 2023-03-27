//Luogu - P3369[FHQ Treap]
#include<bits/stdc++.h>

constexpr unsigned int seed = 22516;
std::mt19937 getRand(seed);
	
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

    NODE() : leftSon(NULL), rightSon(NULL), priority(0), value(0), count(0), size(0) {};

    void init() {
        this->leftSon = this->rightSon = nullptr;
        this->priority = ::getRand();
        this->value = 0;
        this->count = this->size = 1;
    }
    
    void init(valueType key) {
        this->leftSon = this->rightSon = nullptr;
        this->priority = ::getRand();
        this->value = key;
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
    typedef FHQ self;
    typedef node::valueType valueType;
    
private:
    static const self::valueType preNotFoundValue = -1;
    static const self::valueType nextNotFoundValue = -1;
    static const self::valueType minValue = INT_MIN;
    static const self::valueType maxValue = INT_MAX;
    static const self::valueType minNotFoundValue = self::minValue;
    static const self::valueType maxNotFoundValue = self::maxValue;
    
    pointer newNode() {
//        return (pointer) malloc(sizeof(NODE));
		return new NODE;
    }
    
    void delNode(pointer &p) {
//        free(p);
        p = nullptr;
    }
    
public:
    pointer root;

    FHQ() : root(NULL) {};
    
    std::pair<pointer, pointer> split(pointer current, valueType key) {
    	if(current == nullptr)
    		return std::make_pair(nullptr, nullptr);
    	
    	if(current->value <= key) {
    		auto const temp = this->split(current->rightSon, key);
    		
    		current->rightSon = temp.first;
    		
    		current->update();
    		
    		return std::make_pair(current, temp.second);
		} else {
			auto const temp = this->split(current->rightSon, key);
    		
    		current->leftSon = temp.first;
    		
    		current->update();
    		
    		return std::make_pair(temp.first, current);
		}
	}
	
	std::tuple<pointer, pointer, pointer> splitByRank(pointer current, valueType rank) {
		if(current == nullptr)
			return std::make_tuple(nullptr, nullptr, nullptr);
			
		valueType const leftSize = current->leftSon == nullptr ? 0 : current->leftSon->size;
		
		if(rank <= leftSize){
			pointer left, mid, right;
			
			std::tie(left, mid, right) = this->splitByRank(current->leftSon, rank);
			
			current->leftSon = right;
			
			current->update();
			
			return std::make_tuple(left, mid, current);
		} else if(rank <= leftSize + current->count) {
			pointer left = current->leftSon;
			pointer right = current->rightSon;
			
			current->leftSon = current->rightSon = nullptr;
			
			return std::make_tuple(left, current, right);
		} else {
			pointer left, mid, right;
			
			std::tie(left, mid, right) = this->splitByRank(current->rightSon, rank - leftSize - current->count);
			
			current->rightSon = left;
			
			return std::make_tuple(current, mid, right);
		}
	}
	
	pointer merge(pointer left, pointer right){
		if(left == nullptr && right == nullptr) return nullptr;
		if(right == nullptr) return left;
		if(left == nullptr) return right;
		
		if(left->priority < right->priority) {
			left->rightSon = this->merge(left->rightSon, right);
			
			left->update();
			
			return left;
		} else {
			right->leftSon = this->merge(left, right->leftSon);
			
			right->update();
			
			return right;
		}
	}
	
	void insert(valueType key){
		auto const temp = this->split(this->root, key);
		
		auto left = this->split(temp.first, key - 1);
		
		if(left.second == nullptr){
			left.second = this->newNode();
			left.second->init(key);
		} else {
			++left.second->count;
			left.second->update();
		}
		
		pointer leftCombined = this->merge(left.first, left.second);
		
		this->root = this->merge(leftCombined, temp.second);
	}
	
	void remove(valueType key) {
		auto temp = this->split(this->root, key);
		
		auto left = this->split(temp.first, key - 1);
		
		if(left.second->count > 1){
			--left.second->count;
			left.second->update();
			left.first = this->merge(left.first, left.second);
		} else {
//			if (temp.first == left.second){
//				temp.first = nullptr;
//			}
			/* TAG */
			
			this->delNode(left.second);
		}
		
		this->root = this->merge(left.first, temp.second);
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
} tree;

int main() {
    int n;
    std::cin >> n;
    while (n--) {
        int opt, x;
        std::cin >> opt >> x;

        if (opt == 1)
            tree.insert(x);
        else if (opt == 2)
            tree.remove(x);
        else if (opt == 3)
            std::cout << tree.rank(x) << '\n';
        else if (opt == 4)
            std::cout << tree.kth(x) << '\n';
        else if (opt == 5)
            std::cout << tree.pre(x) << '\n';
        else if (opt == 6)
            std::cout << tree.next(x) << '\n';
    }

    return 0;
}
