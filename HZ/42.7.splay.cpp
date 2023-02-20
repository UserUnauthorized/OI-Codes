//HZ - 42.7 [Splay]
//Luogu - P4309 [Splay]
#include<bits/stdc++.h>
using namespace std;
typedef int valueType;

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
//EDITED
#include<iostream>

struct NODE{
	typedef NODE self;
	typedef self* pointer;
	typedef self& reference;
	typedef ::valueType valueType;

	pointer father;
	pointer leftSon;
	pointer rightSon;
	self::valueType value;
	self::valueType count;
	self::valueType size;
	self::valueType max;
	bool tag = false;
	
	NODE():father(NULL), leftSon(NULL), rightSon(NULL), value(0), count(0), size(0), max(0), tag(false){};
	
	pointer &son(bool _rightSon_){
		return _rightSon_ ? this->rightSon : this->leftSon;
	}
	
	bool isRightSon() const {
		return this == (this->father)->rightSon;
	}
	
	void update(){
//		if(this->value == INT_MIN || this->value == INT_MAX)
//			return;
		this->size = (this->leftSon != NULL ? (this->leftSon)->size : 0) + (this->rightSon != NULL ? (this->rightSon)->size : 0) + this->count;
		this->max = std::max({(this->leftSon != NULL ? this->leftSon->max : 0), (this->rightSon != NULL ? this->rightSon->max : 0), 1});
		if(this->leftSon != NULL && this->leftSon->value < this->value)
			this->max = std::max(this->max, this->leftSon->max + 1);
	}
	
	void init(){
		this->leftSon = this->rightSon = this->father = NULL;
		this->value = 0;
		this->count = this->size = 1;
		this->max = 1;
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
    		
    	output << Object->value << ' ' << Object->count << ' ' << Object->size << ' ' << Object->max << std::endl;
    	
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
	static const self::valueType preNotFoundValue = -1;
	static const self::valueType nextNotFoundValue = -1;
	static const self::valueType minNotFoundValue = INT_MAX;
	static const self::valueType maxNotFoundValue = INT_MIN;
	
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
				current->max = -1e9;
				this->splay(current);
				return;
			}
			
			current->max = -1e9;
			
			if(current->value == key){
				++current->count;
				current->max = -1e9;
				this->splay(current);
				return;
			}
		}
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
    
//TEMP CODE
public:
	pointer findBySize(self::valueType key){
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
				return current;
			}
			
			current = current->rightSon;
		}
	}
	
	self::valueType insert(self::valueType key, self::valueType pos){
		this->splay(this->findBySize(pos + 1));
		this->splay(this->findBySize(pos + 2), this->root);
		
		pointer current = this->newNode();
		current->init();
		current->value = key;
			
		current->father = this->root->rightSon;
		this->root->rightSon->leftSon = current;
		current->father->update();
		this->root->update();
		
		this->splay(current);
//		cerr << *this << "\n\n";
		current->max = this->root->leftSon->max + 1;
		current->update();
		return current->max;
	}
	
	
};

#include<bits/stdc++.h>
using namespace std;

int main(){
	SPLAY tree;
	valueType n;
	
	cin >> n;
	tree.insert(INT_MIN);
	tree.insert(INT_MAX);
	
	for(int i = 1; i <= n; ++i){
		int t(0);
		cin >> t;
		cout << tree.insert(i, t) - 1 << '\n';
//		cerr << tree << endl << endl;
	}
	
	return 0;
}
