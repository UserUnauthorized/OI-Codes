//HZ - 36.3[decompose]
//Luogu - P4168[decompose]
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 4e5 + 5, maxK = 520;
typedef pair<int, int> range;

int N_, M, block_, K_;
const int &N = N_, &block = block_, &K = K_; //避免意外更改 
array<int, maxN> source, belong;
array<int, maxK> leftBound, rightBound;
array<array<int, maxK>, maxK> mode;
unordered_map<int, int> cnt;
unordered_map<int, vector<int> > pos;

void init();
int query(const range &x);
int count(int x, const range &r);
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
	
	for(int i = 0; i < N; ++i){//下标从0开始便于处理 
		cin >> source[i];
		belong[i] = i / block;
	}

	for(int k = 0; k < K; ++k)
		rightBound[k] = (leftBound[k] = k * block) + ((k == K - 1) ? (N - K * block + block) : block);
		
	for(int i = 0; i < N; ++i)
		pos[source[i]].push_back(i);
	
	for(int k = 0; k < K; ++k){
		cnt.clear();
		for(int j = k; j < K; ++j){
			int b(INT_MAX), ans = 0;
			
			for(int i = leftBound[j]; i < rightBound[j]; ++i){
				++cnt[source[i]];
				if(cnt[source[i]] > ans)
					ans = cnt[(b = source[i])];
				else if(cnt[source[i]] == ans)
					b = min(b, source[i]);
			}
			
			if(j > 0) {
				if(cnt[mode[k][j - 1]] > ans)
					ans = cnt[(b = mode[k][j - 1])];
				else if(cnt[mode[k][j - 1]] > ans)
					b = min(b, mode[k][j - 1]);
			}
			
			mode[k][j] = mode[j][k] = b;
		}
	}
}

int query(const range &x){
	int const &l = x.first;
	int const &r = x.second;
	
	if(belong[l] == belong[r]){
		int b(INT_MAX), ans = 0;
			
		for(int i = l; i < r; ++i){
			++cnt[source[i]];
			if(cnt[source[i]] > ans)
				ans = cnt[(b = source[i])];
			else if(cnt[source[i]] == ans)
				b = min(b, source[i]);
		}
		
		return b;
	}
	
	int b(INT_MAX), ans = 0, sum(0);
	
	for(int i = l; i < rightBound[l]; ++i){
		sum = count(source[i], range(l, r));
		if(sum > ans)
			ans = sum, b = source[i];
		else if(sum == ans)
			b = min(b, source[i]);
	}
	
	for(int i = leftBound[r]; i <= r; ++i){
		sum = count(source[i], range(l, r));
		if(sum > ans)
			ans = sum, b = source[i];
		else if(sum == ans)
			b = min(b, source[i]);
	}
	
	if (belong[l] + 1 <= belong[r] - 1) {
        sum = count(mode[belong[l] + 1][belong[r] - 1], range(l, r));
        if (sum > ans)
            ans = sum, b = mode[belong[l] + 1][belong[r] - 1];
        else if (sum == ans)
            b = min(b, mode[belong[l] + 1][belong[r] - 1]);
    }
    return b;
}

int count(int x, const range &r){
	return upper_bound(pos[x].begin(), pos[x].end(), r.second) - lower_bound(pos[x].begin(), pos[x].end(), r.first);
}

range decrypt(const range &x, int lastAns){
	return range((x.first + lastAns - 1) % N, (x.second + lastAns - 1) % N);
}
