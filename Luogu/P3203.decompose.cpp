//HZ - 36.2[decompose]
//Luogu - P3203[decompose]
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN = 2e5 + 5;

int N, M, block, K;
array<int, maxN> source,to,cnt;

void init();
void update(int x,int key);
int query(int x);

int main(){
	init();
	
	for(cin >> M; M > 0; --M){
		int order;
		cin >> order;
		if(order == 1){
			int x;
			cin >> x;
			cout << query(x) << '\n';
		} else {
			int x, key;
			cin >> x >> key;
			update(x, key);
		}
	}
	
	return 0;
}

void init(){
	to.fill(-1);
	cnt.fill(-1);
	
	cin >> N;
	
	for(int i = 0; i < N; ++i)
		cin >> source[i];
		
	block = sqrt(N);
	K = ceil((double)N / (double)block);

	for(int k = 0; k <= K; ++k){
		int const st = k * block;
		int const end = min(st + block, N);//×ó¿ªÓÒ±Õ 
		for(int i = end - 1; i >= st; --i){
			if(i + source[i] >= end){
				to[i] = i + source[i];
				cnt[i] = 1;
			} else {
				to[i] = to[i + source[i]];
				cnt[i] = cnt[i + source[i]]	+ 1;
			}
		}
	}
}

void update(int x,int key){
	int const k = x / block;
	int const st = k * block;
	int const end = min(st + block, N);//×ó¿ªÓÒ±Õ
	source[x] = key;
	for(; x >= st; --x){
		if(x + source[x] >= end){
			to[x] = x + source[x];
			cnt[x] = 1;
		} else {
			to[x] = to[x + source[x]];
			cnt[x] = cnt[x + source[x]]	+ 1;
		}
	}
}

int query(int x){
	int result(0);
	
	while(x < N){
		result += cnt[x];
		x = to[x];
	}
	
	return result;
}
