#include <bits/stdc++.h>

using namespace std;
void h(int x);

int main() {
    //freopen("C:\\Users\\苏明\\AppData\\Roaming\\JetBrains\\CLion2022.2\\scratches\\scratch_1.txt","w",stdout);

    srand(time(0));

    for (int i = 1; i <= 1000000; ++i) {
        srand(rand());
        printf("%d %d\n", rand() * (rand() % 1000 + 1), rand());
    }
}
