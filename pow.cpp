#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int pow(int x, int y, int mod) {
  int res = 1;
  for (; y > 0; y >>= 1) {
    if (y & 1) res = res * x % mod;
    x = x * x % mod;
  }
  return res;
}

ll pow(ll x, ll y) {
  ll res = 1;
  for (; y > 0; y >>= 1) {
    if (y & 1) res *= x;
    x *= x;
  }
  return res;
}

ll pow(ll x, ll y, ll mod) {
  ll res = 1;
  for (; y > 0; y >>= 1) {
    if (y & 1) res = res * x % mod;
    x = x * x % mod;
  }
  return res;
}