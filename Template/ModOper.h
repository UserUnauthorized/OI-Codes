#ifndef OI_CODES_MODOPER_H
#define OI_CODES_MODOPER_H

typedef long long valueType;
valueType MOD;

#define ModOperSafeModOption false

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
#if ModOperSafeModOption
    a %= mod;
    b %= mod;

    if (a < 0)
        a += mod;

    if (b < 0)
        b += mod;
#endif // ModOperSafeModOption

    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
#if ModOperSafeModOption
    a %= mod;
    b %= mod;

    if (a < 0)
        a += mod;

    if (b < 0)
        b += mod;
#endif // ModOperSafeModOption

    a = a - b;

    if (a < 0)
        a += mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
#if ModOperSafeModOption
    a %= mod;
    b %= mod;

    if (a < 0)
        a += mod;

    if (b < 0)
        b += mod;
#endif // ModOperSafeModOption

    return a + b >= mod ? a + b - mod : a + b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
#if ModOperSafeModOption
    a %= mod;
    b %= mod;

    if (a < 0)
        a += mod;

    if (b < 0)
        b += mod;
#endif // ModOperSafeModOption

    return a - b < 0 ? a - b + mod : a - b;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
#if ModOperSafeModOption
    a %= mod;
    b %= mod;

    if (a < 0)
        a += mod;

    if (b < 0)
        b += mod;
#endif // ModOperSafeModOption

    return (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
#if ModOperSafeModOption
    a %= mod;
    b %= mod;

    if (a < 0)
        a += mod;

    if (b < 0)
        b += mod;
#endif // ModOperSafeModOption

    a = (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
#if ModOperSafeModOption
    a %= mod;
    b %= mod;

    if (a < 0)
        a += mod;

    if (b < 0)
        b += mod;
#endif // ModOperSafeModOption

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