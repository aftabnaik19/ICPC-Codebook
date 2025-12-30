struct fwt {
  vector<long long> bit;
  int n;
  fwt(int n) {
    this->n = n + 1;
    bit.assign(n + 1, 0);
  }
  fwt(const vector<int> &a) : fwt(a.size()) {
    for (size_t i = 0; i < a.size(); i++) add(i, a[i]);
  }
  long long sum(int idx) {
    long long ret = 0;
    for (++idx; idx > 0; idx -= idx & -idx) ret += bit[idx];
    return ret;
  }
  long long sum(int l, int r) {
    if (l > r) return 0; // Guard clause
    return sum(r) - sum(l - 1);
  }
  void add(int idx, int delta) {
    for (++idx; idx < n; idx += idx & -idx)
      bit[idx] += delta;
  }
};
