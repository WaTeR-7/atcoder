#include <bits/stdc++.h>


/**
 * MODを法とする整数のクラス
 * MODは0より大きく，intの最大値以下でなければならない
 * 徐算にはフェルマーの小定理を利用しているため，MODが素数である必要がある
 * 内部では0以上MOD未満の値を保持する
 * 加算，減算，乗算，除算，累乗などの演算や比較演算子が定義されている
 */
template <long long MOD>
class ModInt {
  
    static_assert((MOD > 0), "The modulus must be positive!");
    static_assert((MOD <= std::numeric_limits<int>::max()), "The modulus is too big!");
  
  private:
    long long val_;  // MODで割った余りを保つ値 0以上MOD未満となる
  
  public:
    /**
     * ModIntのコンストラクタ
     * 計算量はO(1)である
     * @param x 初期値を指定する引数 指定されない場合は0になる 負の値を指定しても，内部では0以上MOD未満の値に変換される
     */
    constexpr ModInt(long long x = 0) noexcept {
        x %= MOD;
        if (x < 0) x += MOD;
        val_ = x;
    }
    
    /**
     * ModIntの値を取得する関数
     * 計算量はO(1)である
     * @return ModIntの値をlong long型で返す
     */
    constexpr long long value() const noexcept { return val_; }
    
    /**
     * ModIntの逆元を求める関数
     * 1/(*this)として，/演算子を呼び出して新しいModIntを返す
     * 計算量はO(log(MOD))である
     * @return ModIntの逆元を返す
     */
    constexpr ModInt inv() const noexcept { return 1/(*this); }
    
    /**
     * ModIntの累乗を求める関数
     * (*this)^xとして，^演算子を呼び出して新しいModIntを返す
     * 計算量はO(log(x))である
     * @param x 累乗の指数を指定する引数
     * @return ModIntの累乗を返す
     */
    constexpr ModInt pow(ModInt& x) const noexcept { return (*this)^x; }
    
    /**
     * ModIntの累乗を求める関数
     * intを引数とするオーバーロード
     * - x >= 0のとき: (*this)^xとして，^演算子を呼び出して新しいModIntを返す
     *    計算量はO(log(x))である
     * - x < 0のとき: inv()^(-x)として，inv()と^演算子を呼び出して新しいModIntを返す
     *     計算量はO(log(-x) + log(MOD))である
     * @param x 累乗の指数を指定する引数
     * @return ModIntの累乗を返す
     */
    constexpr ModInt pow(int x) const noexcept { return x >= 0 ? (*this)^x : inv()^(-x); }
    
    /**
     * ModInt同士の加算を行う+演算子のオーバーロード
     * ModInt(*this) += rhsとして，+=演算子を呼び出して新しいModIntを返す
     * 2数の値は変更しない
     * 計算量はO(1)である
     * @param rhs 加算するModIntを指定する引数
     * @return 加算の結果を返す
     */
    constexpr ModInt operator+(const ModInt& rhs) const noexcept { return ModInt(*this) += rhs; }
    
    /**
     * ModInt同士の減算を行う-演算子のオーバーロード
     * ModInt(*this) -= rhsとして，-=演算子を呼び出して新しいModIntを返す
     * 2数の値は変更しない
     * 計算量はO(1)である
     * @param rhs 減算するModIntを指定する引数
     * @return 減算の結果を返す
     */
    constexpr ModInt operator-(const ModInt& rhs) const noexcept { return ModInt(*this) -= rhs; }
    
    /**
     * ModInt同士の乗算を行う*演算子のオーバーロード
     * ModInt(*this) *= rhsとして，*=演算子を呼び出して新しいModIntを返す
     * 2数の値は変更しない
     * 計算量はO(1)である
     * @param rhs 乗算するModIntを指定する引数
     * @return 乗算の結果を返す
     */
    constexpr ModInt operator*(const ModInt& rhs) const noexcept { return ModInt(*this) *= rhs; }
    
