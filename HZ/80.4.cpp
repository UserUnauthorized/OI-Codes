//HZ - 80.3
//Luogu - P1501
#include<bits/stdc++.h>

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
        if(V < 0){
        	os << '-';
        	V = -V;
		}
		
		if(V > 9)	
			os << V / 10;
		
		os << (int)(V % 10);
		
        return os;
    }

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

constexpr int maxN = 1005, maxM = 1e5;
typedef int valueType;

class LCT {
public:
	struct NODE {
		typedef NODE self;
		typedef self* pointer;
		typedef unsigned int posType;
		
		pointer father;
		pointer leftSon;
		pointer rightSon;
		
		bool tag;
		valueType value;
		valueType size;
		valueType add;
		valueType mul;
		valueType sum;
		
		posType nodeId;
		
		pointer &son(bool _rightSon_){
			return _rightSon_ ? this->rightSon : this->leftSon;
		}
	
		bool isRightSon() const {
			return this == (this->father)->rightSon;
		}
		
		void update(){
			this->size = (this->leftSon != nullptr ? (this->leftSon)->size : 0) + (this->rightSon != nullptr ? (this->rightSon)->size : 0) + 1;
			this->sum = (this->leftSon != nullptr ? (this->leftSon)->sum : 0) + (this->rightSon != nullptr ? (this->rightSon)->sum : 0) + this->value;
			this->sum %= MOD;
		}
		
		void init(){
			this->leftSon = this->rightSon = this->father = nullptr;
			this->value = 0;
			this->size = 1;
			this->tag = false;
			this->add = this->sum = 0;
			this->mul = 1;
		}
		
		void init(valueType key) {
			this->leftSon = this->rightSon = this->father = nullptr;
			this->value = key;
			this->size = 1;
			this->tag = false;
			this->add = this->sum = 0;
			this->mul = 1;
		}
		
		void init(valueType key, posType id) {
			this->leftSon = this->rightSon = this->father = nullptr;
			this->value = key;
			this->size = 1;
			this->nodeId = id;
			this->tag = false;
			this->add = this->sum = 0;
			this->mul = 1;
		}
		
		bool isRoot() {
			return this->father == nullptr || (this->father->leftSon != this && this->father->rightSon != this);
		}
		
		void push() {
			if(this->tag) {
				if(this->leftSon != nullptr) {
					std::swap(this->leftSon->leftSon, this->leftSon->rightSon);
					this->leftSon->tag = !this->leftSon->tag;
				}
				
				if(this->rightSon != nullptr) {
					std::swap(this->rightSon->leftSon, this->rightSon->rightSon);
					this->rightSon->tag = !this->rightSon->tag;
				}
				
				this->tag = false;
			}
			
			if(this->mul != 1) {
				if(this->leftSon != nullptr) {
					this->leftSon->mul = (this->leftSon->mul * this->mul) % MOD;
					this->leftSon->value = (this->leftSon->value * this->mul) % MOD;
					this->leftSon->sum = (this->leftSon->sum * this->mul) % MOD;
					this->leftSon->add = (this->leftSon->add * this->mul) % MOD;
				}
				
				if(this->rightSon != nullptr) {
					this->rightSon->mul = (this->rightSon->mul * this->mul) % MOD;
					this->rightSon->value = (this->rightSon->value * this->mul) % MOD;
					this->rightSon->sum = (this->rightSon->sum * this->mul) % MOD;
					this->rightSon->add = (this->rightSon->add * this->mul) % MOD;
				}
				
				this->mul = 1;
			}
			
			if(this->add != 0) {
				if(this->leftSon != nullptr) {
					this->leftSon->value = (this->leftSon->value + this->add) % MOD;
					this->leftSon->sum = (this->leftSon->sum + this->add * this->leftSon->size) % MOD;
					this->leftSon->add = (this->leftSon->add + this->add) % MOD;
				}
				
				if(this->rightSon != nullptr) {
					this->rightSon->value = (this->rightSon->value + this->add) % MOD;
					this->rightSon->sum = (this->rightSon->sum + this->add * this->rightSon->size) % MOD;
					this->rightSon->add = (this->rightSon->add + this->add) % MOD;
				}
				
				this->add = 0;
			}
		}
		
		friend std::ostream &operator<<(std::ostream &output, pointer Object) {
			if(Object == nullptr)
				return output;
			
			output << "nodeId:" << Object->nodeId;
        	output << "\tisRoot:" << Object->isRoot() << std::endl;
        	output << Object->value << ' ' << Object->sum << ' ';
        	output << "leftSon:" << (Object->leftSon != nullptr ? Object->leftSon->nodeId : 0) << "\trightSon:" << (Object->rightSon != nullptr ? Object->rightSon->nodeId : 0) << "\tfather:" << (Object->father != nullptr ? Object->father->nodeId : 0) << std::endl << std::endl << std::endl;
        	
        	return output;
    	}
	}; 

