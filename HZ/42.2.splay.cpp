//HZ - 42.2 [Splay]
//Luogu - P2286 [Splay]
#include<bits/stdc++.h>
using namespace std;
typedef int valueType;
constexpr valueType maxN = 8e4 + 5;
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
//		static node pool[::maxN], *allocp = pool - 1;
//		return ++allocp;
	}
	
	void delNode(pointer &p){
		free(p);
		p = NULL;
	}
	
protected:
	pointer root;

public:
	SPLAY():root(NULL){};
	
	void rotate(const pointer &current){
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
		
		if(current->father == NULL)/*TAG:forget*/
			this->root = current;
	}
	
	void splay(const pointer &current){
		for(pointer father = current->father; (father = current->father)/*TAG:forget*/ != NULL; this->rotate(current))
			if(father->father != NULL)
				this->rotate(current->isRightSon() == father->isRightSon() ? father : current);
	}
	
	void insert(self::valueType key){
		if(this->root == NULL){
			this->root = this->newNode();
			this->root->init();
			this->root->value = key;
			return;
		}
		
		pointer current = this->root, father(NULL);
		
		while(true){
			if(current == NULL){/*TAG:forget*/
				current = this->newNode();
				current->init();
				current->father = father;
				current->value = key;
				father->son(key > father->value) = current;/*TAG:forget*/
				this->splay(current);
				return;
			}
			
			if(current->value == key){
				++current->count;
				this->splay(current);
				return;
			}
			
			father = current;
			current = current->son(key > current->value);
		}
	}
	
	pointer find(self::valueType key){
		pointer result = this->root;
		
		while(result != NULL && result->value != key)
			result = result->son(key > result->value);
			
		if(result != NULL)
			this->splay(result);
			
		return result;
	}
	
	void remove(self::valueType key){
		pointer current = find(key);
		
		if(current == NULL)
			exit(1);
		
		if(current->count > 1){
			--current->count;
			current->update();
			this->splay(current);
			return;
		}
		
		this->splay(current);
		current = this->root;
		
		if(current->leftSon == NULL && current->rightSon == NULL){
			this->delNode(current);
			this->root = NULL;
			return;
		}
		
		if(current->leftSon == NULL){
			this->root = current->rightSon;
			this->root->father = NULL;/*TAG:forget*/
			this->delNode(current);
			return;
		}
		
		if(current->rightSon == NULL){
			this->root = current->leftSon;
			this->root->father = NULL;/*TAG:forget*/
			this->delNode(current);
			return;
		}
		
		this->pre(current->value);
		current->rightSon->father = this->root;
		this->root->rightSon = current->rightSon;/*TAG:forget*/
		this->delNode(current);
		this->root->update();
	}
	
	self::valueType pre(self::valueType key){
		pointer current = this->find(key);
		bool newNodeCreated = false;
		
		if(current == NULL){
			this->insert(key);
			current = this->root;
			newNodeCreated = true;
		}
		
		if(current->leftSon == NULL){
			if(newNodeCreated)
				this->remove(key);
				
			return -1;
		}
		
		for(current = current->leftSon; current->rightSon != NULL/*TAG:forget*/; current = current->rightSon);
		
		if(newNodeCreated)
			this->remove(key);
			
		this->splay(current);
		
		return current->value;
	}
	
	self::valueType next(self::valueType key){
		pointer current = this->find(key);
		bool newNodeCreated = false;
		
		if(current == NULL){
			this->insert(key);
			current = this->root;
			newNodeCreated = true;
		}
			
		if(current->rightSon == NULL){
			if(newNodeCreated)
				this->remove(key);
				
			return -1;
		}
		
		for(current = current->rightSon; current->leftSon != NULL; current = current->leftSon);
		
		if(newNodeCreated)
			this->remove(key);
			
		this->splay(current);
		
		return current->value;
	}
	
	bool empty(){
		return this->root == NULL;
	}
} tree;

int main(){
	valueType n(0), ans(0);
	int treeType = -1;
	cin >> n;
	
	while(n--){
		int type;
		valueType x;
		
		cin >> type >> x;
		
		if(treeType == -1)
			treeType = type;
			
		if(type == treeType || tree.empty()){
			treeType = type;
			tree.insert(x);
		} else {
			valueType const pre = tree.pre(x);
			valueType const next = tree.next(x);
			if(next - x < x - pre){
				tree.remove(next);
				ans += next - x;
			} else {
				tree.remove(pre);
				ans -= x - pre;
			}
		}
	}
	
	cout << ans;
	return 0;
}
