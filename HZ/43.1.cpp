//HZ - 43.1
//Luogu - P5494
#include<bits/stdc++.h>
using namespace std;

typedef int valueType;
constexpr valueType maxN = 1e5 + 5;

struct SEGNODE{
	typedef SEGNODE self;
	typedef self* pointer;
	typedef ::valueType valueType;

	struct DATA{
		self::valueType value;
		self::valueType cnt;
		
		DATA(): value(INT_MAX), cnt(-1){};
		DATA(self::valueType _value_, self::valueType _cnt_):value(_value_), cnt(_cnt_){};
		
		friend bool operator<(const DATA &a, const DATA &b){
			if(a.cnt != b.cnt)
				return a.cnt < b.cnt;
				
			return a.value > b.value;
		}
		
		void operator+=(self::valueType key){
			this->cnt += key;
		}
		
		void operator+=(const DATA &Object){
			if(this->value == Object.value)
				this->cnt += Object.cnt;
		}
	};
	
	self::valueType leftBound, rightBound, mid;
	pointer leftSon, rightSon;
	DATA data;
	
	SEGNODE():leftBound(-1), rightBound(-1), mid(-1), leftSon(NULL), rightSon(NULL), data(){};
	
	void init(self::valueType l, self::valueType r){
		this->leftBound = l;
		this->rightBound = r;
		this->mid = (this->leftBound + this->rightBound) >> 1;
	}
	
	void update(){
		this->data = DATA();
		
		if(this->leftSon != NULL)
			this->data = std::max(this->data, this->leftSon->data);
		
		if(this->rightSon != NULL)
			this->data = std::max(this->data, this->rightSon->data);
	}
};

SEGNODE* newNode();

class TREE{
public:
	typedef TREE self;
	typedef SEGNODE node;
	typedef node::DATA DATA;
	typedef node* pointer;
	typedef node::valueType valueType;

	pointer root;
	
	TREE():root(NULL){};
	
public:
	void insert(self::valueType pos, self::valueType key){
		this->root = this->insert(this->root, pos, key, 1, maxN);
	}
	
private:
	pointer insert(pointer current, self::valueType pos, self::valueType key, self::valueType l, self::valueType r){
		if(current == NULL){
			current = newNode();
			current->init(l, r);
		}
		
		if(current->leftBound == current->rightBound){
			current->data += key;
			return current;
		}
		
		if(pos <= current->mid)
			current->leftSon = this->insert(current->leftSon, pos, key, l, current->mid);
		else 
			current->rightSon = this->insert(current->rightSon, pos, key, current->mid + 1, r);
		
		current->update();
		
		return current;
	}
	
	self::valueType ans(){
		if(this->root == NULL)
			return 0;
		
		return this->root->data.value;
	}
	
	void merge(const self &Object){
		this->root = this->merge(this->root, Object.root);
	}

private:
	pointer merge(pointer a, pointer b){
		if(a == NULL)
			return b;
		
		if(b == NULL)
			return a;
		
		if(a->leftBound == a->rightBound){
			a->data += b->data;
			return a;
		}
		
		a->leftSon = this->merge(a->leftSon, b->leftSon);
		a->rightSon = this->merge(a->rightSon, b->rightSon);
		
		a->update();
		
		return a;
	}
};

struct EDGE {
    int next;
    int to;

    EDGE():next(-1), to(-1){};

    EDGE(int _next, int _to):next(_next), to(_to){};
};


array<valueType, maxN> dfn, father, deep;
array<TREE, maxN> tree;
array<EDGE, maxN << 1> edge;

valueType LCA(int a, int b);
void dfs(int x, int from);

int main(){
	return 0;
}

SEGNODE* newNode(){
	static SEGNODE pool[maxN << 5];
	static SEGNODE* allocp = pool - 1;
	
	return ++allocp; 
}
