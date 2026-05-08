#include <bits/stdc++.h>


/**
 * 要素が属するグループの結合，所属判定を高速に行うことができるデータ構造
 * 0-indexedであることに注意する
 */
class UnionFindTree {
  private:
    int n_;  // ノードの数
    int cnt_groups_;  // グループの数
    /**
     * 根を管理する配列
     * root_[x] < 0のとき: ノードxは根であり，-root_[x]はノードxを根とするグループのサイズ
     * root_[x] >= 0のとき: ノードxはの根はroot_[x]である
     */
    std::vector<int> root_;
    std::vector<int> rank_;  // 木の高さを管理する配列
    
  public:
    /**
     * UnionFindTreeのコンストラクタ
     * 0-indexedであることに注意する
     */
    UnionFindTree(int n) : n_(n), cnt_groups_(n), root_(n, -1), rank_(n) {}
    
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
        --cnt_groups_;
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
    
    /**
     * 指定されたノードを含むグループのサイズを取得する
     * 計算量はO(a(N))である
     * @param x ノードの番号
     * @return グループのサイズ
     */
    int size_of(int x) {
        return -root_[find_root(x)];
    }
    
    /**
     * グループの数を取得する
     * 計算量はO(1)である
     * @return グループの数
     */
    int count_groups() const {
        return cnt_groups_;
    }
};


using UFT = UnionFindTree;


int main() {
    // 入力
    int N, M; std::cin >> N >> M;
    int A, B; std::cin >> A >> B;
    std::vector<int> X(M), Y(M);
    for (int i = 0; i < M; ++i) std::cin >> X[i] >> Y[i];
    
    // 初期化
    // 0-indexedであることに注意!
    UFT uft(N);
    // 結合
    for (int i = 0; i < M; ++i) {
        uft.unite(X[i], Y[i]);
    }
    // 同一か判定
    bool is_same = uft.is_same(A, B);
    // グループの数を取得
    int group_count = uft.count_groups();
    // グループのサイズを取得
    int size_A = uft.size_of(A);
}