//HZ - 37.7
//Luogu - P2375
#include<bits/stdc++.h>

typedef long long valueType;

constexpr valueType maxN = 1e6 + 5, MOD = 1e9 + 7;

std::array<valueType, maxN> next, num;

int main() {
    valueType n;

    std::cin >> n;

    for (valueType i = 1; i <= n; ++i) {
        std::string data;

        std::cin >> data;

        valueType const length = data.length();

        next.fill(0);
        num.fill(0);

        for (valueType i = 1; i < length; ++i) {
            valueType j = next[i - 1];

            while (j > 0 && data[i] != data[j])
                j = next[j - 1];

            if (data[i] == data[j])
                ++j;

            next[i] = j;

			if(j > 0)
				num[j] = num[next[j - 1]] + 1;
        }

        valueType ans = 1;

		valueType j = 0;

        for (valueType i = 1; i < length; ++i) {
			while (j > 0 && data[i] != data[j])
                j = next[j - 1];

            if (data[i] == data[j])
                ++j;

            valueType const pos = (i + 1) >> 1;

            while (j > pos)
                j = next[j - 1];
			
            ans = (ans * (num[j] + 1)) % MOD;
        }

        std::cout << ans << "\n "[i == n];
    }

    std::cout << std::flush;

    return 0;
}
