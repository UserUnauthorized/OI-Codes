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
	valueType cnt;
	valueType size;
	
	pointer &son(bool _rightSon_){
		return _rightSon_ ? this->rightSon : this->leftSon;
	}
	
	bool isRightSon() const {
		return this == *(this->father)->rightSon;
	}
};

class SPLAY{
	
};
