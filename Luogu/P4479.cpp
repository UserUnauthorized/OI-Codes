//Luogu - P4479
//线段树优化 Dijkstra
#include <bits/stdc++.h>

using namespace std;
namespace segTree {
    template<class nodeData>
    class TREE {
    public:
        explicit TREE(nodeData (*_merge)(const nodeData &, const nodeData &));

    private:
        int sourceSize{};
        int treeSize{};


        struct treeNode {
            int l, r;
            nodeData data;
        };

        virtual nodeData merge(const nodeData &left, const nodeData &right) = 0;
    };

    template<class nodeData>
    TREE<nodeData>::TREE(nodeData (*_merge)(const nodeData &, const nodeData &)) {
        this->merge = _merge;
    }

    namespace stdNodeData {
        template<typename nodeType>
        class max {
        public:
            nodeType maxn;

            friend max merge(const max &left, const max &right);

            explicit max(nodeType source);
        };

        template<typename nodeType>
        max<nodeType>::max(nodeType source) {
            maxn = source;
        }

        template<typename nodeType>
        max<nodeType> merge(const max<nodeType> &left, const max<nodeType> &right) {
            return max<nodeType>(std::max(left.maxn, right.maxn));
        }

    }
}

int main() {
}