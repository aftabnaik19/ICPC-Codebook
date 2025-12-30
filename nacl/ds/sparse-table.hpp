// Purpose: Static Range Queries
// Idempotent (Min/Max/GCD): O(1)
// Non-Idempotent (Sum/Prod/XOR): O(log N)
struct SparseTable {
  vector<vector<long long>> sparse;
  vector<int> Log;
  int n, max_log;
  long long IDENTITY_VAL; // e.g., 0 for Sum, 1 for Product,
  long long func(long long a, long long b) {
    return (a + b); // Example: Sum
  }
  void build(const vector<long long> &a,
             long long identity) {
    n = a.size();
    IDENTITY_VAL = identity;
    max_log = 32 - __builtin_clz(n);
    sparse.assign(n, vector<long long>(max_log));
    Log.assign(n + 1, 0);
    for (int i = 2; i <= n; ++i) Log[i] = Log[i / 2] + 1;
    for (int i = 0; i < n; ++i) sparse[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; ++j) {
      for (int i = 0; i + (1 << j) <= n; ++i) {
        sparse[i][j] =
        func(sparse[i][j - 1],
             sparse[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
  // 3. IDEMPOTENT QUERY O(1) Min, Max, GCD, OR, AND
  long long query_idempotent(int l, int r) {
    int k = Log[r - l + 1];
    return func(sparse[l][k], sparse[r - (1 << k) + 1][k]);
  }
  // 4. NON-IDEMPOTENT QUERY O(log N)
  // Use for: Sum, Product, XOR, Matrix Multiplication
  long long query_non_idempotent(int l, int r) {
    long long res = IDENTITY_VAL;
    for (int j = max_log - 1; j >= 0; --j) {
      if ((1 << j) <= r - l + 1) {
        // Combine current result with the next block
        res = func(res, sparse[l][j]);
        l += (1 << j); // Move L forward by 2^j
      }
    }
    return res;
  }
};
