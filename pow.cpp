#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/**
 * X^Y % MOD を計算する
 * 計算量はO(log Y)
 * @param x int 底の値
 * @param y int 指数の値
 * @param mod int 法の値
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
 * @param x ll 底の値
 * @param y ll 指数の値
 * @return X^Y の値
 */
ll pow(ll x, ll y) {
  ll res = 1;
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
 * @param x ll 底の値
 * @param y ll 指数の値
 * @return X^Y % MOD の値
 */
ll pow(ll x, ll y, ll mod) {
  ll res = 1;
  for (; y > 0; y >>= 1) {
    if (y & 1) res = res * x % mod;
    x = x * x % mod;
  }
  return res;
}