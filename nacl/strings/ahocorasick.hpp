const int ALPHA = 26, MAXNODES = 500000 + 5;
int nxt[MAXNODES][ALPHA];
int linkS[MAXNODES];
ll cntNode[MAXNODES];
vector<int> adjSL[MAXNODES];
vector<int> patEnd;
int nodes = 1;

void build_trie(const vector<string> &P) {
  // clear
  for (int i = 0; i < nodes; i++) {
    memset(nxt[i], 0, sizeof nxt[i]);
    cntNode[i] = 0;
    adjSL[i].clear();
  }
  nodes = 1;
  patEnd.clear();
  patEnd.reserve(P.size());
  // insert
  for (auto &pat : P) {
    int u = 0;
    for (char ch : pat) {
      int c = ch - 'a';
      if (!nxt[u][c]) nxt[u][c] = nodes++;
      u = nxt[u][c];
    }
    patEnd.pb(u);
  }
}
vector<int> bfsOrder;
void build_links() {
  queue<int> q;
  linkS[0] = 0;
  // first layer
  for (int c = 0; c < ALPHA; c++) {
    int v = nxt[0][c];
    if (v) {
      linkS[v] = 0;
      q.push(v);
    }
  }
  // BFS
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    bfsOrder.pb(u);
    for (int c = 0; c < ALPHA; c++) {
      int v = nxt[u][c];
      if (!v) continue;
      int j = linkS[u];
      while (j && !nxt[j][c]) j = linkS[j];
      if (nxt[j][c]) j = nxt[j][c];
      linkS[v] = j;
      q.push(v);
    }
  }
  for (int u : bfsOrder) { adjSL[linkS[u]].pb(u); }
}

void solve() {
  string S;
  ll k;
  cin >> S >> k;
  vector<string> P(k);
  for (int i = 0; i < k; i++) cin >> P[i];
  build_trie(P);
  bfsOrder.clear();
  build_links();
}
