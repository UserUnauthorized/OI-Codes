//HZ - 42.1
//Luogu - P2234
//LOJ - 10143
#include<bits/stdc++.h>
using namespace std;
typedef int valueType;
constexpr valueType maxN = 3.4e4 + 5;

struct NODE{
	typedef NODE self;
	typedef self* pointer;
	typedef ::valueType valueType;
	
	self::valueType value;
	self::valueType count;
	self::valueType size;
	
	pointer rightSon;
	pointer leftSon;
	pointer father;
	
	NODE():value(0), count(0), size(0), rightSon(NULL), leftSon(NULL), father(NULL){};
	
	bool isRightSon() const {
		return this == this->father->rightSon;
	}
	
	pointer& son(bool _rightSon_){
		return _rightSon_ ? this->rightSon : this->leftSon;
	}
	
	void init(){
		this->rightSon = this->leftSon = this->father = NULL;
		this->value = 0;
		this->count = this->size = 1;
	}
	
	void update(){
		this->size = this->count;
		
		if(this->leftSon != NULL)
			this->size += this->leftSon->size;
		
		if(this->rightSon != NULL)
			this->size += this->rightSon->size;
	}
};

class SPLAY{
public:
	typedef SPLAY self;
	typedef NODE node;
	typedef node::pointer pointer;
	typedef node::valueType valueType;

private:
	pointer newNode(){
		return (pointer)malloc(sizeof(node));
	}
	
	void delNode(pointer &p){
		free(p);
		p = NULL;
	}
	
protected:
	pointer root;

public:
	SPLAY():root(NULL){};
	
	void rotate(pointer current){
		pointer father = current->father;
		bool const isRightSon = current->isRightSon();
		
		father->son(isRightSon) = current->son(!isRightSon);
		
		if(current->son(!isRightSon) != NULL)
			current->son(!isRightSon)->father = father;
			
		if((current->father = father->father) != NULL)
			current->father->son(father->isRightSon()) = current;
			
		current->son(!isRightSon) = father;
		father->father = current;
		father->update();
		current->update();
	}
};
