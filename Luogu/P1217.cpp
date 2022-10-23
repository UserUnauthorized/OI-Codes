//Luogu - P1217
#include<bits/stdc++.h>

using namespace std;

int a, b;


bool prime(int num) {
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

void output(int num) {
    if ((num >= a) && (num <= b) && (prime(num) == 1)) {
        printf("%d\n", num);
    }

}

int main() {

    scanf("%d%d", &a, &b);
    // Generate the palindromes
    for (int d1 = 1; d1 <= 9; d1 += 2) {
        //��ȥ����Ҫ�������жϣ������ٶ�
        if (a > 10) break;
        output(d1 * 1);
    }

    for (int d1 = 1; d1 <= 9; d1 += 2) {
        //��ȥ����Ҫ�������жϣ������ٶ�
        if (a > 100) break;
        output(d1 * 10 + d1 * 1);
    }

    //��ȥ����Ҫ�������жϣ������ٶ�
    if (b < 100) return 0;
    for (int d1 = 1; d1 <= 9; d1 += 2) {
        //��ȥ����Ҫ�������жϣ������ٶ�
        if (a > 1000) break;
        for (int d2 = 0; d2 <= 9; d2++) {
            output(d1 * 100 + d2 * 10 + d1 * 1);
        }
    }

    //��ȥ����Ҫ�������жϣ������ٶ�
    if (b < 1000) return 0;
    for (int d1 = 1; d1 <= 9; d1 += 2) {
        //��ȥ����Ҫ�������жϣ������ٶ�
        if (a > 10000) break;
        for (int d2 = 0; d2 <= 9; d2++) {
            output(d1 * 1000 + d2 * 100 + d2 * 10 + d1 * 1);
        }
    }

    //��ȥ����Ҫ�������жϣ������ٶ�
    if (b < 10000) return 0;
    for (int d1 = 1; d1 <= 9; d1 += 2) {
        //��ȥ����Ҫ�������жϣ������ٶ�
        if (a > 100000) break;
        for (int d2 = 0; d2 <= 9; d2++) {
            for (int d3 = 0; d3 <= 9; d3++) {
                output(d1 * 10000 + d2 * 1000 + d3 * 100 + d2 * 10 + d1 * 1);
            }
        }
    }

    //��ȥ����Ҫ�������жϣ������ٶ�
    if (b < 100000) return 0;
    for (int d1 = 1; d1 <= 9; d1 += 2) {
        //��ȥ����Ҫ�������жϣ������ٶ�
        if (a > 1000000) break;
        for (int d2 = 0; d2 <= 9; d2++) {
            for (int d3 = 0; d3 <= 9; d3++) {
                output(d1 * 100000 + d2 * 10000 + d3 * 1000 + d3 * 100 + d2 * 10 + d1 * 1);
            }
        }
    }
    //��ȥ����Ҫ�������жϣ������ٶ�
    if (b < 1000000) return 0;
    for (int d1 = 1; d1 <= 9; d1 += 2) {
        //��ȥ����Ҫ�������жϣ������ٶ�
        if (a > 10000000) break;
        for (int d2 = 0; d2 <= 9; d2++) {
            for (int d3 = 0; d3 <= 9; d3++) {
                for (int d4 = 0; d4 <= 9; d4++) {
                    output(d1 * 1000000 + d2 * 100000 + d3 * 10000 + d4 * 1000 + d3 * 100 + d2 * 10 + d1 * 1);
                }
            }
        }
    }

    //��ȥ����Ҫ�������жϣ������ٶ�
    if (b < 10000000) return 0;
    for (int d1 = 1; d1 <= 9; d1 += 2) {
        //��ȥ����Ҫ�������жϣ������ٶ�
        for (int d2 = 0; d2 <= 9; d2++) {
            for (int d3 = 0; d3 <= 9; d3++) {
                for (int d4 = 0; d4 <= 9; d4++) {
                    output(d1 * 10000000 + d2 * 1000000 + d3 * 100000 + d4 * 10000 + d4 * 1000 + d3 * 100 + d2 * 10 +
                           d1 * 1);
                }
            }
        }
    }
    return 0;
}
