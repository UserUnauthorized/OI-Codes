#include <bits/stdc++.h>
#include "segTree.h"

void init();

int n, Q;
std::vector<int> source;

int main() {
    init();

    segTree::TREE<segTree::stdNodeData::MIN<int>, int> tree(segTree::stdNodeData::mergeForMin);

    tree.build(::source.begin(), ::source.end());
    while (Q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d ", tree.query(l - 1, r - 1).minn);
    }
    return 0;
}

void init() {
    scanf("%d%d", &n, &Q);

    source.resize(n);

    for (int &iter: source)
        scanf("%d", &iter);
}