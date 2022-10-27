#include<bits/stdc++.h>

using namespace std;
int t, n;
//rev 单数表示逆时针 双数表示顺时针
//skip false表示不跳过下家 true表示跳过下家
//chang false表示不可任意颜色 true表示可以任意颜色
bool ans = false;//ans false表示无解 true表示有解
struct PERSON {
    int color[2022];
    int num[2022];
    bool use[2022];//表示是否被用过
    int useNum;//使用张数
} person[5];

inline void dg(int pers, int ca, int rev, int an)//pers表示是谁  ca表示第几帐牌 tper表示真正应该对应谁 tca表示真正对应的卡号
{
    if (an == 3 * n || ans) {
        ans = true;
        return;
    }
    //此状态对下一状态影响
    bool ski = false;
    bool chan = false;
    int re = rev;
    if (person[pers].num[ca] == 10) ski = true;
    if (person[pers].num[ca] == 11) re++;
    if (person[pers].color[ca] == 4) chan = true;//注意chan可以同时时前后颜色可以任意选
    int next;
    if (re % 2 == 0) next = pers + 1;//顺时针
    else next = pers + 3 - 1;//逆时针
    next %= 3;
    if (next == 0) next = 3;
    if (person[next].useNum == n || ski)//下一个人的牌用完了或上一张牌为skip
    {
        if (re % 2 == 0) next = next + 1;//顺时针
        else next = next + 3 - 1;//逆时针
        next %= 3;
        if (next == 0) next = 3;
    }
    person[pers].use[ca] = true;
    person[pers].useNum++;
    for (int i = 1; i <= n; i++) {
        if (!person[next].use[i] &&
            (chan || person[next].color[i] == 4 || person[next].color[i] == person[pers].color[ca] ||
             person[next].num[i] == person[pers].num[ca])) {
            dg(next, i, re, an + 1);
            // if(an==3*n||ans==true)
            // 	return;
        }
    }
    person[pers].use[ca] = false;
    person[pers].useNum--;
}

int main() {
    //freopen("zhu.in", "r", stdin);
    //freopen("zhu.out", "w", stdout);
    scanf("%d", &t);
    while (t--) {
        memset(person, 0, sizeof(person));
        cin >> n;
        for (int i = 1; i <= 3; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> person[i].color[j] >> person[i].num[j];
                person[i].use[j] = false;
                person[i].useNum = 0;
            }
        }
        for (int i = 1; i <= n; i++) {
            dg(1, i, 0, 1);//顺时针
            dg(1, i, 1, 1);//逆时针 注意要两次，因为不知道二号是谁
            if (ans == 1) break;
        }
        if (ans == 1) cout << "Y" << endl;
        else cout << "N" << endl;
        ans = false;
    }
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}