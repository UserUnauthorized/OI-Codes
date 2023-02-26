//HZ - 43.2
#include<bits/stdc++.h>
using namespace std;
typedef long long valueType;

namespace DEBUG {
    template<typename T>
    inline void _debug(const char *format, T t) {
        std::cerr << format << '=' << t << std::endl;
    }

    template<class First, class... Rest>
    inline void _debug(const char *format, First first, Rest... rest) {
        while (*format != ',') std::cerr << *format++;
        std::cerr << '=' << first << ",";
        _debug(format + 1, rest...);
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &V) {
        os << "[ ";
        for (const auto &vv: V) os << vv << ", ";
        os << "]";
        return os;
    }

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

using namespace DEBUG;

constexpr valueType maxN = 4e4 + 5, maxD = 1e9 + 5;
struct SEGNODE{
	typedef SEGNODE self;
	typedef self* pointer;
	typedef ::valueType valueType;

	int leftBound, rightBound, mid;
	pointer leftSon, rightSon;
	self::valueType data;
	
	SEGNODE():leftBound(-1), rightBound(-1), mid(-1), leftSon(NULL), rightSon(NULL), data(0){};
	
	void init(self::valueType l, self::valueType r){
		this->leftBound = l;
		this->rightBound = r;
		this->mid = (this->leftBound + this->rightBound) >> 1;
		this->leftSon = this->rightSon = NULL;
		this->data = 0;
	}
	
	void update(){
		debug(this->leftBound, this->rightBound);
		debug(this->data);
		debug(this->leftSon != NULL, this->rightSon != NULL);
		this->data = 0;
		
		if(this->leftSon != NULL){
			debug(this->leftSon->data);
			this->data += this->leftSon->data;
		}
		
		if(this->rightSon != NULL){
			debug(this->rightSon->data);
			this->data += this->rightSon->data;
		}
		debug(this->data);
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
		this->root = this->update(this->root, 1, maxD, l, r, key);
	}
	
private:
	pointer update(pointer current, self::valueType l ,self::valueType r, self::valueType queryL, self::valueType queryR, self::valueType key){
		if(current == NULL){
			current = newNode();
			current->init(l, r);
		}

		if(queryL <= current->leftBound && current->rightBound <= queryR && current->leftSon == NULL && current->rightSon == NULL){
			debug(current->data, l, r, queryL, queryR, key);
			current->data = std::max(current->data, key * (current->rightBound - current->leftBound + 1));
			debug(current->data);
			return current;
		}
		
		if(queryL <= current->mid)
			current->leftSon = this->update(current->leftSon, l, current->mid, queryL, queryR, key);

		if(queryR > current->mid)
			current->rightSon = this->update(current->rightSon, current->mid + 1, r, queryL, queryR, key);
		
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
