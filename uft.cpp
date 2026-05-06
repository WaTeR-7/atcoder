#include <bits/stdc++.h>


/**
 * 要素が属するグループの結合，所属判定を高速に行うことができるデータ構造
 */
class UnionFindTree {
  private:
    int n_;
    std::vector<int> root_, rank_;
    
  public:
    /**
     * UnionFindTreeのコンストラクタ
     * 1-indexedに対応するために，n+1で初期化する
     */
    UnionFindTree(int n) : n_(n+1), root_(n+1, -1), rank_(n+1) {}
    
    /**
     * あるノードの根となるノードの番号を求める
     * 計算量はO(a(N))である
     * @param x 根を求めるノードの番号
     * @return 求めた根の番号
     */
    int find_root(int x) {
        assert(0 <= x && x < n_);
        if (root_[x] < 0) return x;
        return root_[x] = find_root(root_[x]);
    }
    
    /**
     * 2つのノードを結合する
     * 計算量はO(a(N))である
     * @param x 結合する1つ目のノードの番号
     * @param y 結合する2つ目のノードの番号
     */
    void unite(int x, int y) {
        x = find_root(x);
        y = find_root(y);
        if (x == y) return;
        if (rank_[x] == rank_[y]) ++rank_[x];
        else if (rank_[x] < rank_[y]) std::swap(x, y);
        root_[x] += root_[y];
        root_[y] = x;
    }
    
    /**
     * 2つのノードが結合しているかどうか判定する
     * @param x 1つ目のノードの番号
     * @param y 2つ目のノードの番号
     * @return 2つのノードが結合しているならばtrueを返す
     */
    bool is_same(int x, int y) {
        return find_root(x) == find_root(y);
    }
};


using UFT = UnionFindTree;


int main() {
    int N; std::cin >> N;
    // 初期化
    UFT uft(N);
    // 結合
    for (int i = 0; i < 10; ++i) {
        int X, Y; std::cin >> X >> Y;
        uft.unite(X, Y);
    }
    // 同一か判定
    int A, B; std::cin >> A >> B;
    bool is_same = uft.is_same(A, B);
}