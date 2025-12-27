class Solution {
  int cnt;
  int dfs(int u, int p, vvi &adj, vi &vis, vi &low,
          vvi &ans) {
    if (vis[u] != -1) return low[u];
    vis[u] = cnt, low[u] = cnt;
    cnt++;
    for (auto v : adj[u]) {
      if (v == p) continue;
      int temp = dfs(v, u, adj, vis, low, ans);
      low[u] = min(low[u], low[v]);
      if (temp > vis[u]) ans.push_back({u, v});
      else low[u] = min(low[u], vis[v]);
    }
    return low[u];
  }
  vvi tarjanAlgorithm(int n, vvi &edges) {
    vector<vector<int>> adj(n);
    for (int i = 0; i < edges.size(); i++) {
      int u = edges[i][0], v = edges[i][1];
      adj[u].pb(v), adj[v].pb(u);
    }
    vi vis(n, -1), low(n, -1);
    vector<vector<int>> ans;
    cnt = 1;
    dfs(0, -1, adj, vis, low, ans);
    return ans;
  }
};
