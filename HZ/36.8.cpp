//HZ - 36.8
//Luogu - P4396
#include<bits/stdc++.h>
using namespace std;


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


constexpr int maxN = 1e5 + 5, maxM = 1e6 + 5, maxK = 1e3 + 5;
array<int, maxN> source;
array<int, maxN> belong, sum;
array<int, maxK> blockSum, blockCnt, leftBound, rightBound;

struct Query{
	int l;
	int r;
	int a;
	int b;
	int pos;
	
	Query():l(-1),r(-1),a(-1),b(-1),pos(-1){};
	
	Query(int _l_, int _r_, int _a_, int _b_, int _pos_):l(_l_), r(_r_), a(_a_), b(_b_), pos(_pos_){};
	
	bool operator<(Query const &Object) const{
		if(belong[this->l] != belong[Object.l])
			return this->l < Object.l;
			
		if(belong[this->r] != belong[Object.r])
			return this->r < Object.r;
			
		return this->pos < Object.pos;
	}
};

struct NODE{
	int sum;
	int cnt;
	
	NODE():sum(0),cnt(0){};
	NODE(int _sum_, int _cnt_):sum(_sum_),cnt(_cnt_){};
	
	NODE operator+(NODE const &Object) const{
		return NODE(this->sum + Object.sum, this->cnt + Object.cnt);
	}
	
	void operator+=(NODE const &Object){
		*this = *this + Object;
	}
	
	NODE operator-(NODE const &Object) const{
		return NODE(this->sum - Object.sum, this->cnt - Object.cnt);
	}
};

array<Query, maxM> query;
array<NODE, maxM> out;

void init();
void add(int x);
void del(int x);
inline int read();
NODE getAns(int a, int b);

int N_, M_, D_, block_, K_;
int const &N = N_, &M = M_, &D = D_, &block = block_, &K = K_;

int main(){
	init();

	int nowL(1), nowR(0);
	
	for(int i = 0; i < M; ++i){
		int const &l = query[i].l, &r = query[i].r;
		
		while(nowL > l)
			add(source[--nowL]);
		while(nowL < l)
			del(source[nowL++]);
		while(nowR < r)
			add(source[++nowR]);
		while(nowR > r)
			del(source[nowR]--);
			
		out[i] = getAns(query[i].a, query[i].b);
	}
	
	for(int i = 0; i < M; ++i)
		cout << out[i].sum << ' ' << out[i].cnt << '\n';
	
	return 0;
}

void init(){
	cin >> N_ >> M_;
	
	block_ = ceil((double)N / (double)sqrt(M));
	K_ = ceil((double)N / (double)block);

	for(int i = 1; i <= N; ++i){
		cin >> source[i];
		belong[i] = (i - 1) / block + 1;
//		debug(i, belong[i]);
//		D_ = max(D, source[i]);
	}
//	
//	D_ = max(D, N);
//	
//	for(int i = 1; i <= D; ++i)
//		belong[i] = (i - 1) / block + 1;
	
	for(int k = 1; k <= K; ++k)
		leftBound[k] = (rightBound[k] = k * block + 1) - block;
	
	rightBound[K] = N;
	
	for(int i = 0; i < M; ++i){
		int l, r, a, b;
		cin >> l >> r >> a >> b;
		query[i] = Query(l, r, a, b, i);
	}
	
	sort(query.begin(), query.begin() + M);
}

void add(int x){
	if(belong[x] > K)
		exit(x);
	++blockSum[belong[x]];
	if(!sum[x]++)
		++blockCnt[belong[x]];
}

void del(int x){
	if(belong[x] > K)
		exit(x);
	--blockSum[belong[x]];
	if(!--sum[x])
		--blockCnt[belong[x]];
}

NODE getAns(int a, int b){
	NODE result(0, 0);
	
	if(belong[b] - belong[a] < 2){
		for(int i = a; i <= b; ++i){
			if(sum[i]){
				++result.cnt;
				result.sum += sum[i];
			}
		}
	} else {
		for(int k = belong[a] + 1; k < belong[b]; ++k){
			result.cnt += blockCnt[k];
			result.sum += blockSum[k];
		}
		
		for(int i = a; i < rightBound[belong[a]]; ++i){
			if(sum[i]){
				++result.cnt;
				result.sum += sum[i];
			}
		}
		
		for(int i = leftBound[belong[b]]; i <= b; ++i){
			if(sum[i]){
				++result.cnt;
				result.sum += sum[i];
			}
		}
	}
	
	return result;
}

int read(){
	int result(0), ch(getchar());
	
	while(ch < '0' || ch > '9')
		ch = getchar();
		
	while(ch >= '0' && ch <= '9'){
		result = (result << 3) + (result << 1) + (ch & 15);
		ch = getchar();
	}
	
	return ch;
}