    /**
     * ModInt同士の除算を行う/演算子のオーバーロード
     * ModInt(*this) /= rhsとして，/=演算子を呼び出して新しいModIntを返す
     * 2数の値は変更しない
     * 計算量はO(log(MOD))である
     * @param rhs 除算するModIntを指定する引数
     * @return 除算の結果を返す
     */
    constexpr ModInt operator/(const ModInt& rhs) const noexcept { return ModInt(*this) /= rhs; }
    
    /**
     * ModInt同士の累乗を行う^演算子のオーバーロード
     * ModInt(*this) ^= rhsとして，^=演算子を呼び出して新しいModIntを返す
     * 2数の値は変更しない
     * 計算量はO(log(rhs))である
     * @param rhs 累乗するModIntを指定する引数
     * @return 累乗の結果を返す
     */
    constexpr ModInt operator^(const ModInt& rhs) const noexcept { return ModInt(*this) ^= rhs; }
    
    /**
     * ModIntの単項マイナスを行う-演算子のオーバーロード
     * ModInt(-(*this))として，-演算子を呼び出して新しいModIntを返す
     * 値は変更しない
     * 計算量はO(1)である
     * @return 単項マイナスの結果を返す
     */
    constexpr ModInt operator-() const noexcept { return ModInt(-val_); }
    
    /**
     * ModIntの前置インクリメントを行う++演算子のオーバーロード
     * val_をインクリメントして，自身を返す
     * 計算量はO(1)である
     * @return インクリメント後の自身を返す
     */
    constexpr ModInt& operator++() noexcept { ++val_; if (val_ == MOD) val_ = 0; return *this; }
    
    /**
     * ModIntの後置インクリメントを行う++演算子のオーバーロード
     * インクリメント前の自身をtmpに保存してからval_をインクリメントし，tmpを返す
     * 計算量はO(1)である
     * @return インクリメント前の自身のコピーを返す
     */
    constexpr ModInt& operator++(int) noexcept { ModInt tmp = *this; ++(*this); return tmp; }
    
    /**
     * ModIntの前置デクリメントを行う--演算子のオーバーロード
     * val_をデクリメントして，自身を返す
     * 計算量はO(1)である
     * @return デクリメント後の自身を返す
     */
    constexpr ModInt& operator--() noexcept { --val_; if (val_ < 0) val_ = MOD-1; return *this; }
    
    /**
     * ModIntの後置デクリメントを行う--演算子のオーバーロード
     * デクリメント前の自身をtmpに保存してからval_をデクリメントし，tmpを返す
     * 計算量はO(1)である
     * @return デクリメント前の自身のコピーを返す
     */
    constexpr ModInt& operator--(int) noexcept { ModInt tmp = *this; --(*this); return tmp; }
    
    /**
     * ModIntにModIntを加算代入する+=演算子のオーバーロード
     * 自身は変更されるが，引数rhsは変更されない
     * 計算量はO(1)である
     * @param rhs 加算するModIntを指定する引数
     * @return 加算後の自身を返す
     */
    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {
        val_ += rhs.val_;
        if (val_ >= MOD) val_ -= MOD;
        return *this;
    }
    
    /**
     * ModIntからModIntを減算代入する-=演算子のオーバーロード
     * 自身は変更されるが，引数rhsは変更されない
     * 計算量はO(1)である
     * @param rhs 減算するModIntを指定する引数
     * @return 減算後の自身を返す
     */
    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {
        val_ -= rhs.val_;
        if (val_ < 0) val_ += MOD;
        return *this;
    }
    
    /**
     * ModIntにModIntを乗算代入する*=演算子のオーバーロード
     * 自身は変更されるが，引数rhsは変更されない
     * 計算量はO(1)である
     * @param rhs 乗算するModIntを指定する引数
     * @return 乗算後の自身を返す
     */
    constexpr ModInt& operator*=(const ModInt& rhs) noexcept {
        val_ = val_ * rhs.val_ % MOD;
        return *this;
    }
    
