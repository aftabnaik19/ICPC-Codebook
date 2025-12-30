const int INF = 1e9;
vector<vector<int>> d, p;
void path(int i, int j) {
  if (i != j) path(i, p[i][j]);
  cout << j << " ";
}
int main() {
  int n, m;
  cin >> n >> m;
  d.assign(n, vector<int>(n, INF));
  p.assign(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    d[i][i] = 0;
    for (int j = 0; j < n; j++) p[i][j] = i;
  }
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    --u;
    --v;
    d[u][v] = min(d[u][v], w);
  }
  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (d[i][k] < INF && d[k][j] < INF &&
            d[i][j] > d[i][k] + d[k][j]) {
          d[i][j] = d[i][k] + d[k][j];
          p[i][j] = p[k][j];
        }
  for (int i = 0; i < n; i++)
    if (d[i][i] < 0) {
      // negative cycle exists
    }
}
