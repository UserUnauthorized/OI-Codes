//HZ - 37.12
//Loj - 10050
#include<bits/stdc++.h>

typedef unsigned int valueType;

class Trie_01 {
public:
	typedef size_t sizeType;
	static const sizeType maxSize = 32;
	typedef std::bitset<maxSize> bitset;
	
private:
	struct NODE{
		typedef NODE self;
		typedef self* pointer;
		
		pointer leftSon, rightSon;
		
		int weight;
		valueType sum;
		
		NODE() : leftSon(nullptr), rightSon(nullptr), weight(0), sum(0){};
		
		pointer &son(bool _rightSon_) {
			return _rightSon_ ? this->rightSon : this->leftSon;
		}
		
		void update() {
			this->weight = this->sum = 0;
			
			if(this->leftSon) {
				this->weight += this->leftSon->weight;
				this->sum ^= this->leftSon->sum << 1;
			}
			
			if(this->rightSon) {
				this->weight += this->rightSon->weight;
				this->sum ^= (this->rightSon->sum << 1) | (this->rightSon->weight & 1);
			}
		}
	};
	
	typedef NODE::pointer pointer;
	
	static pointer allocate() {
		return new NODE();
	}
	
	
	static void freeNode(pointer &p) {
		delete p;
	}
	
	pointer root;
	
public:
	Trie_01() : root(allocate()){};
	
	void insert(valueType x) {
		insert(this->root, maxSize - 1, bitset(x));
	}
	
	void insert(const bitset &data) {
		insert(this->root, maxSize - 1, data);
	}
	
	valueType get(valueType x) {
		int result = 0;
		
		bitset data(x);
		
		pointer current = this->root;
		
		for(int i = maxSize - 1; i >= 0; --i) {
			if(current->son(!data[i]) != nullptr) {
				current = current->son(!data[i]);
				result  = result << 1 | 1;
			} else {
				current = current->son(data[i]);
				result  = result << 1;
			}
		}
		
		return result;
	}
	
private:
	void insert(const pointer &current, int i, const bitset &data) {
		if(i == -1) {
			++current->weight;
			return;
		}
			
		if(current->son(data[i]) == nullptr)
			current->son(data[i]) = allocate();
		
		insert(current->son(data[i]), i - 1, data);
		
		current->update();
	}
};

int main () {
	int N;
	valueType ans = 0;
	
	std::cin >> N;
	
	std::vector<valueType> source(N);
	
	for(auto &iter : source)
		std::cin >> iter;
		
	Trie_01 tree;
	
	tree.insert(source[0]);
	
	for(int i = 1; i < N; ++i) {
		ans = std::max(ans, tree.get(source[i]));
		tree.insert(source[i]);
	}
	
	std::cout << ans << std::flush;
	
	return 0;
}
