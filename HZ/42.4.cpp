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
	
	void delNode(pointer p){
		free(p);
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
	
	void splay(pointer now){
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
		pointer result = root;
		
		while(result != NULL && result->value != key)
			result = result->son(key > result->value);
		
		if(result != NULL)
			this->splay(result);
			
		return result;
	}
	
	/*TODO:void remove(int key)*/
	
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
			
		return result;
	}
	
	int kth(int key){
		pointer current = root;
		
		while(true){
			if(current->leftSon != NULL && key <= (current->leftSon)->size){
				current = current->leftSon;
				continue;
			}
			
			if(current->leftSon != NULL)
				key -= (current->leftSon)->size;
			
			key -= current->size;
			
			if(key <= 0){
				this->splay(current);
				return current->value;
			}
			
			current = current->rightSon;
		}
	}
};
