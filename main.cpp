#include <bits/stdc++.h>

// =============================================================================
// 入出力高速化
// =============================================================================

void inout_sync() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}


// =============================================================================
// 入力
// =============================================================================

// 可変長汎用入力関数
void in_impl () {}

template <typename T, typename... TS>
void in_impl (T& head, TS&... tail) {
    std::cin >> head;
    in_impl(tail ...);
}

// 可変長汎用入力マクロ
#define IN(T, ...) T __VA_ARGS__; in_impl(__VA_ARGS__)

// pair<T1,T2>の入力
template <typename T1, typename T2>
std::istream& operator>> (std::istream& is, std::pair<T1, T2>& p) {
    is >> p.first >> p.second;
    return is;
}

// vector<T>の入力
template <typename T>
std::istream& operator>> (std::istream& is, std::vector<T>& v) {
    for (auto&& vi : v) is >> vi;
    return is;
}


// =============================================================================
// 出力
// =============================================================================

// pair<T1,T2>の出力
template <typename T1, typename T2>
std::ostream& operator<< (std::ostream& os, const std::pair<T1, T2>& p) {
    os << p.first << ' ' << p.second;
    return os;
}

// vector<T>の出力
template <typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& v) {
    for (int i = 0, s = v.size(); i < s; ++i) {
        if (i) os << ' ';
        os << v[i];
    }
    return os;
}

// set<T>の出力
template <typename T>
std::ostream& operator<< (std::ostream& os, const std::set<T>& st) {
    auto itr = st.begin();
    int n = st.size();
    for (int i = 0; i < n; ++i, ++itr) {
        if (i) os << ' ';
        os << (*itr);
    }
    return os;
}

// multiset<T>の出力
template <typename T>
std::ostream& operator<< (std::ostream& os, const std::multiset<T>& st) {
    auto itr = st.begin();
    int n = st.size();
    for (int i = 0; i < n; ++i, ++itr) {
        if (i) os << ' ';
        os << (*itr);
    }
    return os;
}

// unordered_set<T>の出力
template <typename T>
std::ostream& operator<< (std::ostream& os, const std::unordered_set<T>& st) {
    auto itr = st.begin();
    int n = st.size();
    for (int i = 0; i < n; ++i, ++itr) {
        if (i) os << ' ';
        os << (*itr);
    }
    return os;
}

// map<Key,Val>の出力
template <typename Key, typename Val>
std::ostream& operator<< (std::ostream& os, const std::map<Key, Val>& mp) {
    auto itr = mp.begin();
    int n = mp.size();
    for (int i = 0; i < n; ++i, ++itr) {
        if (i) os << ' ';
        auto [key, val] = *itr;
        os << key << ':' << val;
    }
    return os;
}

// unordered_map<Key,Val>の出力
template <typename Key, typename Val>
std::ostream& operator<< (std::ostream& os, const std::unordered_map<Key, Val>& mp) {
    auto itr = mp.begin();
    int n = mp.size();
    for (int i = 0; i < n; ++i, ++itr) {
        if (i) os << ' ';
        auto [key, val] = *itr;
        os << key << ':' << val;
    }
    return os;
}


// =============================================================================
// ハッシュ（unordered_XXXで使用する）
// =============================================================================

// hashを組み合わせる関数
// 参考: pairをキーにしたstd::unordered_mapを手軽に使えるようにする (https://qiita.com/hamamu/items/4d081751b69aa3bb3557)
// 参考: boost::hash_combine（https://www.boost.org/doc/libs/1_55_0/doc/html/hash/reference.html#boost.hash_combine）
template <typename T>
size_t hash_combine (const size_t seed, const T& x) {
    return seed ^ (std::hash<T>()(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}

// pair用のhash
template <typename T1, typename T2>
struct std::hash<std::pair<T1, T2>> {
    size_t operator() (const std::pair<T1, T2>& p) const noexcept {
        size_t seed = 0;
        seed = hash_combine(seed, p.first);
        seed = hash_combine(seed, p.second);
        return seed;
    }
};

// tuple用のhash
template <int N>
struct HashTuple {
    template <typename Tuple>
    size_t operator() (const Tuple& tuple) const noexcept {
        size_t seed = HashTuple<N-1>()(tuple);
        return hash_combine(seed, std::get<N-1>(tuple));
    }
};
template <>
struct HashTuple<0> {
    template <typename Tuple>
    size_t operator() (const Tuple& tuple) const noexcept {
        return 0;
    }
};
template <typename... Args>
struct std::hash<std::tuple<Args...>> {
    size_t operator() (const std::tuple<Args...>& tuple) const noexcept {
        return HashTuple<std::tuple_size<std::tuple<Args...>>::value>()(tuple);
    }
};

// hackされないhash
// 参考: Blowing up unordered_map, and how to stop getting hacked on it (https://codeforces.com/blog/entry/62393)
template <typename T>
struct SafeHash {
    // 参考: splitmix64 (http://xorshift.di.unimi.it/splitmix64.c)
    static size_t splitmix64 (size_t x) noexcept {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    
    size_t operator() (const T& x) const noexcept {
        static const size_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(std::hash<T>()(x) + FIXED_RANDOM);
    }
};


// =============================================================================
// マクロ
// =============================================================================

// 反復
#define GET_REP(_1, _2, _3, NAME, ...) NAME
#define REP_2(i, N) for (int i = 0; i < (int)(N); ++i)
#define REP_3(i, A, B) for (int i = (A); i < (int)(B); ++i)
#define rep(...) GET_REP(__VA_ARGS__, REP_3, REP_2)(__VA_ARGS__)
#define RREP_2(i, N) for (int i = (int)(N)-1; i >= 0; --i)
#define RREP_3(i, A, B) for (int i = (int)(B)-1; i >= (int)(A); --i)
#define rrep(...) GET_REP(__VA_ARGS__, RREP_3, RREP_2)(__VA_ARGS__)

// イテレータ
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

// メンバ変数・関数
#define fst first
#define scd second
#define PB push_back
#define EB emplace_back

// 文字
#define el '\n'
#define spa ' '

// Yes, No
#define YES std::cout << "YES" << '\n'
#define NO std::cout << "NO" << '\n'
#define Yes std::cout << "Yes" << '\n'
#define No std::cout << "No" << '\n'
#define yes std::cout << "yes" << '\n'
#define no std::cout << "no" << '\n'
#define YESNO(b) std::cout << ((b) ? "YES" : "NO") << '\n'
#define YesNo(b) std::cout << ((b) ? "Yes" : "No") << '\n'
#define yesno(b) std::cout << ((b) ? "yes" : "no") << '\n'

// デバッグ
#define debug(x) std::cerr << #x << " = " << (x) << '\n'

// using宣言
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using vc = vector<char>;
using vvc = vector<vc>;
using vpii = vector<pii>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vpll = vector<pll>;

// 定数
constexpr int INF = std::numeric_limits<int>::max();
constexpr ll INFLL = std::numeric_limits<ll>::max();
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string abc = "abcdefghijklmnopqrstuvwxyz";
const vpii DX = {{-1,0},{1,0},{0,-1},{0,1}};


int main () {
    inout_sync();
    
}