	typedef NODE::pointer pointer;
	
	typedef NODE::posType posType;

protected:
	size_t _size_;
	
	std::vector<pointer> node;

public:
	LCT():_size_(0){};
	
	LCT(size_t size):_size_(size), node(_size_ + 1){
		node[0] = this->newNode();
		node[0]->init();
	};

private:
	pointer newNode(){
		return (pointer)malloc(sizeof(NODE));
	}

public:
	void set(posType x, valueType key) {
		if(node[x] == nullptr) {
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
		return this->split(node[x], node[y])->sum % MOD;
	}
	
	void add(posType x, posType y, valueType key) {
		pointer current = this->split(node[x], node[y]);
		current->value = (current->value + key) % MOD;
		current->add = (current->add + key) % MOD;
		current->sum = (current->sum + key * current->size) % MOD;
		current->update();
	}
	
	void mul(posType x, posType y, valueType key) {
		pointer current = this->split(node[x], node[y]);
		current->value = (current->value * key) % MOD;
		current->mul = (current->mul * key) % MOD;
		current->sum = (current->sum * key) % MOD;
		current->update();
	}
	
	posType find(posType x) {
		return this->find(node[x]);
	}
	
protected:
	void rotate(pointer current) {
		pointer father = current->father;
		bool const isRightSon = current->isRightSon();
		
		father->son(isRightSon) = current->son(!isRightSon);
		
		if(current->son(!isRightSon) != nullptr) {
			(current->son(!isRightSon))->father = father;
		}
		
		if((current->father = father->father) != nullptr && !father->isRoot())
			(current->father)->son(father->isRightSon()) = current;
			
		father->father = current;
		current->son(!isRightSon) = father;
		father->update();
		current->update();
	}
	
	void splay(pointer current) {
		update(current);

		for(pointer father = current->father; !current->isRoot(); rotate(current))
			if(!(father = current->father)->isRoot())
				rotate(current->isRightSon() == father->isRightSon() ? father : current);
	}
	
	void update(pointer current) {
		if(!current->isRoot())
			update(current->father);
		
		current->push();
	}
	
	posType access(pointer current) {

		pointer pre = nullptr;
		
		for(pre = nullptr; current != nullptr; pre = current, current = current->father) {
			this->splay(current);

			current->rightSon = pre;
			
			current->update();
		}
		
		return pre == nullptr ? 0 : pre->nodeId;
	}
	
	void makeRoot(pointer current) {
		posType const p = this->access(current);

		if(p == 0)
			return;
		
		current = node[p];

		std::swap(current->leftSon, current->rightSon);

		current->tag = !current->tag;
	}
	
	void link(pointer x, pointer y) {
		this->makeRoot(x);

		this->splay(x);
		
		if(this->find(y) == x->nodeId)
			return;

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
		
		if(this->find(y->nodeId) != x->nodeId)
			return;
			
		this->splay(y);
		
		if(y->leftSon == x && x->rightSon == nullptr)
			
		y->leftSon = x->father = nullptr;
			
		y->update();
	}
	
	posType find(pointer current) {
		this->access(current);
		
		this->splay(current);
		
		current->push();

		while(current->leftSon != nullptr) {
			current = current->leftSon;
			
			current->push();
		}
		
		this->splay(current);
		
		return current->nodeId;
	}

public:
	void out() {
		for(size_t i = 1; i <= _size_; ++i)
			std::cerr << node[i];
	}
};

int N_, M_, Q_;
int const &N = N_, &M = M_, &Q = Q_;

int main() {
	std::cin >> N_ >> M_ >> Q_;;
	
	LCT tree(n);
	
	for(int i = 1; i <= n; ++i) {
		tree.set(i, 0);
	}
	
	for(int i = 1; i < n; ++i) {
		LCT::posType a, b;
		
		std::cin >> a >> b;
		
		tree.link(a, b);
	}

	for(int i = 0; i < m; ++i) {
		char op;
		
		std::cin >> op;
		
		if(op == '+') {
			LCT::posType x, y;
			valueType c;
			
			std::cin >> x >> y >> c;

			tree.add(x, y, c);
		} else if(op == '-') {
			LCT::posType x, y, a, b;
			
			std::cin >> x >> y >> a >> b;

			tree.cut(x, y);
			
			tree.link(a, b);
		} else if(op == '*') {
			LCT::posType x, y;
			valueType c;
			
			std::cin >> x >> y >> c;
			
			tree.mul(x, y, c);
		} else if(op == '/') {
			LCT::posType x, y;
			
			std::cin >> x >> y;

			std::cout << tree.ans(x, y) << '\n';
		}
	}
	
	return 0;
}
