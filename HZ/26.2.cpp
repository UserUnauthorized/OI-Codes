//HZ - 26.2
#include<bits/stdc++.h>

constexpr int maxN = 1005;
constexpr int maxM = 1005;

typedef std::list<int> LIST;

int N_, M_;
int const &N = N_, &M = M_;

std::array<LIST, maxM> edge;
std::array<int, maxM> match, use;
std::bitset<maxM> visited;

bool dfs(int x);

void init();

int main() {
    init();

    int ans = 0;

    for (int i = 1; i <= M; ++i) {
        visited.reset();

        if (dfs(i))
            ++ans;
        else
            break;
    }

    std::cout << ans << '\n';

//	for(int i = 1; i <= ans; ++i)
//		std::cout << use[i] - 1 << '\n';

    return 0;
}

void init() {
    std::cin >> N_ >> M_;

    for (int i = 1; i <= M; ++i) {
        int x, y;

        std::cin >> x >> y;

        ++x;
        ++y;

        edge[i].emplace_back(x);
        edge[i].emplace_back(y);
    }
}

bool dfs(int x) {
    for (auto iter: edge[x]) {
        if (!visited[iter]) {
            visited[iter] = true;

            if (!match[iter] || dfs(match[iter])) {
                match[iter] = x;
                use[x] = iter;
                return true;
            }
        }
    }

    return false;
}
