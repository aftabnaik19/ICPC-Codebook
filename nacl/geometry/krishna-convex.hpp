struct Point {
  ll x, y;
  Point() : x(0), y(0) {}
  Point(ll _x, ll _y) : x(_x), y(_y) {}
  bool operator==(const Point &other) const {
    return x == other.x && y == other.y;
  }
  bool operator<(const Point &other) const {
    if (x != other.x) return x < other.x;
    return y < other.y;
  }
};
ll cross_product(const Point &A, const Point &B,
                 const Point &C) {
  /*
  cross(A, B, C) tells you how the angle turns when you go A
  → B → C. If cross > 0 → left turn (counter-clockwise) If
  cross < 0 → right turn (clockwise) If cross = 0 →
  collinear
  */
  return (B.x - A.x) * (C.y - A.y) -
         (B.y - A.y) * (C.x - A.x);
}
long long dot_product(const Point &A, const Point &B,
                      const Point &C) {
  // computes (B - A) · (C - A)
  return (B.x - A.x) * (C.x - A.x) +
         (B.y - A.y) * (C.y - A.y);
}
vector<Point> ConvexHullAndrowChain(vector<Point> pts) {
  sort(pts);
  pts.erase(unique(pts.begin(), pts.end()), pts.end());
  int n = pts.size();
  if (n <= 1) return pts;
  vector<Point> lower, upper;
  // Build lower hull
  for (int i = 0; i < n; ++i) {
    const Point &p = pts[i];
    while (lower.size() >= 2 &&
           cross_product(lower[lower.size() - 2],
                         lower[lower.size() - 1], p) <= 0) {
      lower.pop_back();
    }
    lower.push_back(p);
  }
  // Build upper hull
  for (int i = n - 1; i >= 0; --i) {
    const Point &p = pts[i];
    while (upper.size() >= 2 &&
           cross_product(upper[upper.size() - 2],
                         upper[upper.size() - 1], p) <= 0) {
      upper.pop_back();
    }
    upper.push_back(p);
  }
  vector<Point> hull = lower;
  for (int i = 1; i + 1 < (int)upper.size(); ++i) {
    hull.push_back(upper[i]);
  }

  return hull; // CCW order
}
