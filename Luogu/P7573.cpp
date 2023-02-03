//Luogu - P7573
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin >> T;
	while(T--){
		int n;
		cin >> n;
		if(n == 1) --n;
		cout << (n + 1) / 2 << endl;
	}
	return 0;
}
