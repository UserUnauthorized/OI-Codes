//Luogu - P3690
#include<bits/stdc++.h>

constexpr int maxN = 1e5 + 5;
typedef int valueType;

class LCT {
public:
	struct NODE {
		typedef NODE self;
		typedef *self pointer;
		
		pointer father;
		pointer leftSon;
		pointer rightSon;
		
		valueType value;
	}; 
};
