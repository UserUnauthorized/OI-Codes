//HZ - 42.4
//Luogu - P3369
#include<bits/stdc++.h>
using namespace std;
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
	
	pointer &son(bool _rightSon_) const{
		return _rightSon_ ? this->rightSon : this->leftSon;
	}
	
	bool isRightSon() const {
		return this == (this->father)->rightSon;
	}
	
	void update(){
		this->size = (this->leftSon ? (this->leftSon)->size : 0) + (this->rightSon ? (this->rightSon)->size : 0) + this->cnt;
	}
	
	void init(){
		this->leftSon = this->rightSon = this->father = NULL;
		this->value = 0;
		this->count = this->size = 1;
	}
	
	void clear(){
		this->leftSon = this->rightSon = this->father = NULL;
		this->value this->count = this->size = 0;
	}
};

struct SPLAY{
	typedef NODE node;
	typedef node::pointer pointer;
	
	pointer root;
	
	SPLAY(): root(NULL){};
	
	void rotate(pointer now){
		pointer father = now->father;
		bool isRightSon = now->isRightSon();
		father->son(isRightSon) = now->son(!isRightSon);
		
		if(now->son(!isRightSon))
			(now->son(!isRightSon))->father = father;
			
		if(now->father = father->father)
			(now->father)->son(father->isRightSon()) = now;
			
		father->father = now;
		now->son(!isRightSon) = father;
		father->update();
		now->update();
		
		if(now->father == NULL)
			this->root = now;
	}
};