    /**
     * ModIntからModIntを除算代入する/=演算子のオーバーロード
     * フェルマーの小定理a^(MOD-2) \equiv a^{-1} (mod MOD)を利用し，自身にrhs^(MOD-2)を乗算することで除算を実装する
     * 自身は変更されるが，引数rhsは変更されない
     * 計算量はO(log(MOD))である
     * @param rhs 除算するModIntを指定する引数
     * @return 除算後の自身を返す
     */
    constexpr ModInt& operator/=(const ModInt& rhs) noexcept {
        ModInt r = rhs;
        for (long long x = MOD - 2; x > 0; x >>= 1) {
            if (x & 1) *this *= r;
            r *= r;
        }
        return *this;
    }
    
    /**
     * ModIntをModIntで累乗代入する^=演算子のオーバーロード
     * 自身は変更されるが，引数rhsは変更されない
     * 計算量はO(log(rhs))である
     * @param rhs 累乗するModIntを指定する引数
     * @return 累乗代入後の自身を返す
     */
    constexpr ModInt& operator^=(const ModInt& rhs) noexcept {
        ModInt temp = *this;
        *this = 1;
        for (long long y = rhs.val_; y > 0; y >>= 1) {
            if (y & 1) *this *= temp;
            temp *= temp;
        }
        return *this;
    }
    
    /**
     * ModInt同士の等価比較を行う==演算子のオーバーロード
     * 計算量はO(1)である
     * @param rhs 比較するModIntを指定する引数
     * @return 等価な場合true，それ以外はfalseを返す
     */
    constexpr bool operator==(const ModInt& rhs) const noexcept { return val_ == rhs.val_; }
    
    /**
     * ModInt同士の大小比較を行う<演算子のオーバーロード
     * 計算量はO(1)である
     * @param rhs 比較するModIntを指定する引数
     * @return 自身の値がrhsの値より小さい場合true，それ以外はfalseを返す
     */
    constexpr bool operator<(const ModInt& rhs) const noexcept { return val_ < rhs.val_; }
    
    /**
     * ModInt同士の非等価比較を行う!=演算子のオーバーロード
     * ==演算子の否定として実装する
     * 計算量はO(1)である
     * @param rhs 比較するModIntを指定する引数
     * @return 非等価な場合true，それ以外はfalseを返す
     */
    constexpr bool operator!=(const ModInt& rhs) const noexcept { return ! (*this == rhs); }
    
    /**
     * ModInt同士の大小比較を行う<=演算子のオーバーロード
     * <演算子と==演算子の論理和として実装する
     * 計算量はO(1)である
     * @param rhs 比較するModIntを指定する引数
     * @return 自身の値がrhsの値以下の場合true，それ以外はfalseを返す
     */
    constexpr bool operator<=(const ModInt& rhs) const noexcept { return (*this < rhs) || (*this == rhs); }
    
    /**
     * ModInt同士の大小比較を行う>=演算子のオーバーロード
     * <演算子の否定として実装する
     * 計算量はO(1)である
     * @param rhs 比較するModIntを指定する引数
     * @return 自身の値がrhsの値以上の場合true，それ以外はfalseを返す
     */
    constexpr bool operator>=(const ModInt& rhs) const noexcept {return ! (*this < rhs); }
    
    /**
     * ModInt同士の大小比較を行う>演算子のオーバーロード
     * <演算子の否定と==演算子の否定の論理積として実装する
     * 計算量はO(1)である
     * @param rhs 比較するModIntを指定する引数
     * @return 自身の値がrhsの値より大きい場合true，それ以外はfalseを返す
     */
    constexpr bool operator>(const ModInt& rhs) const noexcept { return (! (*this < rhs)) && (! (*this == rhs)); }
    
};

