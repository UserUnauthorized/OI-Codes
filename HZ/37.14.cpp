//HZ - 37.14
//Loj - 10051
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
			
			this->weight = this->weight & 1;
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
	
	void clear() {
		if(this->root->leftSon != nullptr) 
			clear(this->root->leftSon);
			
		if(this->root->rightSon != nullptr) 
			clear(this->root->rightSon);
			
		freeNode(this->root);
		this->root = allocate();
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
	
	void clear(pointer &current) {
		if(current->leftSon != nullptr)
			clear(current->leftSon);
		
		if(current->rightSon != nullptr)
			clear(current->rightSon);
			
		freeNode(current);
		
		current = nullptr;
	}
};

int main () {
	std::ios::sync_with_stdio(false);
	
	int N;
	
	std::cin >> N;
	
	std::vector<valueType> source(N);
	
	for(auto &iter : source) 
		std::cin >> iter;
	
	std::vector<valueType> leftSum(N), rightSum(N);
	
//	std::function<valueType(valueType, valueType)> xorSumOperator = [](valueType a, valueType b) {
//		return a ^ b;
//	};
//	
//	std::partial_sum(source.begin(), source.end(), leftSum.begin(), xorSumOperator);
//	std::partial_sum(source.rbegin(), source.rend(), rightSum.rbegin(), xorSumOperator);
	
	leftSum[0] = source[0];
	for(int i = 1; i < N; ++i)
		leftSum[i] = leftSum[i - 1] ^ source[i];
		
	rightSum[N - 1] = source[N - 1];
	for(int i = N - 2; i >= 0; --i)
		rightSum[i] = rightSum[i + 1] ^ source[i];
	
	std::vector<valueType> leftMax(N), rightMax(N);
	
	Trie_01 leftTree, rightTree;
	
	leftTree.insert(leftSum[0]);
	
	leftMax[0] = leftSum[0];
	
	for(int i = 1; i < N; ++i) {
		leftMax[i] = leftTree.get(leftSum[i]);
		leftTree.insert(leftSum[i]);
	}
	
	rightTree.insert(rightSum[0]);
	
	rightMax[0] = rightSum[0];
	
	for(int i = 1; i < N; ++i) {
		rightMax[i] = rightTree.get(rightSum[i]);
		rightTree.insert(rightSum[i]);
	}
	
	valueType ans = 0;
	
	for(int i = 1; i < N - 1; ++i) {
		ans = std::max(ans, leftMax[i] + rightMax[i + 1]);
	}
	
	std::cout << ans << std::flush;
	
	return 0;
}
