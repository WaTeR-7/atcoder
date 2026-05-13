#include <bits/stdc++.h>


// プロトタイプ宣言
class Int128;
constexpr Int128 stoi128(const std::string& str) noexcept;

class Int128 {
  private:
    uint64_t hi_;  // 上位64ビットを保つ変数
    uint64_t lo_;  // 下位64ビットを保つ変数
    
    static constexpr uint64_t MASK_32 = static_cast<uint64_t>(std::numeric_limits<uint32_t>::max());  // 32ビットのマスク 111...111 (32個の1)
    
    /**
     * 64ビットの整数xの下位32ビットを取得するヘルパー関数
     */
    static inline constexpr uint64_t get_lower_32(uint64_t x) noexcept { return x & MASK_32; }
    
    /**
     * 64ビットの整数xの上位32ビットを取得するヘルパー関数
     */
    static inline constexpr uint64_t get_upper_32(uint64_t x) noexcept { return x >> 32; }
    
    /**
     * 上位32ビットupperと下位32ビットlowerを結合して64ビットの整数を作るヘルパー関数
     */
    static inline constexpr uint64_t combine_32(uint64_t upper, uint64_t lower) noexcept { return (upper << 32) | (lower & MASK_32); }
    
    /**
     * Int128の最上位ビットの位置を取得するヘルパー関数
     * 1桁目を0と数えるとき、最上位ビットの位置を返す
     * xが0でないことが前提
     * x.hi_が0でない場合は、x.hi_の最上位ビットの位置に64を加えた値を返す
     * x.hi_が0でx.lo_が0でない場合は、x.lo_の最上位ビットの位置を返す
     */
    static inline constexpr int get_msb(const Int128& x) noexcept {
        return x.hi_ != 0 ? 63 + std::bit_width(x.hi_) : std::bit_width(x.lo_) - 1;
    }
    
    /**
     * Int128が負の数かどうかを判定するヘルパー関数
     * Int128は符号付き整数として表現されているため、最上位ビットが1であれば負の数である
     */
    static inline constexpr bool is_negative(const Int128& x) noexcept { return (x.hi_ >> 63) != 0; }
    
    static inline constexpr std::pair<Int128,Int128> u_div_mod(const Int128& dividend, const Int128& divisor) noexcept {
        if (divisor == 0) return {0, 0};  // 0で割る動作は，商も余りも0を返しておく
        
        if (dividend.hi_ == 0 && divisor.hi_ == 0) {  // 両方とも64ビットで表せる場合は，単純にuint64_t同士の割り算を行う
            uint64_t q = dividend.lo_ / divisor.lo_;
            uint64_t r = dividend.lo_ % divisor.lo_;
            return {Int128(0, q), Int128(0, r)};
        }
        
        Int128 quotient = 0;
        Int128 remainder = 0;
        
        int msb = get_msb(dividend);
        for (int i = msb; i >= 0; --i) {
            remainder <<= 1;  // remainderを1ビット左シフトして、次のビットを受け入れるスペースを作る
            if ((dividend >> i) & 1) remainder |= 1;  // dividendのiビット目が1ならremainderの最下位ビットを1にする
            if (remainder >= divisor) {  // remainderがdivisor以上なら、商のiビット目を1にして、remainderからdivisorを引く
                quotient |= (Int128(1) << i);
                remainder -= divisor;
            }
        }
        
        return {quotient, remainder};
    }
    
  public:
    /**
     * Int128のコンストラクタ
     * 引数を指定しない場合は0になる
     * 計算量はO(1)である
     */
    constexpr Int128() noexcept : hi_(0), lo_(0) {}
    
    /**
     * Int128のコンストラクタ
     * 計算量はO(1)である
     * @param hi 上位64ビットを指定する引数
     * @param lo 下位64ビットを指定する引数
     */
    constexpr Int128(uint64_t hi, uint64_t lo) noexcept : hi_(hi), lo_(lo) {}
    
