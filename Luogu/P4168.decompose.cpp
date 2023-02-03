//HZ - 36.3[decompose]
//Luogu - P4168[decompose]
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 4e4 + 10, maxK = 220;
typedef pair<int, int> range;

int N_, M, block_, K_, B_;
const int &N = N_, &block = block_, &K = K_, &B = B_;
vector<int> point_;
const vector<int> &point = point_;
array<int, maxN> source_, belong;
const array<int, maxN> &source = source_;
array<int, maxK> leftBound, rightBound;
array<array<int, maxK>, maxK> mode;
array<int, maxN> cnt;
array<array<int, maxN>, maxK> sum;

void init();
int query(range x);
inline range decrypt(const range &x, int lastAns);

int main(){
	init();
	for(int lastAns(0); M > 0; --M){
		int l, r;
		cin >> l >> r;
		cout << (lastAns = query(decrypt(range(l, r), lastAns))) << '\n';
	}
	return 0;
}

void init(){
	cin >> N_ >> M;

	block_ = sqrt(N);
	K_ = ceil((double)N / (double)block);
	
	for(int i = 0; i < N; ++i){
		cin >> source_[i];
		belong[i] = i / block;
	}
	point_.assign(source.begin(), source.begin() + N);
	sort(point_.begin(), point_.end());
	point_.erase(unique(point_.begin(), point_.end()), point_.end());
	point_.push_back(INT_MAX);
	B_ = point.size() - 1;
	
	for(int i = 0 ; i < N; ++i)
		source_[i] = distance(point.begin(), lower_bound(point.begin(), point.end(), source[i]));
	
	for(int k = 0; k < K - 1; ++k)
		rightBound[k] = (leftBound[k] = k * block) + block;
		
	leftBound[K - 1] = K * block - block;
	rightBound[K - 1] = N;

	for(int k = 0; k < K; ++k){
		if(k > 0)
			sum[k] = sum[k - 1];
			
		for(int i = leftBound[k]; i < rightBound[k]; ++i)
			++sum[k][source[i]];
	}

	for(int k = 0; k < K; ++k){
		for(int j = k; j < K; ++j){
			int b = (j > k ? mode[k][j - 1] : B);
			
			for(int i = leftBound[j]; i < rightBound[j]; ++i)
				if (sum[j][source[i]] - (k > 0 ? (sum[k - 1][source[i]]) : 0) > sum[j][b] - (k > 0 ? (sum[k - 1][b]) : 0) ||
				   ((sum[j][source[i]] - (k > 0 ? sum[k - 1][source[i]] : 0) == sum[j][b] - (k > 0 ? sum[k - 1][b] : 0)) && point[source[i]] < point[b]))
				   b = source[i];
				   
			mode[k][j] = b;
		}
	}
}

int query(range x){
	if(x.first > x.second)
		swap(x.first, x.second);
	int const &l = x.first;
	int const &r = x.second;

    if(belong[r] - belong[l] < 2){
    	int b(B);
    	
    	for(int i = l; i <= r; ++i)
    		++cnt[source[i]];
    		
		cnt[b] = 0;

    	for(int i = l; i <= r; ++i)
    		if(cnt[source[i]] > cnt[b] || ((cnt[source[i]] == cnt[b]) && point[source[i]] < point[b]))
    			b = source[i];
    			
    	for(int i = l; i <= r; ++i)
    		cnt[source[i]] = 0;
		
		return point[b];
	} else {
		for(int i = l; i < rightBound[belong[l]]; ++i)
			++cnt[source[i]];
		
		for(int i = leftBound[belong[r]]; i <= r; ++i)
			++cnt[source[i]];
		
		int b(mode[belong[l] + 1][belong[r] - 1]);
		
		for(int i = l; i < rightBound[belong[l]]; ++i){
			int pre = cnt[b] + sum[belong[r] - 1][b] - sum[belong[l]][b];
			int now = cnt[source[i]] + sum[belong[r] - 1][source[i]] - sum[belong[l]][source[i]];
			if(now > pre || ((now == pre) && point[b] > point[source[i]]))
				b = source[i];
		}
		
		for(int i = leftBound[belong[r]]; i <= r; ++i){
			int pre = cnt[b] + sum[belong[r] - 1][b] - sum[belong[l]][b];
			int now = cnt[source[i]] + sum[belong[r] - 1][source[i]] - sum[belong[l]][source[i]];
			if(now > pre || ((now == pre) && point[b] > point[source[i]]))
				b = source[i];
		}
		
		for(int i = l; i < rightBound[belong[l]]; ++i)
			cnt[source[i]] = 0;
		
		for(int i = leftBound[belong[r]]; i <= r; ++i)
			cnt[source[i]] = 0;
		
		return point[b];
	}
}

range decrypt(const range &x, int lastAns){
	return range((x.first + lastAns - 1) % N, (x.second + lastAns - 1) % N);
}

