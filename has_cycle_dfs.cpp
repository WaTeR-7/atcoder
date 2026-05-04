#include <bits/stdc++.h>


/**
 * グラフが閉路を持つかどうかDFSで判定する
 * 計算量はO(|V|+|E|)
 * @param graph グラフを表す隣接リスト
 * @return グラフが閉路を持つならtrueを返す
 */
bool has_cycle(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<int> done(n);
    std::vector<int> on_stack(n);
    auto dfs = [&](int st, auto self) -> bool {
        done[st] = 1;
        on_stack[st] = 1;
        for (int ds : graph[st]) {
            if (! done[ds]) {
                if (self(ds, self)) return true;
            }
            else if (on_stack[ds]) {
                return true;
            }
        }
        on_stack[st] = 0;
        return false;
    };
    for (int i = 0; i < n; ++i) {
        if (! done[i]) {
            if (dfs(i, dfs)) return true;
        }
    }
    return false;
}