    /**
     * Int128のコンストラクタ
     * 計算量はO(1)である
     * @param x 初期値を指定する引数
     */
    constexpr Int128(long long x) noexcept {
        lo_ = static_cast<uint64_t>(x);
        hi_ = static_cast<uint64_t>(x < 0 ? ~0ULL : 0ULL);  // 負の値の場合は上位ビットを1で埋める
    }
    
    /**
     * Int128のコンストラクタ
     * 計算量はO(1)である
     * @param x 初期値を指定する引数
     */
    constexpr Int128(unsigned long long x) noexcept : hi_(0), lo_(static_cast<uint64_t>(x)) {}
    
    /**
     * Int128のコンストラクタ
     * 計算量はO(1)である
     * @param x 初期値を指定する引数
     */
    constexpr Int128(int x) noexcept : Int128(static_cast<long long>(x)) {}
    
    /**
     * Int128のコンストラクタ
     * 計算量はO(1)である
     * @param x 初期値を指定する引数
     */
    constexpr Int128(unsigned int x) noexcept : Int128(static_cast<unsigned long long>(x)) {}
    
    /**
     * bool型への型変換演算子のオーバーロード
     * Int128が0でない場合はtrue，0の場合はfalseを返す
     * 計算量はO(1)である
     */
    explicit constexpr operator bool() const noexcept { return hi_ != 0 || lo_ != 0; }
    
    /**
     * Int128の単項プラス演算子のオーバーロード
     * 計算量はO(1)である
     * @return 自身を返す
     */
    constexpr Int128 operator+() const noexcept { return *this; }
    
    /**
     * Int128の単項マイナス演算子のオーバーロード
     * 計算量はO(1)である
     * @return 自身の符号を反転させたInt128を返す
     */
    constexpr Int128 operator-() const noexcept {
        return ~(*this) + 1;  // ビット反転して1を加えることで2の補数を取る
    }
    
    /**
     * Int128をInt128で加算代入する+=演算子のオーバーロード
     * 自身は変更されるが，引数rhsは変更されない
     * 計算量はO(1)である
     * @param rhs 加算するInt128を指定する引数
     * @return 加算代入後の自身を返す
     */
    constexpr Int128& operator+=(const Int128& rhs) noexcept {
        uint64_t old_lo = lo_;
        lo_ += rhs.lo_;
        hi_ += rhs.hi_ + static_cast<uint64_t>(lo_ < old_lo ? 1 : 0);  // 下位ビットの加算でオーバーフローが発生した場合は上位ビットに1を加える
        return *this;
    }
    
    /**
     * Int128をInt128で減算代入する-=演算子のオーバーロード
     * 自身は変更されるが，引数rhsは変更されない
     * 計算量はO(1)である
     * @param rhs 減算するInt128を指定する引数
     * @return 減算代入後の自身を返す
     */
    constexpr Int128& operator-=(const Int128& rhs) noexcept {
        uint64_t old_lo = lo_;
        lo_ -= rhs.lo_;
        hi_ -= rhs.hi_ + static_cast<uint64_t>(lo_ > old_lo ? 1 : 0);  // 下位ビットの減算でアンダーフローが発生した場合は上位ビットから1を借りる
        return *this;
    }
    
