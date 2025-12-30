int lis(vector<int> const &a) {
  int n = a.size();
  const int INF = 1e9;
  vector<int> d(n + 1, INF); // min possible ending value
  // of inc subseq of length l, that we have seen
  d[0] = -INF;
  // user lower bound for non-decreasing
  for (int i = 0; i < n; i++) {
    int l =
    upper_bound(d.begin(), d.end(), a[i]) - d.begin();
    if (d[l - 1] < a[i] && a[i] < d[l]) d[l] = a[i];
  }
  int ans = 0;
  for (int l = 0; l <= n; l++) {
    if (d[l] < INF) ans = l;
  }
  return ans;
}
