///HZ - 43.9
//Luogu - P2605
#include<bits/stdc++.h>

typedef int valueType;
typedef size_t sizeType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef std::vector<sizeType> SizeVector;

constexpr valueType MIN = INT_MIN >> 1, MAX = INT_MAX >> 1;

valueType N_, K_;
valueType const &N = N_, &K = K_;

ValueVector D_, C_, S_, W_;
ValueVector const &D = D_, &C = C_, &S = S_, &W = W_;

class MinArray {
private:
    sizeType size;

    sizeType blockSize, blockCount;

    ValueVector data;
    SizeVector belong;

    ValueVector tag, min;
    SizeVector leftBound, rightBound;

    valueType result;

public:
    MinArray() = default;

    MinArray(sizeType N) : size(N), blockSize(std::ceil(std::sqrt(size))),
                           blockCount(std::ceil((double) size / (double) blockSize)),
                           data(size, 0), belong(size, 0), tag(blockCount, 0), leftBound(blockCount, 0),
                           rightBound(blockCount, 0) {
        for (sizeType i = 0; i < N; ++i)
            belong[i] = i / blockSize;

        for (sizeType i = 0; i < blockCount; ++i)
            rightBound[i] = (leftBound[i] = i * blockSize) + blockSize;

        leftBound[blockCount - 1] = blockCount * blockSize - blockSize;
        rightBound[blockCount - 1] = size;
    }

    void init(sizeType N) {
        size = N;
        blockSize = std::ceil(std::sqrt(size));
        blockCount = std::ceil((double) size / (double) blockSize);
        data.resize(N, MAX);
        belong.resize(N, 0);
        tag.resize(blockCount, 0);
        min.resize(blockCount, 0);
        leftBound.resize(blockCount, 0);
        rightBound.resize(blockCount, 0);
        result = MAX;
    }

    void update(sizeType l, sizeType r, valueType value) {
        if (l > r)
            return;

        sizeType const left = belong[l];
        sizeType const right = belong[r];

        if (left == right) {
            for (sizeType i = l; i <= r; ++i)
                data[i] += value;

            min[left] = MAX;

            for (sizeType i = leftBound[left]; i < rightBound[left]; ++i)
                min[left] = std::min(min[left], data[i]);
        } else {
            for (sizeType i = left + 1; i < right; ++i) {
                tag[i] += value;
                min[i] += value;
            }

            for (sizeType i = l; i < rightBound[left]; ++i)
                data[i] += value;

            for (sizeType i = leftBound[right]; i <= r; ++i)
                data[i] += value;

            min[left] = MAX;
            for (sizeType i = leftBound[left]; i < rightBound[left]; ++i)
                min[left] = std::min(min[left], data[i]);

            min[right] = MAX;
            for (sizeType i = leftBound[right]; i < rightBound[right]; ++i)
                min[right] = std::min(min[right], data[i]);
        }
    }

    void set(sizeType pos, valueType key) {
        data[pos] = key - tag[belong[pos]];

        min[belong[pos]] = std::min(tag[belong[pos]], data[pos]);
    }

    valueType ans() const {
        valueType result = MAX;

        for (sizeType i = 0; i < blockCount; ++i)
            result = std::min(result, min[i]);

        return result;
    }

    valueType operator[](sizeType i) const {
        return data[i] + tag[belong[i]];
    }
};

std::vector<MinArray> minValue;

void offline(valueType id) {
    valueType const leftPos = D[id] - S[id];

    sizeType const leftId = std::distance(D.begin(), std::lower_bound(D.begin(), D.end(), leftPos));

    if (leftId > 1) {
        for (valueType i = 1; i <= K; ++i)
            minValue[i].update(1, leftId - 1, W[id]);
    }

    for (sizeType i = 1; i <= K; ++i)
        minValue[i].update(id + 1, N, W[id]);
}

class DistanceArray {
private:
    sizeType size;

    sizeType blockSize, blockCount;

    ValueVector data;
    SizeVector belong;

    ValueVector tag, min;
    SizeVector leftBound, rightBound;

public:
    DistanceArray() = default;

    void init(sizeType N) {
        size = N;
        blockSize = std::ceil(std::sqrt(size));
        blockCount = std::ceil((double) size / (double) blockSize);
        data.resize(N, MAX);
        belong.resize(N, 0);
        tag.resize(blockCount, 0);
        min.resize(blockCount, MAX);
        leftBound.resize(blockCount, 0);
        rightBound.resize(blockCount, 0);
    }

    void push(valueType distance) {
        std::queue<sizeType> off;

        for (sizeType i = 0; i < blockCount; ++i) {
            tag[i] += distance;

            min[i] -= distance;

            if (min[i] < 0)
                off.push(i);
        }

        while (!off.empty()) {
            sizeType x = off.front();
            off.pop();

            for (sizeType i = leftBound[x]; i < rightBound[x]; ++i) {
                data[i] -= tag[x];

                if (data[i] < 0) {
                    offline(i);

                    data[i] = MAX;
                }
            }

            min[x] = MAX;

            for (sizeType i = leftBound[x]; i < rightBound[x]; ++i)
                min[x] = std::min(min[x], data[i]);
        }
    }

    void set(sizeType pos, valueType key) {
        if (key < 0) {
            offline(pos);
            return;
        }

        data[pos] = key + tag[belong[pos]];

        min[belong[pos]] = std::min(tag[belong[pos]], data[pos]);
    }

    const valueType &operator[](sizeType i) const {
        return data[i];
    }
} distance;

int main() {
    std::cin >> N_ >> K_;

    minValue.resize(K + 1);
    for (sizeType i = 0; i <= K; ++i)
        minValue[i].init(N + 1);

    distance.init(N + 1);

    D_.resize(N + 1, 0);
    for (int i = 2; i <= N; ++i)
        std::cin >> D_[i];

    C_.resize(N + 1, 0);
    for (int i = 1; i <= N; ++i)
        std::cin >> C_[i];

    S_.resize(N + 1, 0);
    for (int i = 1; i <= N; ++i)
        std::cin >> S_[i];

    W_.resize(N + 1, 0);
    for (int i = 1; i <= N; ++i)
        std::cin >> W_[i];

    std::array<ValueVector, 2> dp;

    dp[0].resize(K + 1, MAX);
    dp[1].resize(K + 1, MAX);

    dp[1][1] = C[1];

    dp[1][0] = W[1];

    minValue[1].set(1, C[1]);
    minValue[0].set(1, W[1]);

    for (int i = 2; i <= N; ++i) {
        sizeType const now = i & 1, pre = now ^ 1;

        dp[now][0] = dp[pre][0] + W[i];

        valueType const step = D[i] - D[i - 1];

        distance.set(i - 1, S[i - 1] - step);

        distance.push(step);

        for (valueType j = 1; j <= K; ++j)
            dp[now][i] = minValue[j - 1].ans() + C[i];

        for (valueType j = 1; j <= K; ++j)
            minValue[j].set(i, dp[now][i]);

    }

    valueType ans = MAX;

    for (int i = 0; i <= K; ++i)
        ans = std::min(ans, dp[N & 1][i]);

    std::cout << ans << std::flush;

    return 0;
}