    /**
     * Int128をInt128で乗算代入する*=演算子のオーバーロード
     * 自身は変更されるが，引数rhsは変更されない
     * 計算量はO(1)である
     * @param rhs 乗算するInt128を指定する引数
     * @return 乗算代入後の自身を返す
     */
    constexpr Int128& operator*=(const Int128& rhs) noexcept {
        // |------------------ this (128) -----------------|   |------------------- rhs (128) -----------------|
        // |------ hi_ (64) -------|------ lo_ (64) -------| X |------ hi_ (64) -------|------ lo_ (64) -------|
        // |------ hi_ (64) -------|- a1 (32) -|- a0 (32) -|   |------ hi_ (64) -------|- b1 (32) -|- b0 (32) -|
        //
        //   (hi_ * 2^64 + lo_) * (rhs.hi_ * 2^64 + rhs.lo_)
        // = hi_ * rhs.hi_ * 2^128 + (hi_ * rhs.lo_ + lo_ * rhs.hi_) * 2^64 + lo_ * rhs.lo_
        // = hi_ * rhs.hi_ * 2^128 + (hi_ * rhs.lo_ + lo_ * rhs.hi_) * 2^64 + (a1 * 2^32 + a0) * (b1 * 2^32 + b0)
        // = hi_ * rhs.hi_ * 2^128 + (hi_ * rhs.lo_ + lo_ * rhs.hi_) * 2^64 + a1 * b1 * 2^64 + (a1 * b0 + a0 * b1) * 2^32 + a0 * b0
        // = hi_ * rhs.hi_ * 2^128 + (hi_ * rhs.lo_ + lo_ * rhs.hi_ + a1 * b1) * 2^64 + (a1 * b0 + a0 * b1) * 2^32 + a0 * b0
        
        // lo_を上下32ビットずつに分割
        uint64_t a0 = get_lower_32(lo_);
        uint64_t a1 = get_upper_32(lo_);
        uint64_t b0 = get_lower_32(rhs.lo_);
        uint64_t b1 = get_upper_32(rhs.lo_);
        
        // 繰り上がり前の各位を計算
        uint64_t t2 = hi_ * rhs.lo_ + lo_ * rhs.hi_ + a1 * b1;
        uint64_t t1 = a1 * b0 + a0 * b1;
        uint64_t t0 = a0 * b0;
        
        // 繰り上がりを処理
        uint64_t c0 = get_lower_32(t0);
        t1 += get_upper_32(t0);  // t0の繰り上がり
        uint64_t c1 = get_lower_32(t1);
        uint64_t c2 = t2 + get_upper_32(t1);  // t1の繰り上がり
        
        // 結果を格納
        lo_ = combine_32(c1, c0);
        hi_ = c2;
        
        return *this;
    }
    
    /**
     * Int128をInt128で除算代入する/=演算子のオーバーロード
     * 自身は変更されるが，引数rhsは変更されない
     * 計算量はO(log|X|)である
     * @param rhs 除算するInt128を指定する引数
     * @return 除算代入後の自身を返す
     */
    constexpr Int128& operator/=(const Int128& rhs) noexcept {
        Int128 dividend = *this;
        Int128 divisor = rhs;
        
        // 負数のときは正数に変換する
        bool is_dividend_negative = is_negative(dividend);
        bool is_divisor_negative = is_negative(divisor);
        if (is_dividend_negative) dividend = -dividend;
        if (is_divisor_negative) divisor = -divisor;
        
        // 商と剰余を計算する
        auto [q, r] = u_div_mod(*this, rhs);
        
        // 商の符号を調整する
        if (is_dividend_negative != is_divisor_negative) q = -q;
        
        // 商を自身に代入して返す
        return *this = q;
    }
    
    /**
     * Int128をInt128で剰余代入する%=演算子のオーバーロード
     * 自身は変更されるが，引数rhsは変更されない
     * 計算量はO(log|X|)である
     * @param rhs 剰余を求めるInt128を指定する引数
     * @return 剰余代入後の自身を返す
     */
    constexpr Int128& operator%=(const Int128& rhs) noexcept {
        Int128 dividend = *this;
        Int128 divisor = rhs;
        
        // 負数のときは正数に変換する
        bool is_dividend_negative = is_negative(dividend);
        bool is_divisor_negative = is_negative(divisor);
        if (is_dividend_negative) dividend = -dividend;
        if (is_divisor_negative) divisor = -divisor;
        
        // 商と剰余を計算する
        auto [q, r] = u_div_mod(*this, rhs);
        
        // 剰余の符号を調整する 剰余の符号は被除数と同じにする
        if (is_dividend_negative) r = -r;
        
        // 剰余を自身に代入して返す
        return *this = r;
    }
    
