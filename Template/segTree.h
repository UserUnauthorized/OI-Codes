#ifndef D_CPP_SEGTREE_H
#define D_CPP_SEGTREE_H

#include <algorithm>
#include <vector>
#include <iterator>

namespace segTree {
    template<class nodeData, class addData>
    class TREE {
    public:
        explicit TREE(nodeData (*_merge)(const nodeData &, const nodeData &));

        template<typename sourceType>
        void build(const sourceType _source[], int _sourceSize);

        template<typename randomAccessIterator>
        void build(randomAccessIterator begin, randomAccessIterator end);

        void insert(int pos, addData data);

        void update(int l, int r, addData data);

        nodeData query(int l, int r);

    private:
        int sourceSize;

        struct treeNode {
            int l, r;
            nodeData data;
            addData lazy;
            bool haveLazy;

            treeNode() : l(-1), r(-1), data(nodeData()), lazy(addData()), haveLazy(-1) {};
        };

        std::vector<treeNode> node;

        nodeData (*merge)(const nodeData &left, const nodeData &right);

        template<typename randomAccessIterator>
        void _build(int id, randomAccessIterator left, randomAccessIterator right, const randomAccessIterator &begin);

        void _insert(int id, int pos, const addData &data);

        void _update(int id, int l, int r, const addData &data);

        nodeData _query(int id, int l, int r);
    };

    template<class nodeData, class addData>
    TREE<nodeData, addData>::TREE(nodeData (*_merge)(const nodeData &, const nodeData &)):sourceSize(0) {
        this->merge = _merge;
    }

    template<class nodeData, class addData>
    template<typename sourceType>
    void TREE<nodeData, addData>::build(const sourceType *source, int _sourceSize) {
        this->sourceSize = _sourceSize;
        this->node.resize(_sourceSize << 2);
        _build(1, source, source + _sourceSize - 1, source);
    }

    template<class nodeData, class addData>
    template<typename randomAccessIterator>
    void TREE<nodeData, addData>::build(randomAccessIterator begin, randomAccessIterator end) {
        this->sourceSize = std::distance(begin, end);
        this->node.resize(this->sourceSize << 2);
        _build(1, begin, end - 1, begin);
    }

    template<class nodeData, class addData>
    template<typename randomAccessIterator>
    void TREE<nodeData, addData>::_build(int id, randomAccessIterator left, randomAccessIterator right,
                                         const randomAccessIterator &begin) {
        node.at(id).l = std::distance(begin, left);
        node.at(id).r = std::distance(begin, right);

        if (left == right) {
            node.at(id).data = nodeData(*right);
            return;
        }

        randomAccessIterator mid = left + (std::distance(left, right) >> 1);

        _build(id << 1, left, mid, begin);
        _build(id << 1 | 1, mid + 1, right, begin);

        node.at(id).data = merge(node.at(id << 1).data, node.at(id << 1 | 1).data);
    }

    template<class nodeData, class addData>
    void TREE<nodeData, addData>::_insert(int id, int pos, const addData &data) {
        if (node.at(id).l == node.at(id).r) {
            node.at(id).data.addon(data);
            return;
        }

        int mid = (node.at(id).l + node.at(id).r) >> 1;

        if (pos > mid)
            _insert(id << 1 | 1, pos, data);
        else
            _insert(id << 1, pos, data);

        node.at(id).data = merge(node.at(id << 1).data, node.at(id << 1 | 1).data);
    }

    template<class nodeData, class addData>
    void TREE<nodeData, addData>::insert(int pos, addData data) {
        _insert(1, pos, data);
    }

    template<class nodeData, class addData>
    void TREE<nodeData, addData>::_update(int id, int l, int r, const addData &data) {
        if (l <= node.at(id).l && node.at(id).r <= r) {
            node.at(id).data.addLazy(data);
            node.at(id).lazy += data;
            node.at(id).haveLazy = true;
            return;
        }

        node.at(id << 1).data.addLazy(node.at(id).lazy);
        node.at(id << 1 | 1).data.addLazy(node.at(id).lazy);
        node.at(id << 1).lazy = node.at(id).lazy;
        node.at(id << 1 | 1).lazy = node.at(id).lazy;
        node.at(id).lazy = addData();

        int mid = (node.at(id).l + node.at(id).r) >> 1;
        if (l <= mid)
            _update(id << 1, l, r, data);
        if (r > mid)
            _update(id << 1 | 1, l, r, data);

        node.at(id).data = merge(node.at(id << 1).data, node.at(id << 1 | 1).data);
    }

