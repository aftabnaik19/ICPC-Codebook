template <class Node, class Update> struct LazySegTree {
  int n;
  vector<Node> st;
  vector<Update> lz;
  LazySegTree(int n, vector<ll> &a) : n(n) {
    st.assign(4 * n, Node());
    lz.assign(4 * n, Update());
    build(1, 0, n - 1, a);
  }
  void build(int p, int l, int r, vector<ll> &a) {
    if (l == r) return void(st[p] = Node(a[l]));
    int m = (l + r) / 2;
    build(p << 1, l, m, a);
    build(p << 1 | 1, m + 1, r, a);
    st[p].merge(st[p << 1], st[p << 1 | 1]);
  }
  void push(int p, int l, int r) {
    if (lz[p].is_identity()) return;
    int m = (l + r) / 2;
    apply(p << 1, l, m, lz[p]);
    apply(p << 1 | 1, m + 1, r, lz[p]);
    lz[p] = Update();
  }
  void apply(int p, int l, int r, Update &u) {
    u.apply(st[p], l, r);
    if (l != r) lz[p].combine(u);
  }
  void update(int p, int l, int r, int i, int j,
              Update &u) {
    if (r < i || l > j) return;
    if (i <= l && r <= j) return apply(p, l, r, u);
    push(p, l, r);
    int m = (l + r) / 2;
    update(p << 1, l, m, i, j, u);
    update(p << 1 | 1, m + 1, r, i, j, u);
    st[p].merge(st[p << 1], st[p << 1 | 1]);
  }
  Node query(int p, int l, int r, int i, int j) {
    if (r < i || l > j) return Node();
    if (i <= l && r <= j) return st[p];
    push(p, l, r);
    int m = (l + r) / 2;
    Node res;
    res.merge(query(p << 1, l, m, i, j),
              query(p << 1 | 1, m + 1, r, i, j));
    return res;
  }
  void update(int l, int r, ll v) {
    Update u(v);
    update(1, 0, n - 1, l, r, u);
  }
  Node query(int l, int r) {
    return query(1, 0, n - 1, l, r);
  }
};
struct Node {
  ll val = 0;
  Node(ll v = 0) : val(v) {}
  void merge(const Node &l, const Node &r) {
    val = l.val + r.val;
  }
};
struct Update {
  ll val = 0;
  Update(ll v = 0) : val(v) {}
  bool is_identity() const { return val == 0; }
  void apply(Node &a, int l, int r) {
    a.val = val * (r - l + 1);
  }
  void combine(Update &u) { val = u.val; }
};
