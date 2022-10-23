#include <bits/stdc++.h>
//#include <D:\OI\OI-Codes\Template\debug.h>

using namespace std;
//using namespace DEBUG;

int n;

vector<int> v;

void init();

int main() {
    init();
    sort(v.begin(), v.end());
    //debug(v);
    while (v.size() > 1) {
        int a = v.back();
        v.pop_back();
        int b = v.back();
        v.pop_back();
        v.push_back(max(a, b) - min(a, b));
    }
    printf("%d", v.at(0));
    return 0;
}

void init() {
    scanf("%d", &n);
    v.resize(n);
    for (auto iter = v.begin(); iter != v.end(); ++iter) {
        scanf("%d", iter);
    }
}