#include <bits/stdc++.h>

/**
 * X^Y % MOD を計算する
 * 計算量はO(log Y)
 * @param x 底の値
 * @param y 指数の値
 * @param mod 法の値
 * @return X^Y % MOD の値
 */
int pow(int x, int y, int mod) {
    int res = 1;
    for (; y > 0; y >>= 1) {
        if (y & 1) res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}

/**
 * X^Y を計算する
 * long longのオーバーロード
 * 計算量はO(log Y)
 * @param x 底の値
 * @param y 指数の値
 * @return X^Y の値
 */
long long pow(long long x, long long y) {
    long long res = 1;
    for (; y > 0; y >>= 1) {
        if (y & 1) res *= x;
        x *= x;
    }
    return res;
}

/**
 * X^Y % MOD を計算する
 * long longのオーバーロード
 * 計算量はO(log Y)
 * @param x 底の値
 * @param y 指数の値
 * @return X^Y % MOD の値
 */
long long pow(long long x, long long y, long long mod) {
    long long res = 1;
    for (; y > 0; y >>= 1) {
        if (y & 1) res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}