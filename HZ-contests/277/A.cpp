//HZ -  277.1
#include<bits/stdc++.h>

using namespace std;

inline void read(int &);

inline void read(vector<int> &);

inline void init();

inline bool require(const int &);

int n, tCount(0), lCount(0);
vector<vector<int>> source;

int main() {
    init();
    for (auto iter = source.begin(); iter != source.end(); ++iter) {
        int lowerCaseCount(0), upperCaseCount(0);
        for (auto subIter = iter->begin(); subIter != iter->end(); ++subIter) {
            if (*subIter > 96 && *subIter < 123)
                ++lowerCaseCount;
            else if (*subIter > 64 && *subIter < 91)
                ++upperCaseCount;
        }
        if (iter->front() > 64 && iter->front() < 91 || upperCaseCount > lowerCaseCount)
            ++tCount;
        if (lowerCaseCount % 2 == 0 && iter->back() > 47 && iter->back() < 58)
            ++lCount;
    }
    printf("%d %d", tCount, lCount);
    return 0;
}

void init() {
    read(n);
    source.resize(n);
    for (auto iter = source.begin(); iter != source.end(); ++iter)
        read(*iter);
}

inline void read(int &result) {
    int ch(getchar());
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        result = (result << 3) + (result << 1) + (ch ^ 48);
        ch = getchar();
    }
}

inline void read(vector<int> &result) {
    int ch(getchar());
    while (require(ch)) {
        result.push_back(ch);
        ch = getchar();
    }
}

inline bool require(const int &x) {
    return x == 32 || x > 47 && x < 58 || x > 96 && x < 123 || x > 64 && x < 91;
}