    template<class nodeData, class addData>
    nodeData TREE<nodeData, addData>::_query(int id, int l, int r) {
        if (l <= node.at(id).l && node.at(id).r <= r)
            return node.at(id).data;

        node.at(id << 1).data.addLazy(node.at(id).lazy);
        node.at(id << 1 | 1).data.addLazy(node.at(id).lazy);
        node.at(id << 1).lazy = node.at(id).lazy;
        node.at(id << 1 | 1).lazy = node.at(id).lazy;
        node.at(id).lazy = addData();

        int mid = (node.at(id).l + node.at(id).r) >> 1;
        if (r <= mid)
            return _query(id << 1, l, r);
        else if (l > mid)
            return _query(id << 1 | 1, l, r);
        else
            return merge(_query(id << 1, l, r), _query(id << 1 | 1, l, r));
    }

    template<class nodeData, class addData>
    void TREE<nodeData, addData>::update(int l, int r, addData data) {
        _update(1, l, r, data);
    }

    template<class nodeData, class addData>
    nodeData TREE<nodeData, addData>::query(int l, int r) {
        return _query(1, l, r);
    }


    namespace stdNodeData {
        template<typename nodeType>
        class MAX {
        public:
            nodeType maxn;

            MAX() : maxn(0) {};

            template<class addData>
            void addon(const addData &data);

            template<class addData>
            void addLazy(const addData &data);

            friend MAX mergeForMax(const MAX &left, const MAX &right);

            explicit MAX(nodeType source) : maxn(source) {};
        };

        template<typename nodeType>
        MAX<nodeType> mergeForMax(const MAX<nodeType> &left, const MAX<nodeType> &right) {
            return MAX<nodeType>(std::max(left.maxn, right.maxn));
        }

        template<typename nodeType>
        template<class addData>
        void MAX<nodeType>::addon(const addData &data) {
            this->maxn += data;
        }

        template<typename nodeType>
        template<class addData>
        void MAX<nodeType>::addLazy(const addData &data) {
            this->maxn += data;
        }

        template<typename nodeType>
        class MIN {
        public:
            nodeType minn;

            MIN() : minn(0) {};

            template<class addData>
            void addon(const addData &data);

            template<class addData>
            void addLazy(const addData &data);

            friend MIN mergeForMin(const MIN &left, const MIN &right);

            explicit MIN(nodeType source) : minn(source) {};
        };

        template<typename nodeType>
        template<class addData>
        void MIN<nodeType>::addon(const addData &data) {
            this->minn += data;
        }

        template<typename nodeType>
        template<class addData>
        void MIN<nodeType>::addLazy(const addData &data) {
            this->minn += data;
        }

        template<typename nodeType>
        MIN<nodeType> mergeForMin(const MIN<nodeType> &left, const MIN<nodeType> &right) {
            return MIN<nodeType>(std::min(left.minn, right.minn));
        }

        template<typename nodeType>
        class SUM {
        public:
            nodeType sum;
            int size;

            SUM() : sum(0), size(0) {};

            template<class addData>
            void addon(const addData &data);

            template<class addData>
            void addLazy(const addData &data);

            friend SUM mergeForSum(const SUM &left, const SUM &right);

            explicit SUM(nodeType source, int _size = 1) : sum(source), size(_size) {};
        };

        template<typename nodeType>
        template<class addData>
        void SUM<nodeType>::addon(const addData &data) {
            this->sum += data * this->size;
        }

        template<typename nodeType>
        template<class addData>
        void SUM<nodeType>::addLazy(const addData &data) {
            this->sum += data * this->size;
        }

        template<typename nodeType>
        SUM<nodeType> mergeForSum(const SUM<nodeType> &left, const SUM<nodeType> &right) {
            return SUM<nodeType>(left.sum + right.sum, left.size + right.size);
        }
    }
}

#endif //D_CPP_SEGTREE_H