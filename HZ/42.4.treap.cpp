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
//	pointer father;
	randType priority;
		
	self::valueType value;
	self::valueType count;
	self::valueType size;
	
	NODE():leftSon(NULL), rightSon(NULL), /*father(NULL),*/ priority(0), value(0), count(0), size(0){};
	
	void init(){
		this->leftSon = this->rightSon /*= this->father */= NULL;
		this->priority = ::getRand();
		this->value = 0;
		this->count = this->size = 1;
	}
	
	pointer &son(bool _rightSon_){
		return _rightSon_ ? this->rightSon : this->leftSon;
	}
	
/*	bool isRightSon() const {
		return this == (this->father)->rightSon;
	}*/
	
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
	
private:
	void rotate(pointer &current, bool left){
		pointer tmp = current->son(left);
		
		current->son(left) = tmp->son(!left);
		tmp->son(!left) = current;
		
		tmp->update();
		current->update();
		
		current = tmp;
	}
	
public:
	void insert(self::valueType key){
		this->insert(this->root, key);
	}
	
private:	
	void insert(pointer &current, self::valueType key){
		if(current == NULL){
			current = this->newNode();
			current->init();
			current->value = key;
			return;
		} else if(key == current->value){
			++current->count;
			++current->size;
		} else {
			bool const isRightSon = key > current->value;
			
			this->insert(current->son(isRightSon), key);
			if(current->son(isRightSon)->priority < current->priority)
				this->rotate(current, isRightSon);
			
			current->update();
		}
	}
	
public:
	void remove(self::valueType key){
		this->remove(this->root, key);
	}

private:
	void remove(pointer &current, self::valueType key){
		if(key != current->value){
			this->remove(current->son(key > current->value), key);
			current->update();
			return;
		}
		
		if(current->count > 1){
			--current->count;
			--current->size();
			return;
		}
		
		if(current->leftSon == NULL && current->rightSon == NULL){
			this->delNode(current);
			return;
		}
		
		if(current->leftSon == NULL){
			pointer tmp = current;
			current = current->rightSon;
			this->delNode(tmp);
			return;
		}
		
		if(current->rightSon == NULL){
			pointer tmp = current;
			current = current->leftSon;
			this->delNode(tmp);
			return;
		}
		
		bool const direction = current->leftSon->priority > current->rightSon->priority;
		
		this->rotate(current, direction);
		
		this->remove(current->son(!direction), key);
		
		current->update();
	}
	
public:
	self::valueType rank(self::valueType key){
		return this->rank(this->root, key);
	}

private:
	self::valueType rank(pointer current, self::valueType key){
		
	}
};
