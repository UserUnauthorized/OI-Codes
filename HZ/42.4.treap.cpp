//42.4 [Treap]
//Luogu - P3369 [Treap]
//LOJ - 104 [Treap]
#include<bits/stdc++.h>
using namespace std;

mt19937 getRand(22516);

struct NODE{
	typedef NODE self;
	typedef long long valueType;
	typedef self* pointer;
	typedef unsigned int randType;
	
	pointer leftSon;
	pointer rightSon;
	pointer father;
	randType priority;
		
	self::valueType value;
	self::valueType count;
	self::valueType size;
	
	NODE():leftSon(NULL), rightSon(NULL), father(NULL), priority(0), value(0), count(0), size(0){};
	
	void init(){
		this->leftSon = this->rightSon = this->father = NULL;
		this->priority = ::getRand();
		this->value = 0;
		this->count = this->size = 1;
	}
	
	pointer &son(bool _rightSon_){
		return _rightSon_ ? this->rightSon : this->leftSon;
	}
	
	pointer &son(self::valueType key){
		return key > this->value ? this->rightSon : this->leftSon;
	}
	
	bool isRightSon() const {
		return this == (this->father)->rightSon;
	}
	
	void update(){
		this->size = (this->leftSon != NULL ? (this->leftSon)->size : 0) + (this->rightSon != NULL ? (this->rightSon)->size : 0) + this->count;
	}
};

class TREAP{
public:
	typedef NODE node;
	typedef node::pointer pointer;
	typedef TREAP self;
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
	
	TREAP(): root(NULL){};
	
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
	
	void treap(const pointer &current){
		while(current->father != NULL && current->father->priority > current->priority)
			this->rotate(current);
	}
	
	void insert(self::valueType key){
		pointer current = this->root;
		
		while(current != NULL && key != current->value){
			++current->size;
			current = current->son(key);
		}
		
		if(current == NULL){
			current = this->newNode();
			current->init();
			this->treap(current);
		} else {
			++current->count;
			++current->size;
		}
	}
	
	void remove(self::valueType key){
		pointer current = this->root;
		
		while(/*current != NULL &&*/ key != current->value){
			--current->size;
			current = current->son(key);
		}
		
		/*if(currnet == NULL)
			exit(1)*/
			
		--current->size;
		--current->count;
		
		if(current->count > 0)
			return;
			
		while(current->leftSon != NULL && current->rightSon != NULL)
			this->rotate(current->son(current->leftSon->priority > current->rightSon->priority));
			
		if(current->leftSon != NULL){
			this->rotate(current->leftSon);
			current->father->rightSon = NULL;
//			this->delNode(current);
		} else if(current->rightSon != NULL){
			this->rotate(current->rightSon);
			current->father->leftSon = NULL;
//			this->delNode(current);
		} else {
			current->father->son(current->isRightSon()) = NULL;
//			this->delNode(current);
		}
		
		this->delNode(current);
	}
	
	self::valueType rank(self::valueType key) const {
		pointer current = this->root;
		self::valueType result(1);
		
		while(current != NULL){
			while(current != NULL && key >= current->value)
				current = current->leftSon;
			
			while(current != NULL && key < current->value){
				result += current->count;
				
				if(current->leftSon != NULL)
					result += current->leftSon->size;
				
				current = current->rightSon;
			}
		}
		
		return result;
	}
	
	self::valueType kth(self::valueType key) const {
		
	}
};
