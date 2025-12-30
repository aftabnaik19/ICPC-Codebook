struct SegTree {
  int n;
  vector<ll> st, lz;
  SegTree(int n, vector<ll> &a) : n(n) {
    st.assign(4 * n, 0);
    lz.assign(4 * n, -1);
    build(1, 0, n - 1, a);
  }
  void build(int p, int l, int r, vector<ll> &a) {
    if (l == r) return void(st[p] = a[l]);
    int m = (l + r) / 2;
    build(p << 1, l, m, a);
    build(p << 1 | 1, m + 1, r, a);
    st[p] = st[p << 1] + st[p << 1 | 1];
  }
  void push(int p, int l, int r) {
    if (lz[p] == -1) return;
    int m = (l + r) / 2;
    apply(p << 1, l, m, lz[p]);
    apply(p << 1 | 1, m + 1, r, lz[p]);
    lz[p] = -1;
  }
  void apply(int p, int l, int r, ll v) {
    st[p] = v * (r - l + 1);
    if (l != r) lz[p] = v;
  }
  void upd(int p, int l, int r, int i, int j, ll v) {
    if (r < i || l > j) return;
    if (i <= l && r <= j) return apply(p, l, r, v);
    push(p, l, r);
    int m = (l + r) / 2;
    upd(p << 1, l, m, i, j, v);
    upd(p << 1 | 1, m + 1, r, i, j, v);
    st[p] = st[p << 1] + st[p << 1 | 1];
  }
  ll qry(int p, int l, int r, int i, int j) {
    if (r < i || l > j) return 0;
    if (i <= l && r <= j) return st[p];
    push(p, l, r);
    int m = (l + r) / 2;
    return qry(p << 1, l, m, i, j) +
           qry(p << 1 | 1, m + 1, r, i, j);
  }
};
