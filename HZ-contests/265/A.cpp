//HZ - 265.1
#include <bits/stdc++.h>

using namespace std;

string source, mirror;

int n;

void init();

int main() {
    init();
    reverse(mirror.begin(), mirror.end());
    for (auto sourceIter = source.begin(), mirrorIter = mirror.begin();
         sourceIter != source.end() && mirrorIter != mirror.end(); ++sourceIter, ++mirrorIter) {
        if (*sourceIter == '#')
            putchar(*mirrorIter);
    }
    return 0;
}

void init() {
    cin >> source;
    cin >> mirror;
}