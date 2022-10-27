#include <bits/stdc++.h>

using namespace std;
struct CARD;
struct STATUS;

void init(STATUS &);

bool dfs(STATUS);

inline int read();

inline void write(int *);

inline int nextPlayer(const STATUS &status);

int T, n;

struct CARD {
    int color;
    int type;
    bool used;

    CARD() : color(-1), type(-1), used(false) {};

    CARD(int _type, int _color) : color(_color), type(_type), used(false) {};
};

struct STATUS {
    int prevPlayer;
    CARD prevCard;
    bool clockToward;
    vector<CARD> P[5];
    int N[5];

    STATUS() : prevPlayer(-1), clockToward(true) {};

    ~STATUS() {
        P[1].clear();
        P[2].clear();
        P[3].clear();
    }
};

int main() {
    //freopen("zhu.in", "r", stdin);
    //freopen("zhu.out", "w", stdout);
    T = read();
    while (T--) {
        STATUS source;
        init(source);
        if (dfs(source))
            cout << "Y" << endl;
        else
            cout << "N" << endl;
    }
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}

void init(STATUS &source) {
    n = read();
    source.prevPlayer = -1;
    source.clockToward = true;
    source.N[1] = source.N[2] = source.N[3] = 0;
    for (int i = 1; i <= 3; ++i)
        for (int j = 0; j < n; ++j)
            source.P[i].emplace_back(read(), read());

}

inline int read() {
    int result(0), ch(getchar());
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        result = (result << 3) + (result << 1) + (ch ^ 48);
        ch = getchar();
    }
    return result;
}

inline void write(int *result) {
    int ch(getchar());
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        *result = (*result << 3) + (*result << 1) + (ch ^ 48);
        ch = getchar();
    }
}

bool dfs(STATUS status) {
    if (status.prevPlayer == -1) {
        status.prevPlayer = 1;
        //const STATUS bak = status;
        for (CARD &card: status.P[1]) {
            ++status.N[1];
            card.used = true;
            status.prevCard = card;
            if (card.type == 11)
                status.clockToward = !status.clockToward;
            if (dfs(status))
                return true;
            status.clockToward = !status.clockToward;
            if (dfs(status))
                return true;


            status.clockToward = true;
            --status.N[1];
            card.used = false;
        }
        return false;
    }

    if (status.N[1] == n && status.N[2] == n && status.N[3] == n)
        return true;

    const int nextP = nextPlayer(status);
    status.prevPlayer = nextP;
    //const STATUS bak = status;
    const CARD preCard = status.prevCard;
    for (CARD &card: status.P[nextP]) {
        if (!card.used &&
            (card.color == preCard.color || card.type == preCard.type || card.color == 4 ||
             preCard.color == 4)) {
            ++status.N[nextP];
            /*if (status.N[1] == n && status.N[2] == n && status.N[3] == n)
                return true;*/
            card.used = true;
            status.prevCard = card;
            if (card.type == 11)
                status.clockToward = !status.clockToward;
            if (dfs(status))
                return true;

            --status.N[nextP];
            card.used = false;
            if (card.type == 11)
                status.clockToward = !status.clockToward;
        }
    }

    return false;
}

inline int nextPlayer(const STATUS &status) {
    int result;
    if ((status.clockToward && status.prevCard.type != 10) || (!status.clockToward && status.prevCard.type == 10))
        result = status.prevPlayer + 1;
    else
        result = status.prevPlayer - 1;

    if (result > 3)result -= 3;
    else if (result < 1)result += 3;

    while (status.N[result] == n) {
        result += status.clockToward ? 1 : -1;
        if (result > 3)result -= 3;
        else if (result < 1)result += 3;
    }

    return result;
}
