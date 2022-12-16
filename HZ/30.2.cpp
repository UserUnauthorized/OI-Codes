//HZ - 30.2
//Luogu - P4035
#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 15;

typedef array<array<double, maxn>, maxn> MATRIX;
typedef array<double, maxn> ROW;

int n;

ROW solve(MATRIX A, const int &size);

MATRIX transform(MATRIX A, const int &size);

int main() {
    MATRIX matrix;
    cin >> n;

    for (int i = 0; i <= n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> matrix[i][j];

    const ROW ans = solve(transform(matrix, n), n);

    for (int i = 1; i <= n; ++i)
        printf("%.3f ", ans[i]);
}

ROW solve(MATRIX A, const int &size) {
    ROW result;
    int validLines(0);
    for (int i = 0; i < size; ++i) {
        int maxRow = validLines;
        for (int j = validLines + 1; j < size; ++j)
            if (fabs(A[j][i]) > fabs(A[maxRow][i]))
                maxRow = j;

        if (maxRow != validLines)
            swap(A[maxRow], A[validLines]);

        if (A[validLines][i] == 0)
            continue;

        for (int j = 0; j < size; ++j)
            if (j != validLines)
                for (int k = i + 1; k <= size; ++k)
                    A[j][k] -= A[validLines][k] * A[j][i] / A[validLines][i];

        ++validLines;
    }

    if (validLines < size) {
        result[size + 1] = -2;
        while (validLines < size)
            if (A[validLines++][size] != 0) result[size + 1] = -1;
    } else {
        for (int i = 0; i < size; ++i)
            result[i + 1] = A[i][size] / A[i][i];
    }

    return result;
}

MATRIX transform(MATRIX A, const int &size) {
    MATRIX result;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result[i][j] = 2 * (A[i][j] - A[i + 1][j]);
            result[i][size] += pow(A[i][j], 2) - pow(A[i + 1][j], 2);
        }
    }
    return result;
}

