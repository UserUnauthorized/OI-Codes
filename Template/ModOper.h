#ifndef OI_CODES_MODOPER_H
#define OI_CODES_MODOPER_H

typedef long long valueType;
valueType MOD;

bool ModOperSafeModOption = false;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= MOD;
        b %= MOD;

        if (a < 0)
            a += MOD;

        if (b < 0)
            b += MOD;
    }

    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= MOD;
        b %= MOD;

        if (a < 0)
            a += MOD;

        if (b < 0)
            b += MOD;
    }

    a = a - b;

    if (a < 0)
        a += mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= MOD;
        b %= MOD;

        if (a < 0)
            a += MOD;

        if (b < 0)
            b += MOD;
    }

    return a + b >= mod ? a + b - mod : a + b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= MOD;
        b %= MOD;

        if (a < 0)
            a += MOD;

        if (b < 0)
            b += MOD;
    }

    return a - b < 0 ? a - b + mod : a - b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= MOD;
        b %= MOD;

        if (a < 0)
            a += MOD;

        if (b < 0)
            b += MOD;
    }

    return (long long) a * b % MOD;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= MOD;
        b %= MOD;

        if (a < 0)
            a += MOD;

        if (b < 0)
            b += MOD;
    }

    a = (long long) a * b % MOD;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
    if (ModOperSafeModOption) {
        a %= MOD;
        b %= MOD - 1;

        if (a < 0)
            a += MOD;

        if (b < 0)
            b += MOD - 1;
    }

    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

#endif //OI_CODES_MODOPER_H