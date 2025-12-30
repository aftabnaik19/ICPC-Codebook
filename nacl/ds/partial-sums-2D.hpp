struct PrefixSum2D {
  vvll pref;                  // 0-based 2-D prefix sum
  void build(const vvll &v) { // creates a copy
    int n = v.size(), m = v[0].size();
    pref.assign(n, vll(m, 0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        pref[i][j] = v[i][j] + (i ? pref[i - 1][j] : 0) +
                     (j ? pref[i][j - 1] : 0) -
                     (i && j ? pref[i - 1][j - 1] : 0);
      }
    }
  }
  ll query(int ulx, int uly, int brx, int bry) const {
    ll ans = pref[brx][bry];
    if (ulx) ans -= pref[ulx - 1][bry];
    if (uly) ans -= pref[brx][uly - 1];
    if (ulx && uly) ans += pref[ulx - 1][uly - 1];
    return ans;
  }
  ll query(int ulx, int uly, int size) const {
    return query(ulx, uly, ulx + size - 1, uly + size - 1);
  }
};
struct PartialSum2D : PrefixSum2D {
  vvll diff; // 0 based
  int n, m;
  PartialSum2D(int _n, int _m) : n(_n), m(_m) {
    diff.assign(n + 1, vll(m + 1, 0));
  }
  // add c from [ulx,uly] to [brx,bry]
  void update(int ulx, int uly, int brx, int bry, ll c) {
    diff[ulx][uly] += c;
    diff[ulx][bry + 1] -= c;
    diff[brx + 1][uly] -= c;
    diff[brx + 1][bry + 1] += c;
  }
  void update(int ulx, int uly, int size, ll c) {
    int brx = ulx + size - 1, bry = uly + size - 1;
    update(ulx, uly, brx, bry, c);
  }
  void process() {
    this->build(diff);
  } // process grid using prefix sum
};
// usage
PrefixSum2D pref;
pref.build(v); // takes 2d 0-based vector as input
pref.query(x1, y1, x2, y2);     // sum of region
PartialSum2D part(n, m);        // dimension of grid 0 based
part.update(x1, y1, x2, y2, 1); // add 1 in region
// must run after all updates
part.process(); // prefix sum on diff array
// only exists after processing
vvll &grid = part.pref;     // processed diff array
part.query(x1, y1, x2, y2); // gives sum of region
