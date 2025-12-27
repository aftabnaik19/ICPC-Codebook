long long randInRange(long long l, long long r) {
  static random_device rd;     // seed
  static mt19937_64 gen(rd()); // 64-bit Mersenne Twister
  uniform_int_distribution<long long> dist(l, r);
  return dist(gen);
}
void solve() {
  map<ll, pll> mp;
  vector<pll> pref;
  for (int i = 1; i <= n; i++) {
    mp[a[i]] = {randInRange(0LL, (1LL << 64) - 1),
                randInRange(0LL, (1LL << 64) - 1)};
    pref[i].ff = pref[i - 1].ff ^ mp[a[i]].ff;
    pref[i].ss = pref[i - 1].ss ^ mp[a[i]].ss;
  }
}
