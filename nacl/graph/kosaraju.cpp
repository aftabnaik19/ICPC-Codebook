void SCC(vvi const &adj, vvi &components, vvi &adj_cond) {
  int n = adj.size();
  components.clear(), adj_cond.clear();
  vector<int> order; // sorted (exit) list of G's vertices
  visited.assign(n, false);
  for (int i = 0; i < n; i++) // first dfs series
    if (!visited[i]) dfs(i, adj, order);
  // create adjacency list of G^T
  vector<vector<int>> adj_rev(n);
  for (int v = 0; v < n; v++)
    for (int u : adj[v]) adj_rev[u].push_back(v);
  visited.assign(n, false);
  reverse(order.begin(), order.end());
  vector<int> roots(n,
                    0); // gives root vertex of vertex's SCC
  for (auto v : order)  // second dfs series
    if (!visited[v]) {
      std::vector<int> component;
      dfs(v, adj_rev, component);
      components.push_back(component);
      int root = *component.begin();
      for (auto u : component) roots[u] = root;
    }
  // add edges to condensation graph
  adj_cond.assign(n, {});
  for (int v = 0; v < n; v++)
    for (auto u : adj[v])
      if (roots[v] != roots[u])
        adj_cond[roots[v]].push_back(roots[u]);
}
