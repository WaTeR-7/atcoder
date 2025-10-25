#include <bits/stdc++.h>
using namespace std;

class UFT {
  int n;
  vector<int> root, rank;
public:
  UFT (int n): n(n+1), root(n+1, -1), rank(n+1) {}
  int find(int x);
  void unite(int x, int y);
  bool same(int x, int y);
};

int UFT::find(int x) {
  if (root[x] < 0) return x;
  return root[x] = find(root[x]);
}

void UFT::unite(int x, int y) {
  x = find(x); y = find(y);
  if (x == y) return;
  if (rank[x] == rank[y]) rank[x]++;
  else if (rank[x] < rank[y]) swap(x, y);
  root[x] += root[y];
  root[y] = x;
}

bool UFT::same(int x, int y) {
  return find(x) == find(y);
}

int main() {
  int n; cin >> n;
  UFT t(n);
}