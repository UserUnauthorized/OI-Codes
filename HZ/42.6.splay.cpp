//HZ - 42.6 [Splay]
//Luogu - P3380 [Splay]
//LOJ - 106 [Splay]
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

typedef int valueType;
constexpr valueType maxN = 5e4 + 5;
valueType minSource(INT_MAX), maxSource(INT_MIN);
typedef array<valueType, maxN> container;
#ifndef OI_CODES_SPLAY_H
#define OI_CODES_SPLAY_H

#include<iostream>

struct NODE{
	typedef NODE self;
	typedef self* pointer;
	typedef self& reference;
	typedef long long valueType;

	pointer father;
	pointer leftSon;
	pointer rightSon;
	self::valueType value;
	self::valueType count;
	self::valueType size;
	
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
	
	friend std::ostream &operator<<(std::ostream &output, const self &Object) {
        if(Object.leftSon != NULL){
        	output << Object.value << ' ' << Object.leftSon->value << ' ' << 0 << std::endl;
        	output << *(Object.leftSon);
		}
        
        if(Object.rightSon != NULL){
        	output << Object.value << ' ' << Object.rightSon->value << ' ' << 1 << std::endl;
        	output << *(Object.rightSon);
		}
        return output;
    }
    
    friend std::ostream &operator<<(std::ostream &output, pointer Object) {
        output << *Object;
        return output;
    }
    
    friend void outData(std::ostream &output, pointer Object){
    	if(Object == NULL)
    		return;
    		
    	output << Object->value << ' ' << Object->count << ' ' << Object->size << std::endl;
    	
    	if(Object->leftSon != NULL)
    		outData(output, Object->leftSon);
    	
    	if(Object->rightSon != NULL)
    		outData(output, Object->rightSon);
	}
};

class SPLAY{
public:
	typedef NODE node;
	typedef node::pointer pointer;
	typedef SPLAY self;
	typedef node::valueType valueType;

private:
	static const self::valueType preNotFoundValue = -2147483647;
	static const self::valueType nextNotFoundValue = 2147483647;
	static const self::valueType minNotFoundValue = -2147483647;
	static const self::valueType maxNotFoundValue = 2147483647;
	
	pointer newNode(){
//		return new node();
		return (pointer)malloc(sizeof(node));
	}
	
	void delNode(pointer &p){
		free(p);
		p = NULL;
	}

public:
	pointer root;
	
	SPLAY(): root(NULL){};
	
	void rotate(const pointer &current){
		pointer father = current->father;
		bool isRightSon = current->isRightSon();
		father->son(isRightSon) = current->son(!isRightSon);
		
		if(current->son(!isRightSon) != NULL){
			(current->son(!isRightSon))->father = father;
		}
			
			
		if((current->father = father->father))
			(current->father)->son(father->isRightSon()) = current;
			
		father->father = current;
		current->son(!isRightSon) = father;
		father->update();
		current->update();
		
		if(current->father == NULL)
			this->root = current;
	}
	
	void splay(const pointer &current, pointer to = NULL){
		for(pointer father = current->father; (father = current->father) != to; rotate(current))
			if(father->father != to)
				rotate(current->isRightSon() == father->isRightSon() ? father : current);
	}
	
	void insert(self::valueType key){
		if(this->root == NULL){
			this->root = this->newNode();
			this->root->init();
			this->root->value = key;
			return;
		}
		
		pointer current(this->root), father(NULL);

		for(;; father = current, current = current->son(key > current->value)){
			if(current == NULL){
				current = this->newNode();
				current->init();
				current->father = father;
				current->value = key;
				father->son(key > father->value) = current;
				this->splay(current);
				return;
			}
			
			if(current->value == key){
				++current->count;
				this->splay(current);
				return;
			}
		}
	}
	
	pointer find(self::valueType key){
		pointer result = this->root;
		
		while(result != NULL && result->value != key)
			result = result->son(key > result->value);
		
		if(result != NULL)
			this->splay(result);
			
		return result;
	}
	
