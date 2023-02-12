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
	
	pointer &son(bool _rightSon_){
		return _rightSon_ ? this->rightSon : this->leftSon;
	}
	
	bool isRightSon() const {
		return this == (this->father)->rightSon;
	}
	
	void update(){
		this->size = (this->leftSon ? (this->leftSon)->size : 0) + (this->rightSon ? (this->rightSon)->size : 0) + this->count;
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

public:
	pointer root;
	
	SPLAY(): root(NULL){};
	
	void rotate(pointer now){
		pointer father = now->father;
		bool isRightSon = now->isRightSon();
		father->son(isRightSon) = now->son(!isRightSon);
		
		if(now->son(!isRightSon))
			(now->son(!isRightSon))->father = father;
			
		if((now->father = father->father))
			(now->father)->son(father->isRightSon()) = now;
			
		father->father = now;
		now->son(!isRightSon) = father;
		father->update();
		now->update();
		
		if(now->father == NULL)
			this->root = now;
	}
	
	void Splay(pointer now){
		for(pointer father = now->father; (father = now->father) != NULL; rotate(now))
			if(father->father != NULL)
				rotate(now->isRightSon() == father->isRightSon() ? father : now);
	}
	
	void insert(int key){
		if(root == NULL){
			root = this->newNode();
			root->init();
			root->value = key;
			return;
		}
		
		pointer now(root), father(NULL);
		
		for(;; father = now, now = now->son(key > now->value)){
			if(now == NULL){
				now = newNode();
				now->init();
				now->father = father;
				now->value = key;
				father->son(key > father->value) = now;
				Splay(now);
				return;
			}
			
			if(now->value == key){
				++now->count;
				Splay(now);
				return;
			}
		}
	}
	
	pointer find(int key){
		pointer result = root;
		
		while(now != NULL && now->value != key)
			now = now->son(key > now->value);
		
		if(now != NULL)
			Splay(now);
			
		return now;
	}
	
	
};
