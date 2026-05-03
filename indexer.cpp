#include <bits/stdc++.h>


/**
 * 座標と対応する一意なidとを相互に変換できるクラス
 */
template <size_t N>
class Indexer {
    
    static_assert(N > 0, "Dimension must be greater than 0");
    
  private:
    std::array<int,N> dims_;     // 各次元のサイズ
    std::array<int,N> strides_;  // 変換用の重み
    int total_size_;             // idの大きさ
    
  public:
    /**
     * Indexerのコンストラクタ
     * @param dimensions 各次元のサイズ 例: {D1, D2, D3}
     */
    constexpr Indexer(const std::array<int,N>& dimensions) : dims_(dimensions) {
        // 各次元の重みの計算
        int cur_stride = 1;
        for (int i = static_cast<int>(N) - 1; i >= 0; --i) {
            strides_[i] = cur_stride;
            cur_stride *= dims_[i];
        }
        total_size_ = cur_stride;
    }
    
    /**
     * @return idの大きさを取得する
     */
    int size() const noexcept { return total_size_; }
    
    /**
     * (p1,p2,...) -> id 座標からidに変換する関数
     * @param args 次元と同じ大きさの数の座標を引数に渡す
     * @return 計算された座標に対応するid
     */
    template <typename... Args>
    constexpr int to_id(Args... args) const {
        static_assert(sizeof...(args) == N, "Invalid number of arguments");
        return to_id_impl(0, args...);
    }
    
  private:
    /**
     * 再帰的にidを計算するヘルパー関数
     */
    template <typename T, typename... Rest>
    constexpr int to_id_impl(size_t dim_idx, T first, Rest... rest) const {
        assert(first >= 0 && first < dims_[dim_idx]);
        return (first * strides_[dim_idx]) + to_id_impl(dim_idx+1, rest...);
    }
    
    /**
     * idを計算する関数の停止条件としてはたらく
     */
    constexpr int to_id_impl(size_t dim_idx) const {
        return 0;
    }
    
  public:
    /**
     * id -> (p1,p2,...) idから座標に変換する関数
     * @param id 座標に変換するid
     * @return 計算されたidに対応する座標
     */
    constexpr std::array<int,N> to_pos(int id) const {
        assert(id >= 0 && id < total_size_);
        std::array<int,N> pos{};
        for (size_t i = 0; i < N; ++i) {
            pos[i] = (id / strides_[i]) % dims_[i];
        }
        return pos;
    }
    
    /**
     * id -> (p1,p2,...) idから座標に変換する関数
     * @param id 座標に変換するid
     * @param pos idに対応する座標 参照渡しで受け取り，上書きする
     */
    void to_pos(int id, std::array<int,N>& pos) const {
        assert(id >= 0 && id < total_size_);
        for (size_t i = 0; i < N; ++i) {
            pos[i] = (id / strides_[i]) % dims_[i];
        }
        return;
    }
};


int main() {
    constexpr int N = 3;
    int n, m, k; std::cin >> n >> m >> k;
    // 初期化
    std::array<int,N> dims = {n, m, k};
    Indexer<N> indexer(dims);
    // pos -> id
    int id = indexer.to_id(1, 2, 4);
    // id -> pos
    std::array<int,N> pos = indexer.to_pos(13);
}