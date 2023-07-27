//Luogu - P3376
//LOJ - 101
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;

struct Edge {
public:
    typedef std::list<Edge> container;
    typedef container::iterator iterator;

    valueType to;
    valueType cap;
    valueType flow;
    iterator pair;

    Edge() : to(-1), cap(-1), flow(-1), pair() {};

    Edge(valueType to, valueType cap, iterator pair = iterator()) : to(to), cap(cap), flow(0), pair(pair) {};
};

typedef std::vector<Edge::container> Graph;
typedef std::vector<Edge::iterator> IterVector;

int main() {
    valueType N, M, S, T;

    std::cin >> N >> M >> S >> T;


}