    /**
     * Int128をintで左シフトする<<=演算子のオーバーロード
     * 自身は変更される
     * 計算量はO(1)である
     * @param shift シフトするビット数を指定する引数
     * @return 左シフト後の自身を返す
     */
    constexpr Int128& operator<<=(int shift) noexcept {
        if (shift <= 0) return *this;  // シフト量が0以下の場合は何もしない
        
        if (shift >= 128) {  // シフト量が128以上の場合は全てのビットが0になる
            hi_ = 0;
            lo_ = 0;
        }
        else if (shift >= 64) {  // シフト量が64以上128未満の場合は下位ビットが全て0になり、上位ビットは下位ビットのシフト分だけ左に移動する
            hi_ = lo_ << (shift - 64);
            lo_ = 0;
        }
        else {  // シフト量が64未満の場合は上位ビットと下位ビットの両方がシフトされ，下位ビットのシフト分だけ上位ビットに繰り上がる
            hi_ = (hi_ << shift) | (lo_ >> (64 - shift));
            lo_ <<= shift;
        }
        
        return *this;
    }
    
    /**
     * Int128をintで右シフトする>>=演算子のオーバーロード
     * 自身は変更される
     * 計算量はO(1)である
     * @param shift シフトするビット数を指定する引数
     * @return 右シフト後の自身を返す
     */
    constexpr Int128& operator>>=(int shift) noexcept {
        if (shift <= 0) return *this;  // シフト量が0以下の場合は何もしない
        
        int64_t shi = static_cast<int64_t>(hi_);  // hi_を符号付き整数として扱うためにint64_tにキャスト
        uint64_t fill = (shi < 0) ? ~0ULL : 0ULL;  // hi_が負の数の場合は全てのビットが1になる値を、非負の数の場合は全てのビットが0になる値を用意
        
        if (shift >= 128) {  // シフト量が128以上の場合は，上下のビットをfillで埋める
            hi_ = fill;
            lo_ = fill;
        }
        else if (shift >= 64) {  // シフト量が64以上128未満の場合は上位ビットをfillで埋め、下位ビットは上位ビットのシフト分だけ右に移動する
            lo_ = hi_ >> (shift - 64);
            hi_ = fill;
        }
        else {  // シフト量が64未満の場合は上位ビットと下位ビットの両方がシフトされ，上位ビットのシフト分だけ下位ビットに繰り下がる
            lo_ = (lo_ >> shift) | (hi_ << (64 - shift));
            hi_ = static_cast<uint64_t>(shi >> shift);  // hi_を符号付き右シフトするためにshiをshiftだけ右シフトしてからuint64_tにキャスト
        }
        
        return *this;
    }
    
    /**
     * Int128をInt128でビットANDする&=演算子のオーバーロード
     * 自身は変更されるが，引数rhsは変更されない
     * 計算量はO(1)である
     * @param rhs ビットANDするInt128を指定する引数
     * @return ビットAND後の自身を返す
     */
    constexpr Int128& operator&=(const Int128& rhs) noexcept {
        hi_ &= rhs.hi_;
        lo_ &= rhs.lo_;
        return *this;
    }
    
    /**
     * Int128をInt128でビットORする|=演算子のオーバーロード
     * 自身は変更されるが，引数rhsは変更されない
     * 計算量はO(1)である
     * @param rhs ビットORするInt128を指定する引数
     * @return ビットOR後の自身を返す
     */
    constexpr Int128& operator|=(const Int128& rhs) noexcept {
        hi_ |= rhs.hi_;
        lo_ |= rhs.lo_;
        return *this;
    }
    
    /**
     * Int128をInt128でビットXORする^=演算子のオーバーロード
     * 自身は変更されるが，引数rhsは変更されない
     * 計算量はO(1)である
     * @param rhs ビットXORするInt128を指定する引数
     * @return ビットXOR後の自身を返す
     */
    constexpr Int128& operator^=(const Int128& rhs) noexcept {
        hi_ ^= rhs.hi_;
        lo_ ^= rhs.lo_;
        return *this;
    }
    
    /**
     * Int128同士の加算を行う+演算子のオーバーロード
     * Int128(*this) += rhsとして，+=演算子を呼び出して新しいInt128を返す
     * 2数の値は変更しない
     * 計算量はO(1)である
     * @param lhs 加算するInt128を指定する引数
     * @param rhs 加算するInt128を指定する引数
     * @return 加算の結果を返す
     */
    friend constexpr Int128 operator+(const Int128& lhs, const Int128& rhs) noexcept { return Int128(lhs) += rhs; }
    
