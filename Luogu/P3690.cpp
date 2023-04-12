//Luogu - P3690
#include<bits/stdc++.h>

constexpr int maxN = 1e5 + 5;
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
			this->sum = (this->leftSon != nullptr ? (this->leftSon)->sum : 0) ^ (this->rightSon != nullptr ? (this->rightSon)->sum : 0) ^ this->value;
		}
		
		void init(){
			this->leftSon = this->rightSon = this->father = nullptr;
			this->value = 0;
			this->size = 1;
		}
		
		void init(valueType key) {
			this->leftSon = this->rightSon = this->father = nullptr;
			this->value = key;
			this->size = 1;
		}
		
		void init(valueType key, posType id) {
			this->leftSon = this->rightSon = this->father = nullptr;
			this->value = key;
			this->size = 1;
			this->nodeId = id;
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
		}
	}; 

	typedef NODE::pointer pointer;
	
	typedef NODE::posType posType;

protected:
	size_t _size_;
	
	std::vector<pointer> node;

public:
	LCT():_size_(0){};
	
	LCT(size_t size):_size_(size), node(_size_ + 1){};

private:
	pointer newNode(){
		return (pointer)malloc(sizeof(NODE));
	}

public:
	void set(posType x, valueType key) {
		if(node[x] == nullptr) {
			node[x] = this->newNode();
			node[x]->init(key, x);
		} else {
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
	
	void cut(posType x, posType y);
	
	valueType ans(posType x, posType y);
	
protected:
	void rotate(pointer current) {
		pointer father = current->father;
		bool const isRightSon = current->isRightSon();
		
		father->son(isRightSon) = current->son(!isRightSon);
		
		if(current->son(!isRightSon) != NULL) {
			(current->son(!isRightSon))->father = father;
		}
		
		if((current->father = father->father) && !current->isRoot())
			(current->father)->son(father->isRightSon()) = current;
			
		father->father = current;
		current->son(!isRightSon) = father;
		father->update();
		current->update();
	}
	
	void splay(pointer current) {
		update(current);
		
		for(pointer father = current->father; !(father = current->father)->isRoot(); rotate(current))
			if(!(father->father)->isRoot())
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
		
		return pre->nodeId;
	}
	
	void makeRoot(pointer current) {
		current = node[this->access(current)];
		
		std::swap(current->leftSon, current->rightSon);
		
		current->tag = !current->tag;
	}
	
	void link(pointer x, pointer y) {
		this->makeRoot(x);
		
		this->splay(x);
		
		x -> father = y;
	}
	
	pointer split(pointer x, pointer y) {
		this->makeRoot(x);
		
		this->access(y);
		
		this->splay(y);
		
		return y;
	}
};
