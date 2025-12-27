const long long LOG = 20;
const long long sz = (1 << LOG);
void forward1(
vector<long long> &dp) { // subSet contribution to superset
  for (int b = 0; b <= LOG; b++)
    for (int i = 0; i <= sz; i++)
      if (i & (1 << b)) dp[i] += dp[i ^ (1 << b)];
}
void backward1(vector<long long> &dp) { // undo of forward 1
  for (int b = LOG; b >= 0; b--)
    for (int i = sz; i >= 0; i--)
      if (i & (1 << b)) dp[i] -= dp[i ^ (1 << b)];
}
void forward2(
vector<long long> &dp) { // superset contributes to subset
  for (int b = 0; b <= LOG; b++)
    for (int i = 0; i <= sz; i++)
      if (i & (1 << b)) dp[i ^ (1 << b)] += dp[i];
}
void backward2(vector<long long> &dp) { // undo of forward 2
  for (int b = LOG; b >= 0; b--)
    for (int i = sz; i >= 0; i--)
      if (i & (1 << b)) dp[i ^ (1 << b)] += dp[i];
}