    /**
     * Int128同士の減算を行う-演算子のオーバーロード
     * Int128(*this) -= rhsとして，-=演算子を呼び出して新しいInt128を返す
     * 2数の値は変更しない
     * 計算量はO(1)である
     * @param lhs 減算するInt128を指定する引数
     * @param rhs 減算するInt128を指定する引数
     * @return 減算の結果を返す
     */
    friend constexpr Int128 operator-(const Int128& lhs, const Int128& rhs) noexcept { return Int128(lhs) -= rhs; }
    
    /**
     * Int128同士の乗算を行う*演算子のオーバーロード
     * Int128(*this) *= rhsとして，*=演算子を呼び出して新しいInt128を返す
     * 2数の値は変更しない
     * 計算量はO(1)である
     * @param lhs 乗算するInt128を指定する引数
     * @param rhs 乗算するInt128を指定する引数
     * @return 乗算の結果を返す
     */
    friend constexpr Int128 operator*(const Int128& lhs, const Int128& rhs) noexcept { return Int128(lhs) *= rhs; }
    
    /**
     * Int128同士の除算を行う/演算子のオーバーロード
     * Int128(*this) /= rhsとして，/=演算子を呼び出して新しいInt128を返す
     * 2数の値は変更しない
     * 計算量はO(log|X|)である
     * @param lhs 除算するInt128を指定する引数
     * @param rhs 除算するInt128を指定する引数
     * @return 除算の結果を返す
     */
    friend constexpr Int128 operator/(const Int128& lhs, const Int128& rhs) noexcept { return Int128(lhs) /= rhs; }
    
    /**
     * Int128同士の剰余を行う%演算子のオーバーロード
     * Int128(*this) %= rhsとして，%=演算子を呼び出して新しいInt128を返す
     * 2数の値は変更しない
     * 計算量はO(log|X|)である
     * @param lhs 剰余を取るInt128を指定する引数
     * @param rhs 剰余を取るInt128を指定する引数
     * @return 剰余の結果を返す
     */
    friend constexpr Int128 operator%(const Int128& lhs, const Int128& rhs) noexcept { return Int128(lhs) %= rhs; }
    
    /**
     * Int128をintで左シフトする<<演算子のオーバーロード
     * Int128(*this) <<= shiftとして，<<=演算子を呼び出して新しいInt128を返す
     * 2数の値は変更しない
     * 計算量はO(1)である
     * @param lhs 左シフトするInt128を指定する引数
     * @param shift シフトするビット数を指定する引数
     * @return 左シフトの結果を返す
     */
    friend constexpr Int128 operator<<(const Int128& lhs, int shift) noexcept { return Int128(lhs) <<= shift; }
    
    /**
     * Int128をintで右シフトする>>演算子のオーバーロード
     * Int128(*this) >>= shiftとして，>>=演算子を呼び出して新しいInt128を返す
     * 2数の値は変更しない
     * 計算量はO(1)である
     * @param lhs 右シフトするInt128を指定する引数
     * @param shift シフトするビット数を指定する引数
     * @return 右シフトの結果を返す
     */
    friend constexpr Int128 operator>>(const Int128& lhs, int shift) noexcept { return Int128(lhs) >>= shift; }
    
    /**
     * Int128同士のビットANDを行う&演算子のオーバーロード
     * Int128(*this) &= rhsとして，&=演算子を呼び出して新しいInt128を返す
     * 2数の値は変更しない
     * 計算量はO(1)である
     * @param lhs ビットANDするInt128を指定する引数
     * @param rhs ビットANDするInt128を指定する引数
     * @return ビットANDの結果を返す
     */
    friend constexpr Int128 operator&(const Int128& lhs, const Int128& rhs) noexcept { return Int128(lhs) &= rhs; }
    