/**
 * long longとModIntの加算を行う+演算子のオーバーロード
 * ModInt(l) += rとして，+=演算子を呼び出して新しいModIntを返す
 * 2数の値は変更しない
 * 計算量はO(1)である
 * @param l 加算するlong longを指定する引数
 * @param r 加算するModIntを指定する引数
 * @return 加算の結果を返す
 */
template <long long MOD>
constexpr ModInt<MOD> operator+(long long l, const ModInt<MOD>& r) noexcept { return ModInt<MOD>(l) += r; }

/**
 * long longとModIntの減算を行う-演算子のオーバーロード
 * ModInt(l) -= rとして，-=演算子を呼び出して新しいModIntを返す
 * 2数の値は変更しない
 * 計算量はO(1)である
 * @param l 減算するlong longを指定する引数
 * @param r 減算するModIntを指定する引数
 * @return 減算の結果を返す
 */
template <long long MOD>
constexpr ModInt<MOD> operator-(long long l, const ModInt<MOD>& r) noexcept { return ModInt<MOD>(l) -= r; }

/**
 * long longとModIntの乗算を行う*演算子のオーバーロード
 * ModInt(l) *= rとして，*=演算子を呼び出して新しいModIntを返す
 * 2数の値は変更しない
 * 計算量はO(1)である
 * @param l 乗算するlong longを指定する引数
 * @param r 乗算するModIntを指定する引数
 * @return 乗算の結果を返す
 */
template <long long MOD>
constexpr ModInt<MOD> operator*(long long l, const ModInt<MOD>& r) noexcept { return ModInt<MOD>(l) *= r; }

/**
 * long longとModIntの除算を行う/演算子のオーバーロード
 * ModInt(l) /= rとして，/=演算子を呼び出して新しいModIntを返す
 * 2数の値は変更しない
 * 計算量はO(log(MOD))である
 * @param l 除算するlong longを指定する引数
 * @param r 除算するModIntを指定する引数
 * @return 除算の結果を返す
 */
template <long long MOD>
constexpr ModInt<MOD> operator/(long long l, const ModInt<MOD>& r) noexcept { return ModInt<MOD>(l) /= r; }

/**
 * long longとModIntの累乗を行う^演算子のオーバーロード
 * ModInt(l) ^= rとして，^=演算子を呼び出して新しいModIntを返す
 * 2数の値は変更しない
 * 計算量はO(log(r))である
 * @param l 累乗するlong longを指定する引数
 * @param r 累乗するModIntを指定する引数
 * @return 累乗の結果を返す
 */
template <long long MOD>
constexpr ModInt<MOD> operator^(long long l, const ModInt<MOD>& r) noexcept { return ModInt<MOD>(l) ^= r; }

/**
 * long longとModIntの等価比較を行う==演算子のオーバーロード
 * ModInt(l) == rとして，ModIntに変換して比較を行う
 * 計算量はO(1)である
 * @param l 比較するlong longを指定する引数
 * @param r 比較するModIntを指定する引数
 * @return 等価な場合true，それ以外はfalseを返す
 */
template <long long MOD>
constexpr bool operator==(long long l, const ModInt<MOD> &r) noexcept { return ModInt<MOD>(l) == r; }

/**
 * long longとModIntの非等価比較を行う!=演算子のオーバーロード
 * ModInt(l) != rとして，ModIntに変換して比較を行う
 * 計算量はO(1)である
 * @param l 比較するlong longを指定する引数
 * @param r 比較するModIntを指定する引数
 * @return 非等価な場合true，それ以外はfalseを返す
 */
template <long long MOD>
constexpr bool operator!=(long long l, const ModInt<MOD> &r) noexcept {return ModInt<MOD>(l) != r; }

/**
 * long longとModIntの大小比較を行う<演算子のオーバーロード
 * ModInt(l) < rとして，ModIntに変換して比較を行う
 * 計算量はO(1)である
 * @param l 比較するlong longを指定する引数
 * @param r 比較するModIntを指定する引数
 * @return lがrより小さい場合true，それ以外はfalseを返す
 */
