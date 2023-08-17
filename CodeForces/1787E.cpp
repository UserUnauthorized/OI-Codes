//Codeforces - 1787E
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::set<valueType> ValueSet;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

int main() {
    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType N, K, X;

        std::cin >> N >> K >> X;

        valueType xorSum = 0;

        for (valueType i = 1; i <= N; ++i)
            xorSum ^= i;

        if (((K & 1) == 1 && xorSum != X) || ((K & 1) == 0 && xorSum != 0)) {
            std::cout << "NO" << '\n';

            continue;
        }

        ValueVector remain;
        ValueMatrix ans;

        for (valueType i = 1; i <= N; ++i) {
            if (i == X) {
                ans.emplace_back(1, i);
            } else if ((i ^ X) > N) {
                remain.emplace_back(i);
            } else if ((i ^ X) < i) {
                ans.push_back({i, i ^ X});
            }
        }

        if (ans.size() < K) {
            std::cout << "NO" << '\n';

            continue;
        }

        for (valueType i = K; i < ans.size(); ++i)
            ans[0].insert(ans[0].end(), ans[i].begin(), ans[i].end());

        ans[0].insert(ans[0].end(), remain.begin(), remain.end());

        std::cout << "YES" << '\n';

        for (valueType i = 0; i < K; ++i) {
            std::cout << ans[i].size() << ' ';

            for (auto const &value: ans[i])
                std::cout << value << ' ';

            std::cout << '\n';
        }
    }
}