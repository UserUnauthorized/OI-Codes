//HZ - 42.4
//Luogu - P3369
#include<bits/stdc++.h>
using namespace std;

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

typedef long long valueType;
constexpr valueType maxN = 1e5 + 5;

struct NODE{
	typedef NODE self;
	typedef self* pointer;
	typedef self& reference;

	pointer father;
	pointer leftSon;
	pointer rightSon;
	valueType value;
	valueType count;
	valueType size;
	
	NODE():father(NULL), leftSon(NULL), rightSon(NULL), value(0), count(0), size(0){};
	
	pointer &son(bool _rightSon_){
		return _rightSon_ ? this->rightSon : this->leftSon;
	}
	
	bool isRightSon() const {
		return this == (this->father)->rightSon;
	}
	
	void update(){
		this->size = (this->leftSon != NULL ? (this->leftSon)->size : 0) + (this->rightSon != NULL ? (this->rightSon)->size : 0) + this->count;
	}
	
	void init(){
		this->leftSon = this->rightSon = this->father = NULL;
		this->value = 0;
		this->count = this->size = 1;
	}
	
	void clear(){
		this->leftSon = this->rightSon = this->father = NULL;
		this->value = this->count = this->size = 0;
	}
};

class SPLAY{
public:
	typedef NODE node;
	typedef node::pointer pointer;

private:
	pointer newNode(){
		return (pointer)malloc(sizeof(NODE));
	}
	
	void delNode(pointer &p){
		free(p);
		p = NULL;
	}

public:
	pointer root;
	
	SPLAY(): root(NULL){};
	
	void rotate(const pointer &now){
		pointer father = now->father;
		bool isRightSon = now->isRightSon();
		father->son(isRightSon) = now->son(!isRightSon);
		
		if(now->son(!isRightSon) != NULL){
			debug(isRightSon, now->son(!isRightSon)->father->value);
			(now->son(!isRightSon))->father = father;
			debug(now->son(!isRightSon)->father->value);
		}
			
			
		if((now->father = father->father))
			(now->father)->son(father->isRightSon()) = now;
			
		father->father = now;
		now->son(!isRightSon) = father;
		father->update();
		now->update();
		
		if(now->father == NULL)
			this->root = now;
	}
	
	void splay(const pointer &now){
		for(pointer father = now->father; (father = now->father) != NULL; rotate(now))
			if(father->father != NULL)
				rotate(now->isRightSon() == father->isRightSon() ? father : now);
	}
	
	void insert(int key){
		if(this->root == NULL){
			this->root = this->newNode();
			this->root->init();
			this->root->value = key;
			return;
		}
		
		pointer now(this->root), father(NULL);
		
		for(;; father = now, now = now->son(key > now->value)){
			if(now == NULL){
				now = newNode();
				now->init();
				now->father = father;
				now->value = key;
				father->son(key > father->value) = now;
				this->splay(now);
				return;
			}
			
			if(now->value == key){
				++now->count;
				this->splay(now);
				return;
			}
		}
	}
	
	pointer find(int key){
		pointer result = this->root;
		
		while(result != NULL && result->value != key)
			result = result->son(key > result->value);
		
		if(result != NULL)
			this->splay(result);
			
		return result;
	}
	
	void remove(int key){
		pointer current = find(key);
		
		if(current == NULL)
			exit(1);
			
		this->splay(current);
		
		current = this->root;
		
		if(current->count > 1){
			--current->count;
			current->update();
			return;
		}
		
		if(current->leftSon == NULL && current->rightSon == NULL){
			this->delNode(current);
			this->root = NULL;
			return;
		}
		
		if(current->leftSon == NULL){
			this->root = current->rightSon;
			this->root->father = NULL;
			delNode(current);
			return;
		}
		
		if(current->rightSon == NULL){
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
	
	int rank(int key){
		pointer current = find(key);
		bool newNodeCreated = false;
		
		if(current == NULL){
			insert(key);
			newNodeCreated = true;
		}
		
		int result = 1;
		
		if(root->leftSon != NULL)
			result += (root->leftSon)->size;
			
		if(newNodeCreated)
			remove(key);
		else
			this->splay(current);
			
		return result;
	}
	
	int kth(int key){
		pointer current = this->root;
		
		while(true){
			if(current->leftSon != NULL && key <= (current->leftSon)->size){
				current = current->leftSon;
				continue;
			}
			
			if(current->leftSon != NULL)
				key -= (current->leftSon)->size;
			
			key -= current->size;
			
			if(key <= 0){
				debug(current->value, key);
				this->splay(current);
				debug(current->value);
				return current->value;
			}
			
			current = current->rightSon;
		}
	}
	
	int pre(int key){
		pointer current = this->find(key);
		bool newNodeCreated = false;
		
		if(current == NULL){
			insert(key);
			current = this->root;
			newNodeCreated = true;
		}
		
		if(current->leftSon == NULL){
			if(newNodeCreated)
				remove(key);
			
			return -1;
		}
		
		for(current = current->leftSon; current->rightSon != NULL; current = current->rightSon);
		
		if(newNodeCreated)
			remove(key);
				
		this->splay(current);
		
		return current->value;
	}
	
	int next(int key){
		pointer current = this->find(key);
		bool newNodeCreated = false;
		
		if(current == NULL){
			insert(key);
			current = this->root;
			newNodeCreated = true;
		}
		
		if(current->rightSon == NULL){
			if(newNodeCreated)
				remove(key);
			
			return -1;
		}
		
		for(current = current->rightSon; current->leftSon != NULL; current = current->leftSon);
		
		if(newNodeCreated)
				remove(key);
				
		this->splay(current);		
		
		return current->value;
	}
} tree;

int main(){
	freopen("input2.in", "r", stdin);
	freopen("input2.ans", "w", stdout);
	freopen("input2.err", "w", stderr);
	int n;
	cin >> n;
	while(n--){
		int opt, x;
		cin >> opt >> x;
		
		if(opt == 1)
			tree.insert(x);
		else if(opt == 2)
			tree.remove(x);
		else if(opt == 3)
			cout << tree.rank(x) << '\n';
		else if(opt == 4)
			cout << tree.kth(x) << '\n';
		else if(opt == 5)
			cout << tree.pre(x) << '\n';
		else if(opt == 6)
			cout << tree.next(x) << '\n';
	}
	
	return 0;
}