template <long long MOD>
constexpr bool operator<(long long l, const ModInt<MOD> &r) noexcept { return ModInt<MOD>(l) < r; }

/**
 * long longとModIntの大小比較を行う<=演算子のオーバーロード
 * ModInt(l) <= rとして，ModIntに変換して比較を行う
 * 計算量はO(1)である
 * @param l 比較するlong longを指定する引数
 * @param r 比較するModIntを指定する引数
 * @return lがr以下の場合true，それ以外はfalseを返す
 */
template <long long MOD>
constexpr bool operator<=(long long l, const ModInt<MOD> &r) noexcept { return ModInt<MOD>(l) <= r; }

/**
 * long longとModIntの大小比較を行う>演算子のオーバーロード
 * ModInt(l) > rとして，ModIntに変換して比較を行う
 * 計算量はO(1)である
 * @param l 比較するlong longを指定する引数
 * @param r 比較するModIntを指定する引数
 * @return lがrより大きい場合true，それ以外はfalseを返す
 */
template <long long MOD>
constexpr bool operator>(long long l, const ModInt<MOD> &r) noexcept { return ModInt<MOD>(l) > r; }

/**
 * long longとModIntの大小比較を行う>=演算子のオーバーロード
 * ModInt(l) >= rとして，ModIntに変換して比較を行う
 * 計算量はO(1)である
 * @param l 比較するlong longを指定する引数
 * @param r 比較するModIntを指定する引数
 * @return lがr以上の場合true，それ以外はfalseを返す
 */
template <long long MOD>
constexpr bool operator>=(long long l, const ModInt<MOD> &r) noexcept { return ModInt<MOD>(l) >= r; }

/**
 * ModIntを入力するための，std::istream&とModInt&を引数とする>>演算子のオーバーロード
 * isからlong long型の値を読み取ってModIntに変換し，rに代入する
 * @param is 入力ストリームを指定する引数
 * @param r 入力した値を格納するModIntを指定する引数
 * @return 入力ストリームisを返す
 */
template <long long MOD>
std::istream& operator>>(std::istream& is, ModInt<MOD>& r) noexcept {
    long long x; is >> x;
    r = ModInt<MOD>(x);
    return is;
}

/**
 * ModIntを出力するための，std::ostream&とconst ModInt&を引数とする<<演算子のオーバーロード
 * r.value()の値をosに出力する
 * @param os 出力ストリームを指定する引数
 * @param r 出力するModIntを指定する引数
 * @return 出力ストリームosを返す
 */
template <long long MOD>
std::ostream& operator<<(std::ostream& os, const ModInt<MOD>& r) noexcept {
    return os << r.value();
}


constexpr long long MOD = 998'244'353;
//constexpr long long MOD = 1'000'000'007;
using mint = ModInt<MOD>;


int main() {
    // 入力
    mint A, B; std::cin >> A >> B;
    // 値の取得
    long long A_val = A.value();  // O(1)
    // 四則演算と累乗
    mint A_plus_B  = A + B;  // O(1)
    mint A_minus_B = A - B;  // O(1)
    mint A_times_B = A * B;  // O(1)
    mint A_div_B   = A / B;  // O(log(MOD))
    mint A_pow_B   = A ^ B;  // O(log(B))
    // 逆数
    mint A_inv = A.inv();  // O(log(MOD))
    // 比較
    bool A_eq_B  = A == B;  // O(1)
    bool A_neq_B = A != B;  // O(1)
    bool A_lt_B  = A < B;   // O(1)
    bool A_le_B  = A <= B;  // O(1)
    bool A_gt_B  = A > B;   // O(1)
    bool A_ge_B  = A >= B;  // O(1)
    // 出力
    std::cout << A << ' ' << B << '\n';
}