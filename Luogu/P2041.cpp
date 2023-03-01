//Luogu - P2041
#include<stdio.h>

int main() {
    int n;
    scanf("%2d", &n);
    if (n > 2)
        printf("-1");
    else if (n == 2)
        printf("4\n1 1\n2 1\n2 2\n1 2");
    else
        printf("1\n1 1");
    return 0;
}
