struct SparseTable {
  vector<vector<ll>> sparse;
  vector<int> Log;
  int n, max_log;
  ll IDENTITY_VAL; // e.g., 0 for Sum, 1 for Product,
  ll func(ll a, ll b) { return (a + b); } // Example: Sum
  void build(const vector<ll> &a, ll identity) {
    n = a.size();
    IDENTITY_VAL = identity;
    max_log = 32 - __builtin_clz(n);
    sparse.assign(n, vector<ll>(max_log));
    Log.assign(n + 1, 0);
    for (int i = 2; i <= n; ++i) Log[i] = Log[i / 2] + 1;
    for (int i = 0; i < n; ++i) sparse[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; ++j) {
      for (int i = 0; i + (1 << j) <= n; ++i)
        sparse[i][j] =
        func(sparse[i][j - 1],
             sparse[i + (1 << (j - 1))][j - 1]);
    }
  }
  ll query_idempotent(int l, int r) {
    int k = Log[r - l + 1];
    return func(sparse[l][k], sparse[r - (1 << k) + 1][k]);
  }
  // Use for: Sum, Product, XOR, Matrix Multiplication
  ll query_non_idempotent(int l, int r) {
    ll res = IDENTITY_VAL;
    for (int j = max_log - 1; j >= 0; --j)
      if ((1 << j) <= r - l + 1) {
        res = func(res, sparse[l][j]);
        l += (1 << j); // Move L forward by 2^j
      }
    return res;
  }
};
