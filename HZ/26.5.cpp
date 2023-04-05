//HZ - 26.5
#include<bits/stdc++.h>

constexpr int maxN = 55 * 55;
constexpr int maxM = maxN * maxN;

typedef std::list<int> LIST;

int M_, N_, X_, Y_;
int const &M = M_, &N = N_, &X = X_, &Y = Y_;

std::array<LIST, maxN << 1> edge;
std::array<int, maxN << 1> match;
std::bitset<maxN << 1> visited;
std::array<std::array<char, maxN>, maxN> source;
std::array<std::array<int, maxN>, maxN> belongX, belongY;

bool dfs(int x);

void init();

int main() {
    init();

    int ans = 0;

    for (int i = 1; i <= X; ++i) {
        visited.reset();

        if (dfs(i))
            ++ans;
    }

    std::cout << ans;
}

void init() {
    std::cin >> M_ >> N_;

    for (int i = 1; i <= M; ++i)
        for (int j = 1; j <= N; ++j)
            std::cin >> source[i][j];

    for (int i = 1; i <= M; ++i)
        for (int j = 1; j <= N; ++j)
            if (source[i][j - 1] == '*' || source[i][j - 1] == 'o')
                belongX[i][j] = belongX[i][j - 1];
            else
                belongX[i][j] = ++X_;

    for (int j = 1; j <= N; ++j)
        for (int i = 1; i <= M; ++i)
            if (source[i - 1][j] == '*' || source[i - 1][j] == 'o')
                belongY[i][j] = belongY[i - 1][j];
            else
                belongY[i][j] = ++Y_;

    for (int i = 1; i <= M; ++i)
        for (int j = 1; j <= N; ++j)
            if (source[i][j] == 'o')
                edge[belongX[i][j]].emplace_back(belongY[i][j]);
}

bool dfs(int x) {
    for (auto iter: edge[x]) {
        if (!visited[iter]) {
            visited[iter] = true;

            if (!match[iter] || dfs(match[iter])) {
                match[iter] = x;
                return true;
            }
        }
    }

    return false;
}