    /**
     * Int128同士のビットORを行う|演算子のオーバーロード
     * Int128(*this) |= rhsとして，|=演算子を呼び出して新しいInt128を返す
     * 2数の値は変更しない
     * 計算量はO(1)である
     * @param lhs ビットORするInt128を指定する引数
     * @param rhs ビットORするInt128を指定する引数
     * @return ビットORの結果を返す
     */
    friend constexpr Int128 operator|(const Int128& lhs, const Int128& rhs) noexcept { return Int128(lhs) |= rhs; }

    /**
     * Int128同士のビットXORを行う^演算子のオーバーロード
     * Int128(*this) ^= rhsとして，^=演算子を呼び出して新しいInt128を返す
     * 2数の値は変更しない
     * 計算量はO(1)である
     * @param lhs ビットXORするInt128を指定する引数
     * @param rhs ビットXORするInt128を指定する引数
     * @return ビットXORの結果を返す
     */
    friend constexpr Int128 operator^(const Int128& lhs, const Int128& rhs) noexcept { return Int128(lhs) ^= rhs; }
    
    /**
     * Int128のビット反転を行う~演算子のオーバーロード
     * 上下のビットをそれぞれ反転させたInt128を返す
     * 値は変更しない
     * 計算量はO(1)である
     * @return ビット反転の結果を返す
     */
    constexpr Int128 operator~() const noexcept { return Int128(~hi_, ~lo_); }

    /**
     * Int128の前置インクリメントを行う++演算子のオーバーロード
     * 自身を1加算してから自身を返す
     * 計算量はO(1)である
     * @return インクリメント後の自身を返す
     */
    constexpr Int128& operator++() noexcept { return *this += Int128(1); }
    
    /**
     * Int128の後置インクリメントを行う++演算子のオーバーロード
     * インクリメント前の自身をtmpに保存してから自身を1加算し，tmpを返す
     * 計算量はO(1)である
     * @return インクリメント前の自身のコピーを返す
     */
    constexpr Int128 operator++(int) noexcept { Int128 tmp = *this; ++(*this); return tmp; }
    
    /**
     * Int128の前置デクリメントを行う--演算子のオーバーロード
     * 自身を1減算してから自身を返す
     * 計算量はO(1)である
     * @return デクリメント後の自身を返す
     */
    constexpr Int128& operator--() noexcept { return *this -= Int128(1); }
    
    /**
     * Int128の後置デクリメントを行う--演算子のオーバーロード
     * デクリメント前の自身をtmpに保存してから自身を1減算し，tmpを返す
     * 計算量はO(1)である
     * @return デクリメント前の自身のコピーを返す
     */
    constexpr Int128 operator--(int) noexcept { Int128 tmp = *this; --(*this); return tmp; }
    
    /**
     * Int128同士の等価比較を行う==演算子のオーバーロード
     * 2数の上位ビットと下位ビットが両方等しい場合にtrueを返し、そうでない場合はfalseを返す
     * 計算量はO(1)である
     * @param lhs 比較するInt128を指定する引数
     * @param rhs 比較するInt128を指定する引数
     * @return 等価な場合true，それ以外はfalseを返す
     */
    friend constexpr bool operator==(const Int128& lhs, const Int128& rhs) noexcept { return lhs.hi_ == rhs.hi_ && lhs.lo_ == rhs.lo_; }
    
    /**
     * Int128同士の非等価比較を行う!=演算子のオーバーロード
     * ==演算子の否定として実装する
     * 計算量はO(1)である
     * @param lhs 比較するInt128を指定する引数
     * @param rhs 比較するInt128を指定する引数
     * @return 非等価な場合true，それ以外はfalseを返す
     */
    friend constexpr bool operator!=(const Int128& lhs, const Int128& rhs) noexcept { return ! (lhs == rhs); }
    
