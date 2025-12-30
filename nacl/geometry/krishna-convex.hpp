struct Point {
  ll x, y;
  Point(ll _x = 0, ll _y = 0) : x(_x), y(_y) {}
  bool operator==(const Point &other) const {
    return x == other.x && y == other.y;
  }
  bool operator<(const Point &other) const {
    if (x != other.x) return x < other.x;
    return y < other.y;
  }
};
ll cross_product(Point &A, Point &B, Point &C) {
  // cross(A, B, C) tells you how the angle turns when you
  // go A → B → C. If cross > 0 → left turn If cross < 0 →
  // right turn (clockwise) If cross = 0 → collinear
  return (B.x - A.x) * (C.y - A.y) -
         (B.y - A.y) * (C.x - A.x);
}
long long dot_product(Point &A, Point &B, Point &C) {
  // computes (B - A) · (C - A)
  return (B.x - A.x) * (C.x - A.x) +
         (B.y - A.y) * (C.y - A.y);
}
vector<Point> ConvexHullAndrowChain(vector<Point> pts) {
  sort(pts);
  pts.erase(unique(pts.begin(), pts.end()), pts.end());
  int n = pts.size();
  if (n <= 1) return pts;
  vector<Point> lr, up;
  for (int i = 0; i < n; ++i) { // Build lr hull
    const Point &p = pts[i];
    while (lr.size() >= 2 &&
           cross_product(lr[lr.size() - 2],
                         lr[lr.size() - 1], p) <= 0) {
      lr.pop_back();
    }
    lr.push_back(p);
  }
  for (int i = n - 1; i >= 0; --i) { // Build up hull
    const Point &p = pts[i];
    while (up.size() >= 2 &&
           cross_product(up[up.size() - 2],
                         up[up.size() - 1], p) <= 0) {
      up.pop_back();
    }
    up.push_back(p);
  }
  vector<Point> hull = lr;
  for (int i = 1; i + 1 < (int)up.size(); ++i)
    hull.push_back(up[i]);
  return hull; // CCW order
}
