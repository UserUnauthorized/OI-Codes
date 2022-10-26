#include <bits/stdc++.h>

using namespace std;
struct CARD;
struct STATUS;

void init(STATUS &);

bool dfs(STATUS);

inline int read();

inline void write(int &);

inline void write(int *);

int T, n;

struct CARD {
    int color;
    int type;
    bool used;

    CARD() : color(-1), type(-1), used(false) {};

    CARD(int _color, int _type) : color(_color), type(_type), used(false) {};
};

struct STATUS {
    int prevPlayer;
    CARD prevCard;
    bool clockToward;
    vector<CARD> P1, P2, P3;
    int N1, N2, N3;

    STATUS() : prevPlayer(-1), clockToward(true) {};

    ~STATUS() {
        P1.clear();
        P2.clear();
        P3.clear();
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
    n = 0;
    write(n);
    source.prevPlayer = -1;
    source.clockToward = true;
    source.N1 = source.N2 = source.N3 = 0;
    for (int i = 1; i <= n; ++i)
        source.P1.emplace_back(read(), read());
    for (int i = 1; i <= n; ++i)
        source.P2.emplace_back(read(), read());
    for (int i = 1; i <= n; ++i)
        source.P3.emplace_back(read(), read());
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

inline void write(int &result) {
    int ch(getchar());
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        result = (result << 3) + (result << 1) + (ch ^ 48);
        ch = getchar();
    }
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
        const STATUS bak = status;
        for (CARD &card: status.P1) {
            ++status.N1;
            card.used = true;
            status.prevCard = card;
            if (card.type == 11)
                status.clockToward = !status.clockToward;
            if (dfs(status))
                return true;
            status.clockToward = !status.clockToward;
            if (dfs(status))
                return true;
            status = bak;
        }
    }

    if ((status.clockToward && status.prevCard.type != 10) || (!status.clockToward && status.prevCard.type == 10)) {
        if (status.prevPlayer == 1) {
            status.prevPlayer = 2;
            const STATUS bak = status;
            for (CARD &card: status.P2) {
                if (!card.used &&
                    (card.color == status.prevCard.color || card.type == status.prevCard.type || card.color == 4 ||
                     status.prevCard.color == 4)) {
                    ++status.N2;
                    if (status.N1 == n && status.N2 == n && status.N3 == n)
                        return true;
                    card.used = true;
                    status.prevCard = card;
                    if (card.type == 11)
                        status.clockToward = !status.clockToward;
                    if (dfs(status))
                        return true;
                }
                status = bak;
            }
        } else if (status.prevPlayer == 2) {
            status.prevPlayer = 3;
            const STATUS bak = status;
            for (CARD &card: status.P3) {
                if (!card.used &&
                    (card.color == status.prevCard.color || card.type == status.prevCard.type || card.color == 4 ||
                     status.prevCard.color == 4)) {
                    ++status.N3;
                    if (status.N1 == n && status.N2 == n && status.N3 == n)
                        return true;
                    card.used = true;
                    status.prevCard = card;
                    if (card.type == 11)
                        status.clockToward = !status.clockToward;
                    if (dfs(status))
                        return true;
                }
                status = bak;
            }
        } else if (status.prevPlayer == 3) {
            status.prevPlayer = 1;
            const STATUS bak = status;
            for (CARD &card: status.P1) {
                if (!card.used &&
                    (card.color == status.prevCard.color || card.type == status.prevCard.type || card.color == 4 ||
                     status.prevCard.color == 4)) {
                    ++status.N1;
                    if (status.N1 == n && status.N2 == n && status.N3 == n)
                        return true;
                    card.used = true;
                    status.prevCard = card;
                    if (card.type == 11)
                        status.clockToward = !status.clockToward;
                    if (dfs(status))
                        return true;
                }
                status = bak;
            }
        }
    } else {
        if (status.prevPlayer == 1) {
            status.prevPlayer = 3;
            const STATUS bak = status;
            for (CARD &card: status.P3) {
                if (!card.used &&
                    (card.color == status.prevCard.color || card.type == status.prevCard.type || card.color == 4 ||
                     status.prevCard.color == 4)) {
                    ++status.N3;
                    if (status.N1 == n && status.N2 == n && status.N3 == n)
                        return true;
                    card.used = true;
                    status.prevCard = card;
                    if (card.type == 11)
                        status.clockToward = !status.clockToward;
                    if (dfs(status))
                        return true;
                }
                status = bak;
            }
        } else if (status.prevPlayer == 2) {
            status.prevPlayer = 1;
            const STATUS bak = status;
            for (CARD &card: status.P1) {
                if (!card.used &&
                    (card.color == status.prevCard.color || card.type == status.prevCard.type || card.color == 4 ||
                     status.prevCard.color == 4)) {
                    ++status.N1;
                    if (status.N1 == n && status.N2 == n && status.N3 == n)
                        return true;
                    card.used = true;
                    status.prevCard = card;
                    if (card.type == 11)
                        status.clockToward = !status.clockToward;
                    if (dfs(status))
                        return true;

                }
                status = bak;
            }
        } else if (status.prevPlayer == 3) {
            status.prevPlayer = 2;
            const STATUS bak = status;
            for (CARD &card: status.P2) {
                if (!card.used &&
                    (card.color == status.prevCard.color || card.type == status.prevCard.type || card.color == 4 ||
                     status.prevCard.color == 4)) {
                    ++status.N2;
                    if (status.N1 == n && status.N2 == n && status.N3 == n)
                        return true;
                    card.used = true;
                    status.prevCard = card;
                    if (card.type == 11)
                        status.clockToward = !status.clockToward;
                    if (dfs(status))
                        return true;
                }
                status = bak;
            }
        }
    }
    return false;
}