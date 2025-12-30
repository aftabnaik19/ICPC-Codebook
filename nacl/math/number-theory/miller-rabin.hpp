using u128 = __uint128_t;
using ull = unsigned long long;
ull mod_mul(ull a, ull b, ull mod) {
  return (u128)a * b % mod;
}
ull mod_pow(ull a, ull d, ull mod) {
  ull res = 1;
  while (d) {
    if (d & 1) res = mod_mul(res, a, mod);
    a = mod_mul(a, a, mod);
    d >>= 1;
  }
  return res;
}
bool isPrime(ull n) {
  if (n < 2) return false;
  for (ull p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    if (n % p == 0) return n == p;
  ull d = n - 1;
  int s = __builtin_ctzll(d);
  d >>= s;
  auto check = [&](ull a) {
    ull x = mod_pow(a, d, n);
    if (x == 1 || x == n - 1) return true;
    for (int r = 1; r < s; r++) {
      x = mod_mul(x, x, n);
      if (x == n - 1) return true;
    }
    return false;
  };
  // Proven deterministic bases for 64-bit
  // {2, 7, 61} for 32 bits
  for (ull a :
       {2, 325, 9375, 28178, 450775, 9780504, 1795265022})
    if (a < n && !check(a)) return false;
  return true;
}
