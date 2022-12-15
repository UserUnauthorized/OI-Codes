//HZ - 30.1
//Luogu - P2455
#include <bits/stdc++.h>

using namespace std;

constexpr int maxn = 5e1 + 5;

typedef array<array<double, maxn>, maxn> MATRIX;
typedef array<double, maxn> ROW;

int n;

ROW solve(MATRIX A, const int &size);

int main() {
    MATRIX matrix;
    cin >> n;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= n; ++j)
            cin >> matrix[i][j];

    const ROW ans = solve(matrix, n);

    if (ans[n + 1] == -1)
        cout << -1;
    else if (ans[n + 1] == -2)
        cout << 0;
    else
        for (int i = 1; i <= n; ++i)
            printf("x%d=%.2f\n", i, ans[i]);

    return 0;
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