//HZ - 36.4
//Luogu - P2801
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 1e6 + 5;
typedef long long valueType;
typedef array<valueType, maxN>::iterator iterator;
typedef array<valueType, maxN> valueArray;
typedef array<array<valueType, maxN>::iterator, maxN> iterArray;

int N_, Q, K_, block_;
int const &N = N_, &K = K_, &block = block_;
valueArray source, value, belong, leftBound, rightBound, tag;
iterArray leftIter, rightIter, leftSource, rightSource;

void init();
void update(valueType l, valueType r, valueType W);
void update(valueType k);
valueType query(valueType l, valueType r, valueType C);

int main(){
	init();
	while(Q--){
		char order;
		cin >> order;
		if(order == 'M'){
			int l, r, W;
			cin >> l >> r >> W;
			update(l - 1, r - 1, W);
		} else {
			int l, r, C;
			cin >> l >> r >> C;
			cout << query(l - 1, r - 1, C) << '\n';
		}
	}
	return 0;
}

void init(){
	cin >> N_ >> Q;
	
	block_ = sqrt(N);
	K_ = ceil((double)N / (double)block);
	
	for(int i = 0; i < N; ++i){
		cin >> source[i];
		belong[i] = i / block;
	}
	
	copy(source.begin(), source.begin() + N, value.begin());
	
	for(int k = 0; k < K; ++k)
		leftIter[k] = (rightIter[k] = value.begin() + (rightBound[k] = (leftBound[k] = k * block) + block)) - block,
		rightSource[k] = (leftSource[k] = source.begin() + leftBound[k]) + block;
		
	rightBound[K - 1] = N;
	rightIter[K - 1] = value.begin() + N;
	rightSource[K - 1] = source.begin() + N;
	
	for(int k = 0; k < K; ++k)
		sort(leftIter[k], rightIter[k]);
}

void update(valueType l, valueType r, valueType W){
	if(belong[r] - belong[l] < 2){
		for(int i = l; i <= r; ++i)
			source[i] += W;
		
		update(belong[l]);
		update(belong[r]);
		return;
	} else {
		for(int i = l; i < rightBound[belong[l]]; ++i)
			source[i] += W;
		
		update(belong[l]);
		
		for(int i = leftBound[belong[r]]; i <= r; ++i)
			source[i] += W;
		
		update(belong[r]);
		
		for(int k = belong[l] + 1; k < belong[r]; ++k)
			tag[k] += W;
	}
}

valueType query(valueType l, valueType r, valueType C){
	valueType result(0);
	
	if(belong[r] - belong[l] < 2){
		for(int i = l; i <= r; ++i)
			if(source[i] + tag[belong[i]] >= C)
				++result;
	} else {
		for(int i = l; i < rightBound[belong[l]]; ++i)
			if(source[i] + tag[belong[i]] >= C)
				++result;
				
		for(int i = leftBound[belong[r]]; i <= r; ++i)
			if(source[i] + tag[belong[i]] >= C)
				++result;
				
		for(int k = belong[l] + 1; k < belong[r]; ++k)
			result += distance(lower_bound(leftIter[k], rightIter[k], C - tag[k]), rightIter[k]);
	}
	
	return result;
}

void update(valueType k){
	copy(leftSource[k], rightSource[k], leftIter[k]);
	sort(leftIter[k], rightIter[k]);
}
