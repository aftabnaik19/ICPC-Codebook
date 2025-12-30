// d1[i] = number of odd-length palindromes centered at i
// d2[i] = number of even-length palindromes centered
// between i-1 and i
vector<int> d1, d2;
void manacher(const string &s) {
  int n = s.size();
  d1.assign(n, 0);
  d2.assign(n, 0);
  // Odd length palindromes
  for (int i = 0, l = 0, r = -1; i < n; i++) {
    int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
    while (0 <= i - k && i + k < n && s[i - k] == s[i + k])
      k++;
    d1[i] = k;
    if (i + k - 1 > r) {
      l = i - k + 1;
      r = i + k - 1;
    }
  }
  // Even length palindromes
  for (int i = 0, l = 0, r = -1; i < n; i++) {
    int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
    while (0 <= i - k - 1 && i + k < n &&
           s[i - k - 1] == s[i + k])
      k++;
    d2[i] = k;
    if (i + k - 1 > r) {
      l = i - k;
      r = i + k - 1;
    }
  }
}
