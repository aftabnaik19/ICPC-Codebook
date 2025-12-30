int n;
vvi jump, g, adj;
vi depth, val;
void dfs(int root, int parent, int currDepth) {
  depth[root] = parent == -1 ? 0 : depth[parent] + 1;
  jump[root][0] = parent;
  g[root][0] = val[root];
  for (int i = 1; i < 20;
       i++) { // always start from 1, since i depends on i-1
    if (jump[root][i - 1] != -1) {
      jump[root][i] = jump[jump[root][i - 1]][i - 1];
      g[root][i] =
      gcd(g[root][i - 1],
          g[jump[root][i - 1]][i - 1]); // combination logic
    } else {
      jump[root][i] = -1;
      g[root][i] =
      g[root]
       [i - 1]; // when the i-1th ancestor doesn't exist,
                // then store same aggregate as i-1th
    }
  }
  // do normal DFS from here
}
int path_gcd(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  int GCD = 0; // always use the identity value
  for (int i = 19; i >= 0; i--) {
    if (((depth[u] - depth[v]) >> i) & 1) {
      {
        GCD = gcd(g[u][i], GCD);
        u = jump[u][i];
      }
    }
  }
  if (u == v)
    return gcd(
    GCD,
    val[u]); // g[u][i], doesn't contain val at jump[u][i]
  for (int i = 19; i >= 0; i--) {
    if (jump[u][i] != jump[v][i]) {
      GCD = gcd(GCD, g[u][i]);
      GCD = gcd(GCD, g[v][i]);
      u = jump[u][i];
      v = jump[v][i];
    }
  }
  // since both u and v are immediate child of lca
  // neither u, v nor lca is included in the computation
  // add them explicitly
  GCD = gcd(GCD, val[u]);
  GCD = gcd(GCD, val[v]);
  return gcd(GCD, val[jump[u][0]]);
}
