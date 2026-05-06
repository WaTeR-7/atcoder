#include <bits/stdc++.h>


/**
 * 配列の最大公約数を求める
 * @param v 最大公約数を計算する空でない配列
 * @return 配列の最大公約数
 */
int gcd(const std::vector<int>& v) {
    assert(v.size() > 0);
    return std::accumulate(v.begin()+1, v.end(), v[0], [](int a, int b){ return std::gcd(a, b); });
}


/**
 * 配列の最大公約数を求める
 * long longのオーバーロード版
 * @param v 最大公約数を計算する空でない配列
 * @return 配列の最大公約数
 */
long long gcd(const std::vector<long long>& v) {
    assert(v.size() > 0);
    return std::accumulate(v.begin()+1, v.end(), v[0], [](long long a, long long b){ return std::gcd(a, b); });
}
