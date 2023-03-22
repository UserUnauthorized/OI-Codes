//HZ - 44.7
//Luogu - P2839
#include<bits/stdc++.h>

namespace HJT{
	#include <bits/stdc++.h>
	typedef unsigned int posType;
	typedef int valueType;
	
	constexpr posType maxN = 2e4 + 5;
	
	class NODE;
	class POINTER;
	class DATA;
	
	typedef posType pointer;
	
	pointer newNode();
	
	class DATA{
	public:
		DATA():sum(-1), leftMax(-1), rightMax(-1){};
		
		DATA(valueType key):sum(key), leftMax(key), rightMax(key){};	
	
	protected:
		valueType sum;
		valueType leftMax;
		valueType rightMax;
	
	public:
		void merge(DATA const &left, DATA const &right);
		
		friend void merge(DATA &father, DATA const &left, DATA const &right);
		
		friend DATA merge(DATA const &left, DATA const &right);
	};
	
	pointer newNode(){
		static posType count = 0;
		return count++;
	}
	
	class NODE{
	public:
		NODE():leftSon(), rightSon(), data(){};
		
	public:
		pointer leftSon;
		pointer rightSon;
	
	public:
		DATA data;
		
	public:
		void update();	
	};

	
	void merge(DATA &father, DATA const &left, DATA const &right){
		father.sum = left.sum + right.sum;
		
		father.leftMax = std::max(left.leftMax, left.sum + right.leftMax);
		
		father.rightMax = std::max(right.rightMax, right.sum + left.leftMax);
	}
	
	DATA merge(DATA const &left, DATA const &right){
		DATA result;
		
		merge(result, left, right);
		
		return result;
	}
	
	void DATA::merge(DATA const &left, DATA const &right){
		HJT::merge(*this, left, right);
	}
	
	std::array<NODE, maxN> tree;
	
	void NODE::update(){
		this->data.merge(tree[this->leftSon].data, tree[this->rightSon].data);
	}
	
	pointer build(posType l, posType r) {
    	pointer current = newNode();

    	if (l == r) {
    	    return current;
    	}

    	posType const mid = (l + r) >> 1;

    	tree[current].leftSon = build(l, mid);
    	tree[current].rightSon = build(mid + 1, r);

    	return current;
	}
	
	pointer insert(const pointer &current, posType nodeL, posType nodeR, posType pos, valueType key) {
    	pointer result = newNode();
    	tree[result] = tree[current];

    	if (nodeL == nodeR) {
    	    tree[result].data = DATA(key);
    	    return result;
    	}

    	posType const mid = (nodeL + nodeR) >> 1;

    	if (pos <= mid)
    	    tree[result].leftSon = insert(tree[current].leftSon, nodeL, mid, pos, key);
    	else
    	    tree[result].rightSon = insert(tree[current].rightSon, mid + 1, nodeR, pos, key);

    	tree[result].update();

    	return result;
	}
	
	DATA query(const pointer &current, posType nodeL, posType nodeR, posType queryL, posType queryR){
		if(queryL <= nodeL && nodeR <= queryR)
			return tree[current].data;
		
		posType const mid = (nodeL + nodeR) >> 1;
		
		if(queryR <= mid)
			return query(tree[current].leftSon, nodeL, mid, queryL, queryR);
		else if(queryL > mid)
			return query(tree[current].rightSon, mid + 1, nodeR, queryL, queryR);
		else
			return merge(query(tree[current].leftSon, nodeL, mid, queryL, queryR), query(tree[current].rightSon, mid + 1, nodeR, queryL, queryR));
	}
}