	void remove(self::valueType key){
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
	
	self::valueType rank(self::valueType key){
//		pointer current = find(key);
		pointer current = NULL;
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
	
	self::valueType kth(self::valueType key){
		pointer current = this->root;
		
		while(true){
			if(current->leftSon != NULL && key <= (current->leftSon)->size){
				current = current->leftSon;
				continue;
			}
			
			if(current->leftSon != NULL)
				key -= (current->leftSon)->size;
			
			key -= current->count;
			
			if(key <= 0){
				this->splay(current);
				return current->value;
			}
			
			current = current->rightSon;
		}
	}
	
	self::valueType pre(self::valueType key){
//		pointer current = this->find(key);
		pointer current = NULL;
		bool newNodeCreated = false;
		
		if(current == NULL){
			insert(key);
			current = this->root;
			newNodeCreated = true;
		}
		
		if(current->leftSon == NULL){
			if(newNodeCreated)
				remove(key);
			
			return this->preNotFoundValue;
		}
		
		for(current = current->leftSon; current->rightSon != NULL; current = current->rightSon);
		
		if(newNodeCreated)
			remove(key);
				
		this->splay(current);
		
		return current->value;
	}
	
	self::valueType next(self::valueType key){
//		pointer current = this->find(key);
		pointer current = NULL;
		bool newNodeCreated = false;
		
		if(current == NULL){
			insert(key);
			current = this->root;
			newNodeCreated = true;
		}
		
		if(current->rightSon == NULL){
			if(newNodeCreated)
				remove(key);
			
			return this->nextNotFoundValue;
		}
		
		for(current = current->rightSon; current->leftSon != NULL; current = current->leftSon);
		
		if(newNodeCreated)
				remove(key);
				
		this->splay(current);		
		
		return current->value;
	}
	
	bool empty()const{
		return this->root == NULL;
	}
	
	self::valueType min(){
		if(this->empty())
			return this->minNotFoundValue;
		
		pointer current = this->root;
		
		while(current->leftSon != NULL)
			current = current->leftSon;
		
		this->splay(current);
		return current->value;
	}
	
	self::valueType max(){
		if(this->empty())
			return this->maxNotFoundValue;
			
		pointer current = this->root;
		
		while(current->rightSon != NULL)
			current = current->rightSon;
		
		this->splay(current);
		return current->value;
	}
	
	self::valueType size()const{
		if(this->empty())
			return 0;
			
		return this->root->size;
	}

public:
    friend std::ostream &operator<<(std::ostream &output, const self &Object) {
    	output << "TREE BEGIN" << std::endl;
        if(Object.root != NULL)
        	output << Object.root;
        output << "TREE END" << std::endl;
        output << "==========" << std::endl;
        output << "DATA BEGIN" << std::endl;
        if(Object.root != NULL)
        	outData(output, Object.root);
        output << "DATA END" << std::endl;
        return output;
    }
};

#endif //OI_CODES_SPLAY_H

struct SEGNODE{
	typedef SEGNODE self;
	typedef self* selfPointer;
	typedef SPLAY splay;
	typedef splay* pointer;
	typedef ::valueType valueType;
	typedef ::container container;
	
	pointer data;
	self::valueType leftBound, rightBound;
	selfPointer leftSon, rightSon;
	
	SEGNODE():data(NULL), leftBound(-1), rightBound(-1), leftSon(NULL), rightSon(NULL){};
	
	void init(self::valueType l, self::valueType r, const container &source){
		this->data = new splay();

		this->leftBound = l;
		this->rightBound = r;

		for(int i = l; i <= r; ++i){
			this->data->insert(source[i]);
		}
	}
};

class TREE{
public:
	typedef TREE self;
	typedef ::valueType valueType;
	typedef SEGNODE Node;
	typedef Node* pointer;
	typedef ::container container;
	
private:
	pointer newNode(){
//		return new Node();
//		return (pointer)malloc(sizeof(Node));
		static Node pool[maxN << 2], *allocp = pool - 1;
		return ++allocp;
	}
	
public:
	pointer root;
	
	TREE():root(NULL){};
	
	pointer build(const self::valueType &l, const self::valueType &r, const container &source){
		pointer current = this->newNode();

		if(this->root == NULL)
			this->root = current;

		current->init(l , r, source);

		if(l == r)
			return current;
		
		self::valueType mid = (l + r) >> 1;
		
		current->leftSon = this->build(l, mid, source);
		current->rightSon = this->build(mid + 1, r, source);
		
		return current;
	}
	
	void modify(self::valueType pos, self::valueType from, self::valueType to){
		this->modify(this->root, pos, from, to);
	}
	
	void modify(pointer current, self::valueType pos, self::valueType from, self::valueType to){
		current->data->remove(from);
		current->data->insert(to);

		if(current->leftBound == current->rightBound)
			return;
		
		self::valueType mid = (current->leftBound + current->rightBound) >> 1;
		
		if(pos <= mid)
			this->modify(current->leftSon, pos, from, to);
		else
			this->modify(current->rightSon, pos, from, to);
	}
	
	self::valueType rank(self::valueType l, self::valueType r, self::valueType key){
		return this->rank(this->root, l, r, key) + 1;
	}
	
	self::valueType rank(pointer current, self::valueType l, self::valueType r, self::valueType key){
		if(l <= current->leftBound && current->rightBound <= r)
			return current->data->rank(key) - 1;
		
		self::valueType mid = (current->leftBound + current->rightBound) >> 1;
		
		if(r <= mid)
			return this->rank(current->leftSon, l, r, key);
		if(l > mid)
			return this->rank(current->rightSon, l, r, key);
			
		return this->rank(current->leftSon, l, r, key) + this->rank(current->rightSon, l, r, key);
	}
	
	self::valueType kth(self::valueType l, self::valueType r, self::valueType key){
		self::valueType nowL = minSource, nowR = maxSource;
		
		while(nowL != nowR){
			self::valueType mid = (nowL + nowR) >> 1;
			
			if(this->rank(l, r, mid) - 1 < key)
				nowL = mid + 1;
			else 
				nowR = mid;
		}
		
		return nowL - 1;
	}
	
	self::valueType pre(self::valueType l, self::valueType r, self::valueType key){
		return this->pre(this->root, l, r, key);
	}
	
	self::valueType pre(pointer current, self::valueType l, self::valueType r, self::valueType key){
		if(l <= current->leftBound && current->rightBound <= r)
			return current->data->pre(key);
		
		self::valueType mid = (current->leftBound + current->rightBound) >> 1;
		
		if(r <= mid)
			return this->pre(current->leftSon, l, r, key);
		if(l > mid)
			return this->pre(current->rightSon, l, r, key);
			
		return max(this->pre(current->leftSon, l, r, key), this->pre(current->rightSon, l, r, key));
	}
	
	self::valueType next(self::valueType l, self::valueType r, self::valueType key){
		return this->next(this->root, l, r, key);
	}
	
	self::valueType next(pointer current, self::valueType l, self::valueType r, self::valueType key){
		if(l <= current->leftBound && current->rightBound <= r)
			return current->data->next(key);
		
		self::valueType mid = (current->leftBound + current->rightBound) >> 1;
		
		if(r <= mid)
			return this->next(current->leftSon, l, r, key);
		if(l > mid)
			return this->next(current->rightSon, l, r, key);
			
		return min(this->next(current->leftSon, l, r, key), this->next(current->rightSon, l, r, key));
	}
};

inline int read();

int main(){
	valueType n(0), m(0);
	container source;
	
	n = read();
	m = read();
	
	for(int i = 1; i <= n; ++i){
		source[i] = read();
		minSource = min(minSource, source[i] - 1);
		maxSource = max(maxSource, source[i] + 1);
	}
		
	
	TREE tree;
	
	tree.build(1, n, source);
	
	while(m--){
		int opt;
		cin >> opt;
		if(opt == 1){
			int l(read()), r(read()), key(read());
			cout << tree.rank(l, r, key) << '\n';
		} else if(opt == 2){
			int l(read()), r(read()), key(read());
			cout << tree.kth(l, r, key) << '\n';
		} else if(opt == 3){
			int pos(read()), key(read());
			minSource = min(minSource, key - 1);
			maxSource = max(maxSource, key + 1);
			tree.modify(pos, source[pos], key);
			source[pos] = key;
		} else if(opt == 4){
			int l(read()), r(read()), key(read());
			cout << tree.pre(l, r, key) << '\n';
		} else {
			int l(read()), r(read()), key(read());
			cout << tree.next(l, r, key) << '\n';
		}
	}
}

inline int read(){
	int result(0), ch(getchar());
	
	while(ch < '0' || ch > '9')
		ch = getchar();
		
	while(ch >='0' && ch <= '9'){
		result = (result << 3) + (result << 1) + (ch & 15);
		ch = getchar();
	}
	
	return result;
}