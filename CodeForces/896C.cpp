//CodeForces 896C
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

struct Node {
    int l, r;
    mutable valueType value;

    explicit Node(int l, int r = -1, valueType value = 0) : l(l), r(r), value(value) {}

    bool operator<(const Node &o) const {
        return l < o.l;
    }
};

valueType N, M;

typedef std::set<Node> Set;
typedef Set::iterator iterator;

Set tree;

auto split(int x) {
    if (x > N) {
        return tree.end();
    }

    auto it = std::prev(tree.upper_bound(Node(x)));

    if (it->l == x) {
        return it;
    }

    auto const l = it->l;
    auto const r = it->r;
    auto const value = it->value;

    tree.erase(it);
    tree.insert(Node(l, x - 1, value));

    return tree.insert(Node(x, r, value)).first;
}

void assign(int l, int r, valueType v) {
    auto itr = split(r + 1), itl = split(l);
    tree.erase(itl, itr);
    tree.insert(Node(l, r, v));
}

valueType rand(valueType &seed) {
    valueType const result = seed;

    seed = (seed * 7 + 13) % 1000000007;

    return result;
}

std::stringstream Uncompress(valueType seed, valueType vmax) {
    std::stringstream os;

    for (valueType i = 1; i <= N; ++i) {
        os << rand(seed) % vmax + 1 << ' ';
    }

    os << std::endl;

    for (valueType i = 1; i <= M; ++i) {
        valueType const op = (rand(seed) % 4) + 1;
        valueType l = rand(seed) % N + 1;
        valueType r = rand(seed) % N + 1;
        valueType x, y;

        if (l > r)
            std::swap(l, r);

        if (op == 3)
            x = rand(seed) % (r - l + 1) + 1;
        else
            x = rand(seed) % vmax + 1;

        os << op << ' ' << l << ' ' << r << ' ' << x;

        if (op == 4) {
            y = rand(seed) % vmax + 1;

            os << ' ' << y;
        }

        os << '\n';
    }

    return os;
}

int main() {
    valueType seed, vmax;

    std::cin >> N >> M >> seed >> vmax;

    std::stringstream os = Uncompress(seed, vmax);
    std::cin.rdbuf(os.rdbuf());

    for (int i = 1; i <= N; ++i) {
        valueType x;

        std::cin >> x;

        tree.insert(Node(i, i, x));
    }

    for (int i = 0; i < M; ++i) {
        valueType op, l, r, x, y;

        std::cin >> op >> l >> r >> x;
    }
}