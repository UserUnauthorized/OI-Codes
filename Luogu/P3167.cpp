//HZ - 37.4
//Luogu - P3167
#include <bits/stdc++.h>

using namespace std;
constexpr int maxW = 1e5 + 5, base = 27;
typedef array<char, maxW> inputStr;
typedef unsigned long long hash_type;

void init();

bool check(const inputStr &str, int length);

bool check(int strPos, int matchPos, const inputStr &str, const array<hash_type, maxW> &strHash);

inline bool isWild(const char &c);

inline bool isStr(const char &c);

array<hash_type, maxW> matchHash;
array<hash_type, maxW> bin;
inputStr match;
array<int, maxW> subLength;
int matchLength, n;

int main() {
    init();

    while (n--) {
        inputStr input;
        int inputLength(0);
        int i(getchar());
        while (isStr((char) i) || isWild((char) i)) {
            input[++inputLength] = (char) i;
            i = getchar();
        }
        cout << (check(input, inputLength) ? "YES" : "NO");
    }
}

void init() {
    int input(getchar());
    while (isStr((char) input) || isWild((char) input)) {
        match[++matchLength] = (char) input;
        input = getchar();
    }

    pair<int, int> continuous;

    for (int i = 1; i <= matchLength; ++i)
        isWild(match[i]) ? (subLength[continuous.first] = continuous.second, continuous.first =
                i + 1, continuous.second = 0, matchHash[i] *= base) : (++continuous.second,
                matchHash[i] = matchHash[i - 1] * base + match[i] - 'a' + 1);
    subLength[continuous.first] = continuous.second;

    cin >> ::n;

    bin[0] = 1;
    for (int i = 1; i <= maxW; ++i)
        bin[i] = bin[i - 1] * base;
}

bool isWild(const char &c) {
    return (c == '?' || c == '*');
}

bool isStr(const char &c) {
    return (c >= 'a' && c <= 'z');
}

bool check(const inputStr &str, int length) {
    array<hash_type, maxW> strHash{};

    for (int i = 1; i <= length; ++i)
        strHash[i] = strHash[i - 1] * base + str[i] - 'a' + 1;

    for (int i = 1; i <= matchLength; ++i) {

    }
}

bool check(int strPos, int matchPos, const inputStr &str, const array<hash_type, maxW> &strHash) {
    if (isWild(match[matchPos])) {
        for (int i = 1)
    }
}