    /**
     * Int128同士の大小比較を行う<演算子のオーバーロード
     * 上位ビットが異なる場合は上位ビットの大小で比較し、上位ビットが等しい場合は符号を考慮して下位ビットの大小で比較する
     * 計算量はO(1)である
     * @param lhs 比較するInt128を指定する引数
     * @param rhs 比較するInt128を指定する引数
     * @return lhsの値がrhsの値より小さい場合true，それ以外はfalseを返す
     */
    friend constexpr bool operator<(const Int128& lhs, const Int128& rhs) noexcept {
        int64_t l_shi = static_cast<int64_t>(lhs.hi_);
        int64_t r_shi = static_cast<int64_t>(rhs.hi_);
        if (l_shi != r_shi) return l_shi < r_shi;  // 上位ビットが異なる場合は上位ビットの大小で比較
        if (l_shi < 0) return lhs.lo_ > rhs.lo_;  // 上位ビットが等しく負の数の場合は下位ビットを逆に比較
        return lhs.lo_ < rhs.lo_;  // 上位ビットが等しく非負の数の場合は下位ビットをそのまま比較
    }
    
    /**
     * Int128同士の大小比較を行う<=演算子のオーバーロード
     * <演算子と==演算子の論理和として実装する
     * 計算量はO(1)である
     * @param lhs 比較するInt128を指定する引数
     * @param rhs 比較するInt128を指定する引数
     * @return lhsの値がrhsの値以下の場合true，それ以外はfalseを返す
     */
    friend constexpr bool operator<=(const Int128& lhs, const Int128& rhs) noexcept { return (lhs < rhs) || (lhs == rhs); }
    
    /**
     * Int128同士の大小比較を行う>=演算子のオーバーロード
     * <演算子の否定として実装する
     * 計算量はO(1)である
     * @param lhs 比較するInt128を指定する引数
     * @param rhs 比較するInt128を指定する引数
     * @return lhsの値がrhsの値以上の場合true，それ以外はfalseを返す
     */
    friend constexpr bool operator>=(const Int128& lhs, const Int128& rhs) noexcept { return ! (lhs < rhs); }
    
    /**
     * Int128同士の大小比較を行う>演算子のオーバーロード
     * <演算子の否定と==演算子の否定の論理積として実装する
     * 計算量はO(1)である
     * @param lhs 比較するInt128を指定する引数
     * @param rhs 比較するInt128を指定する引数
     * @return lhsの値がrhsの値より大きい場合true，それ以外はfalseを返す
     */
    friend constexpr bool operator>(const Int128& lhs, const Int128& rhs) noexcept { return (! (lhs < rhs)) && (! (lhs == rhs)); }
    
    /**
     * Int128を文字列に変換するto_string関数のオーバーロード
     * Int128の値を10進数の文字列に変換する
     * 計算量はO(log|x|)である
     * @param x 変換するInt128を指定する引数
     * @return Int128を10進数の文字列に変換した結果を返す
     */
    friend constexpr std::string to_string(const Int128& x) noexcept {
        if (x == 0) return "0";
        
        std::string str;
        
        // 符号を処理し，正の値にする
        Int128 y = x;
        bool is_negative = false;
        if (x < 0) {
            is_negative = true;
            y = -x;
        }
        
        // 10で割り続けて桁を取得していく
        while (y > 0) {
            Int128 digit = y % 10;
            str += static_cast<char>(digit.lo_ + '0');
            y /= 10;
        }
        
        // 符号を追加して桁を逆順にする
        if (is_negative) {
            str += '-';
        }
        std::reverse(str.begin(), str.end());
        
        return str;
    }
    
    /**
     * Int128を入力するための>>演算子のオーバーロード
     * 文字列として入力を受け取り、符号と桁を解析してInt128に変換する
     * 計算量はO(|S|)である
     * @param is 入力ストリームを指定する引数
     * @param x 入力された値を格納するInt128を指定する引数
     * @return 入力ストリームを返す
     */
    friend std::istream& operator>>(std::istream& is, Int128& x) noexcept {
        std::string str; is >> str;
        x = stoi128(str);
        return is;
    }
    
    /**
     * Int128を出力するための<<演算子のオーバーロード
     * Int128を10進数の文字列に変換して出力する
     * 計算量はO(log|x|)である
     * @param os 出力ストリームを指定する引数
     * @param x 出力するInt128を指定する引数
     * @return 出力ストリームを返す
     */
    friend std::ostream& operator<<(std::ostream& os, const Int128& x) noexcept {
        return os << to_string(x);
    }
};

