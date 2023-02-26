//HZ - 43.2
#include<bits/stdc++.h>
using namespace std;
typedef long long valueType;
constexpr valueType maxN = 4e4 + 5, maxD = 1e9 + 5;
struct SEGNODE{
	typedef SEGNODE self;
	typedef self* pointer;
	typedef ::valueType valueType;

	bool isLeaf;
	int leftBound, rightBound, mid;
	pointer leftSon, rightSon;
	self::valueType data, lazy;
	
	SEGNODE():isLeaf(false), leftBound(-1), rightBound(-1), mid(-1), leftSon(NULL), rightSon(NULL), data(0), lazy(0){};
	
	void init(self::valueType l, self::valueType r, self::valueType key){
		this->leftBound = l;
		this->rightBound = r;
		this->isLeaf = (l == r);
		this->mid = (this->leftBound + this->rightBound) >> 1;
		this->leftSon = this->rightSon = NULL;
		this->data = key * (r - l + 1);
		this->lazy = key;
	}
	
	void push(){
		if(this->lazy == 0)
			return;
			
		if(this->leftSon != NULL)
			this->leftSon->data = this->leftSon->lazy = std::max(this->lazy, this->leftSon->lazy);
			
		if(this->rightSon != NULL)
			this->rightSon->data = this->rightSon->lazy = std::max(this->lazy, this->rightSon->lazy);
			
		this->lazy = 0;
	}
	
	void update(){
		this->data = 0;
		
		if(this->leftSon != NULL)
			this->data += this->leftSon->data;
		
		if(this->rightSon != NULL)
			this->data += this->rightSon->data;
	}
};

SEGNODE* newNode();

class TREE{
public:
	typedef TREE self;
	typedef SEGNODE node;
	typedef node* pointer;
	typedef node::valueType valueType;

	pointer root;
	
	TREE():root(NULL){};
	
public:
	void update(self::valueType l ,self::valueType r, self::valueType key){
		this->root = this->update(this->root, l, r - 1, key);
	}
	
private:
	pointer update(pointer current, self::valueType l ,self::valueType r, self::valueType key){
		if(current == NULL){
			current = newNode();
			current->init(l, r, key);
		}
		
		if(l <= current->leftBound && current->rightBound <= r){
			current->lazy = std::max(current->lazy, key);
			
			if(current->leftSon == NULL && current->rightSon == NULL){
				current->data = key * (current->rightBound - current->leftBound + 1);
				return current;
			}
			
			current->push();
		}
		
		if(l <= current->mid)
			current->leftSon = this->update(current->leftSon, l, current->mid, key);
		if(r > current->mid)
			current->rightSon = this->update(current->rightSon, current->mid + 1, r, key);
		
		current->update();
		
		return current;
	}

public:
	self::valueType ans(){
		if(this->root == NULL)
			return 0;
		
		return this->root->data;
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
} tree;

int main(){
	valueType n;
	cin >> n;
	
	while(n--){
		valueType a, b, k;
		
		cin >> a >> b >> k;
		
		tree.update(a, b, k);
	}
	
	cout << tree.ans();
	
	return 0;
}

SEGNODE pool[maxN * 60];
SEGNODE* newNode(){
	static SEGNODE* allocp = pool - 1;
	
	return ++allocp; 
}
