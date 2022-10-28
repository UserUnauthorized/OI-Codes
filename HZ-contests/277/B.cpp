//HZ - 277.2
#include<bits/stdc++.h>
using namespace std;
int n,N[10],h(-1);
long long ans(0);
inline void read();
inline long long get(int,int);
int main() {
	read();
//	n = 200000;
//	N[0] = N[1] = N[2] = N[3] = N[4] = 10;
//	N[5] = 2;
//	h = 5;
	//ans = n;
//	if(h == 0)
//		ans = N[0];
//	else
//		ans += 10;
//	for(int i=1; i<=h; ++i) {
//		int t((N[i]-1) * 10 + min);
//		for(int j=1; j<i; ++j)
//			t *= N[j];
//		ans += t;
//	}

//	if(h==0){
//		printf("%d",n);
//		return 0;
//	}

	for(int i=1; i<=9; ++i) {
		for(int j=1; j<=9; ++j) {
			ans += get(i,j) * get(j,i);
		}
//		ans += get(i,10) * get(i,10);
	}

//	cout<<"DEBUG\t"<<get(1,0)<<endl;
	printf("%lld",ans);
	return 0;
}
inline void read() {
	int ch(getchar());
	while(ch<'0' || ch>'9')
		ch = getchar();
	while(ch>='0' && ch<='9') {
		N[++h] = ch ^ 48;
//		if(N[h] == 0)
//			N[h] = 10;
		n = (n << 3) + (n << 1) + (ch ^ 48);
		ch = getchar();
	}
	reverse(N,N+h+1);
}

inline long long get(int first,int last) {
	if(h == 0) {
		if(first != last)
			return (long long)0;
		else if(first > N[0])
			return (long long)0;
		else
			return (long long)1;
	}

	long long result(0);
	if(first == last)
		result += 1;//1位数字

	for(int i = 1; i < h; ++i)
		result += pow(10,i - 1);//从2位到h位

	if(N[h] > first)
		result += pow(10,h -1);//h+1位

	else if(N[h]==first) {
		if(h == 1) {
			if(last <= N[0])
				++result;
		} else {
			long long t(1);
			if(last <= N[0]) {
				for(int i=1; i<h; ++i)
					t *= N[i]+1;
				result += t;
			} else {
				for(int i=1; i<h; ++i) {
					t = 1;
					for (int j=1; j<h; ++j) {
						if(j == i)
							t *= N[j];
						else
							t *= N[j] + 1;
					}
					result += t;
				}
			}
		}
	}
	return result;
}
