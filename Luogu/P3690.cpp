//Luogu - P3690
#include<bits/stdc++.h>

constexpr int maxN = 1e5 + 5;
typedef int valueType;

class LCT {
public:
	struct NODE {
		typedef NODE self;
		typedef self* pointer;
		
		pointer father;
		pointer leftSon;
		pointer rightSon;
		
		bool tag;
		valueType value;
		valueType size;
		
		pointer &son(bool _rightSon_){
			return _rightSon_ ? this->rightSon : this->leftSon;
		}
	
		bool isRightSon() const {
			return this == (this->father)->rightSon;
		}
		
		void update(){
			this->size = (this->leftSon != NULL ? (this->leftSon)->size : 0) + (this->rightSon != NULL ? (this->rightSon)->size : 0) + 1;
		}
		
		void init(){
			this->leftSon = this->rightSon = this->father = NULL;
			this->value = 0;
			this->size = 1;
		}
		
		void init(valueType key) {
			this->leftSon = this->rightSon = this->father = NULL;
			this->value = key;
			this->size = 1;
		}
	}; 

	typedef NODE::pointer pointer;

protected:
	size_t _size_;
	
	std::vector<pointer> node;

public:
	LCT():_size_(0){};
	
	LCT(size_t size):_size_(size), node(_size_){};
};
