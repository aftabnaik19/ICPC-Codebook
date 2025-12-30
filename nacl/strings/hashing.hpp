struct Hasher64 {
  int n;
  vector<uint32_t> pref1, pref2, pow1, pow2;
  Hasher64() {}
  Hasher64(const string &s) {
    n = s.size();
    pref1.assign(n + 1, 0);
    pref2.assign(n + 1, 0);
    pow1.assign(n + 1, 0);
    pow2.assign(n + 1, 0);
    pow1[0] = pow2[0] = 1;
    for (int i = 1; i <= n; i++) {
      uint32_t val = (s[i - 1] - 'A' + 1);
      pref1[i] =
      (val + (uint64_t)BASE1 * pref1[i - 1]) % MOD1;
      pref2[i] =
      (val + (uint64_t)BASE2 * pref2[i - 1]) % MOD2;
      pow1[i] = (uint64_t)pow1[i - 1] * BASE1 % MOD1;
      pow2[i] = (uint64_t)pow2[i - 1] * BASE2 % MOD2;
    }
  }
  inline uint64_t getHash(int l, int r) {
    uint32_t h1 =
    (pref1[r + 1] -
     (uint64_t)pref1[l] * pow1[r - l + 1] % MOD1 + MOD1) %
    MOD1;
    uint32_t h2 =
    (pref2[r + 1] -
     (uint64_t)pref2[l] * pow2[r - l + 1] % MOD2 + MOD2) %
    MOD2;
    return (uint64_t(h2) << 32) | h1;
  }
};
Hasher64 s(a);
unordered_map<uint64_t, int> mp;
mp.reserve(n);
mp.max_load_factor(0.7);
uint64_t h = s.getHash(i, i + len - 1);
