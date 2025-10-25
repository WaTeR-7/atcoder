#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <ll MOD>
class modint {
private:
  static_assert((MOD > 0), "The modulus must be positive!");
  static_assert((MOD <= numeric_limits<int>::max()), "The modulus is too big!");
  ll val;
public:
  constexpr modint(ll x = 0) noexcept {
    x %= MOD;
    if (x < 0) x += MOD;
    val = x;
  }
  constexpr ll value() const noexcept {return val;}
  constexpr modint inv() const noexcept {return 1/(*this);}
  constexpr modint pow(modint &x) const noexcept {return *this^x;}
  constexpr modint pow(int x) const noexcept {return *this^x;}
  constexpr modint operator+(const modint &rhs) const noexcept {return modint(*this) += rhs;}
  constexpr modint operator-(const modint &rhs) const noexcept {return modint(*this) -= rhs;}
  constexpr modint operator*(const modint &rhs) const noexcept {return modint(*this) *= rhs;}
  constexpr modint operator/(const modint &rhs) const noexcept {return modint(*this) /= rhs;}
  constexpr modint operator^(const modint &rhs) const noexcept {return modint(*this) ^= rhs;}
  constexpr modint operator-() const noexcept {return modint(-val);}
  constexpr modint &operator++() noexcept {++val; if (val == MOD) val = 0; return *this;}
  constexpr modint &operator++(int) noexcept {modint tmp = *this; ++(*this); return tmp;}
  constexpr modint &operator--() noexcept {--val; if (val < 0) val = MOD-1; return *this;}
  constexpr modint &operator--(int) noexcept {modint tmp = *this; --(*this); return tmp;}
  constexpr modint &operator+=(const modint &rhs) noexcept {
    val += rhs.val;
    if (val >= MOD) val -= MOD;
    return *this;
  }
  constexpr modint &operator-=(const modint &rhs) noexcept {
    val -= rhs.val;
    if (val < 0) val += MOD;
    return *this;
  }
  constexpr modint &operator*=(const modint &rhs) noexcept {
    val = val*rhs.val%MOD;
    return *this;
  }
  constexpr modint &operator/=(const modint &rhs) noexcept {
    modint r = rhs;
    for (ll x = MOD-2; x > 0; x >>= 1) {
      if (x&1) *this *= r;
      r *= r;
    }
    return *this;
  }
  constexpr modint &operator^=(const modint &rhs) noexcept {
    modint temp = *this;
    *this = 1;
    for (ll y = rhs.val; y > 0; y >>= 1) {
      if (y&1) *this *= temp;
      temp *= temp;
    }
    return *this;
  }
  constexpr bool operator==(const modint &rhs) const noexcept {return val==rhs.val;}
  constexpr bool operator!=(const modint &rhs) const noexcept {return !(*this==rhs);}
  constexpr bool operator<(const modint &rhs) const noexcept {return val<rhs.val;}
  constexpr bool operator<=(const modint &rhs) const noexcept {return val<=rhs.val;}
  constexpr bool operator>(const modint &rhs) const noexcept {return val>rhs.val;}
  constexpr bool operator>=(const modint &rhs) const noexcept {return val>=rhs.val;}
};
template<ll MOD>
constexpr modint<MOD> operator+(ll l, const modint<MOD> &r) noexcept {return modint<MOD>(l) += r;}
template<ll MOD>
constexpr modint<MOD> operator-(ll l, const modint<MOD> &r) noexcept {return modint<MOD>(l) -= r;}
template<ll MOD>
constexpr modint<MOD> operator*(ll l, const modint<MOD> &r) noexcept {return modint<MOD>(l) *= r;}
template<ll MOD>
constexpr modint<MOD> operator/(ll l, const modint<MOD> &r) noexcept {return modint<MOD>(l) /= r;}
template<ll MOD>
constexpr modint<MOD> operator^(ll l, const modint<MOD> &r) noexcept {return modint<MOD>(l) ^= r;}
template<ll MOD>
constexpr bool operator==(ll l, const modint<MOD> &r) noexcept {return modint<MOD>(l)==r;}
template<ll MOD>
constexpr bool operator!=(ll l, const modint<MOD> &r) noexcept {return !(l==r);}
template<ll MOD>
constexpr bool operator<(ll l, const modint<MOD> &r) noexcept {return modint<MOD>(l)<r;}
template<ll MOD>
constexpr bool operator<=(ll l, const modint<MOD> &r) noexcept {return modint<MOD>(l)<=r;}
template<ll MOD>
constexpr bool operator>(ll l, const modint<MOD> &r) noexcept {return modint<MOD>(l)>r;}
template<ll MOD>
constexpr bool operator>=(ll l, const modint<MOD> &r) noexcept {return modint<MOD>(l)>=r;}
template<ll MOD>
istream &operator>>(istream &is, modint<MOD> &r) noexcept {
  ll x; is >> x;
  r = modint<MOD>(x);
  return is;
}
template<ll MOD>
ostream &operator<<(ostream &os, const modint<MOD> &r) noexcept {return os<<r.value();}


constexpr ll MOD = 998'244'353;
//constexpr ll MOD = 1'000'000'007;
using mint = modint<MOD>;

int main() {
  mint a, b; cin >> a >> b;
  cout << a.pow(b) << endl;
}