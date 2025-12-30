const long long INF = 1e18;
vector<array<int, 3>> e; // {u, v, w}
vector<long long> d, par;
int main() {
  int n, m;
  cin >> n >> m;
  e.resize(m);
  d.assign(
  n, 0); // use 0 to detect neg-cycle in disconnected graph
  par.assign(n, -1);
  int x = -1;
  for (int i = 0; i <= n; i++) {
    x = -1;
    for (auto [u, v, w] : e) {
      if (d[v] > d[u] + w) {
        d[v] = d[u] + w;
        par[v] = u;
        x = v;
      }
    }
  }
  if (x == -1) {
    // no negative cycle
  } else {
    // negative cycle exists
    for (int i = 0; i < n; i++) x = par[x];
    vector<int> cyc;
    for (int v = x;; v = par[v]) {
      cyc.push_back(v);
      if (v == x && cyc.size() > 1) break;
    }
    reverse(cyc.begin(), cyc.end());
  }
}
