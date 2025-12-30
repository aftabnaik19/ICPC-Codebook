static uint64_t seed =
chrono::steady_clock::now().time_since_epoch().count();
uint64_t splitmix64() {
  seed += 0x9e3779b97f4a7c15;
  uint64_t x = seed;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return x ^ (x >> 31);
}
long long randInRange(long long l, long long r) {
  assert(l <= r);
  return l + splitmix64() % (r - l + 1);
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
