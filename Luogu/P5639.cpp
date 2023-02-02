//Luogu - P5639
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n(0), ans(0);
	cin >> n;
	
	int t(INT_MAX);
	while(n--){
		int k;
		cin >> k;
		if(t != k){
			++ans;
			t = k;
		}
	}
	
	cout << ans;
}
