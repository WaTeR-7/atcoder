#include <bits/stdc++.h>


/**
 * グラフが閉路を持つかどうかトポロジカルソートで判定する
 * 計算量はO(|V|+|E|)
 * @param graph グラフを表す隣接リスト
 * @return グラフが閉路を持つならtrueを返す
 */
bool has_cycle(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<int> in_degree(n);
    for (int i = 0; i < n; ++i) {
        for (int j : graph[i]) {
            in_degree[j]++;
        }
    }
    
    std::queue<int> que;
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] == 0) que.push(i);
    }
    
    int visited_cnt = 0;
    while (! que.empty()) {
        int st = que.front(); que.pop();
        ++visited_cnt;
        for (int ds : graph[st]) {
            --in_degree[ds];
            if (in_degree[ds] == 0) {
                que.push(ds);
            }
        }
    }
    
    // 削除できたノード数が全体より少なければ，閉路が存在する．
    return visited_cnt != n;
}