/**
 * 文字列リテラルをInt128に変換するユーザー定義リテラルのオーバーロード
 * 文字列の先頭に符号がある場合は符号を考慮して変換する
 * 文字列が空の場合は0を返す
 * 計算量はO(|S|)である
 * @param c_ptr 変換する文字列の先頭を指すポインタを指定する引数
 * @param len 変換する文字列の長さを指定する引数
 * @return 文字列をInt128に変換した結果を返す
 */
constexpr Int128 operator"" _i128(const char* c_ptr, size_t len) noexcept {
    Int128 x = 0;
    std::string str(c_ptr, len);
    x = stoi128(str);
    return x;
}

/**
 * 文字列strをInt128に変換する関数
 * 文字列の先頭に符号がある場合は符号を考慮して変換する
 * 文字列が空の場合は0を返す
 * 計算量はO(|S|)である
 * @param str 変換する文字列を指定する引数
 * @return 文字列をInt128に変換した結果を返す
 */
constexpr Int128 stoi128(const std::string& str) noexcept{
    Int128 x = 0;
    
    if (str.empty()) return x;
    
    // 先頭に符号があるか確認
    int idx = 0;
    bool is_negative = false;
    if (str[0] == '-') {
        idx = 1;
        is_negative = true;
    }
    
    // 1桁ずつ処理していく
    int n = str.size();
    for (; idx < n; ++idx) {
        x = x * 10 + (str[idx] - '0');
    }
    
    // 符号を反映
    if (is_negative) {
        x = -x;
    }
    
    return x;
}


#ifdef LOCAL_USE

int main () {
    // Int128の使用例
    // 初期化
    Int128 a;  // 引数なしでは0で初期化される
    Int128 b = "-12345678901234567890"_i128;  // 文字列リテラルからInt128を初期化 O(|S|)
    Int128 c = 12345678901234567890ULL;  // unsigned long longからInt128を初期化 O(1)
    Int128 d = 1234567890;  // intからInt128を初期化 O(1)
    // 入力
    std::cin >> a;  // 標準入力からInt128を読み込む O(|S|)
    // 演算
    Int128 a_plus_b = a + b;  // Int128同士の加算 O(1)
    Int128 a_minus_b = a - b;  // Int128同士の減算 O(1)
    Int128 a_times_b = a * b;  // Int128同士の乗算 O(1)
    Int128 a_div_b = a / b;  // Int128同士の除算 O(log|X|)
    Int128 a_mod_b = a % b;  // Int128同士の剰余 O(log|X|)
    Int128 a_shift_left = a << 10;  // Int128をintで左シフト O(1)
    Int128 a_shift_right = a >> 10;  // Int128同士のビット演算 O(1)
    Int128 a_and_b = a & b;  // Int128同士のビットAND O(1)
    Int128 a_or_b = a | b;  // Int128同士のビットOR O(1)
    Int128 a_xor_b = a ^ b;  // Int128同士のビットXOR O(1)
    Int128 a_not = ~a;  // Int128のビット反転 O(1)
    Int128 a_neg = -a;  // Int128の符号反転 O(1)
    // 比較
    bool a_eq_b = (a == b);  // Int128同士の等価比較 O(1)
    bool a_ne_b = (a != b);  // Int128同士の非等価比較 O(1)
    bool a_lt_b = (a < b);  // Int128同士の大小比較 O(1)
    bool a_le_b = (a <= b);  // Int128同士の大小比較 O(1)
    bool a_gt_b = (a > b);  // Int128同士の大小比較 O(1)
    bool a_ge_b = (a >= b);  // Int128同士の大小比較 O(1)
    // 出力
    std::cout << "a: " << a << std::endl;  // Int128を標準出力に出力する O(log|X|)
    // 文字列との変換
    std::string a_str = to_string(a);  // Int128を文字列に変換する O(log|X|)
    Int128 a_from_str = stoi128(a_str);  // 文字列をInt128に変換する O(|S|)
}

#endif