#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

class Basis {
private:
    valueType V;

    ValueVector basis;

public:
    explicit Basis(valueType n) : V(n), basis(V + 1) {}

    void insert(valueType n) {
        for (valueType i = V; i >= 0; --i) {
            if (n & (1ll << i)) {
                if (basis[i]) {
                    n ^= basis[i];
                } else {
                    basis[i] = n;

                    break;
                }
            }
        }
    }

    valueType queryMax() const {
        valueType ans = 0;

        for (valueType i = V; i >= 0; --i)
            ans = std::max(ans, ans ^ basis[i]);

        return ans;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Basis basis(55);

    valueType N;

    std::cin >> N;

    for (valueType i = 0; i < N; ++i) {
        valueType x;

        std::cin >> x;

        basis.insert(x);
    }

    std::cout << basis.queryMax() << std::endl;

    return 0;
}