class Trie {
public:
  struct Node {
    vector<int> next; // Indices of children nodes
    int pfxCnt = 0; // How many words pass through this node
    int wordCnt =
    0; // How many words end exactly at this node

    Node(int maxChars) {
      next.assign(maxChars, -1);
      pfxCnt = 0;
      wordCnt = 0;
    }
  };
  vector<Node> nodes;
  int
  distWords;    // Count of distinct words currently in Trie
  int maxChars; // Alphabet size (usually 26)
  int getBase(char c) {
    return c - 'Change'; // based on problem
  }

  Trie(int maxChars = 26) {
    this->maxChars = maxChars;
    nodes.clear();
    distWords = 0;
    // Create Root Node (Index 0)
    nodes.emplace_back(maxChars);
  }

  // Insert string s into Trie
  void insert(string s) {
    int curr = 0;
    nodes[curr].pfxCnt++;
    for (char &ch : s) {
      int base = getBase(ch);
      // If path doesn't exist, create new node
      if (nodes[curr].next[base] == -1) {
        nodes[curr].next[base] = nodes.size();
        nodes.emplace_back(maxChars);
      }
      curr = nodes[curr].next[base];
      nodes[curr].pfxCnt++;
    }
    if (nodes[curr].wordCnt == 0) {
      distWords++; // New distinct word found
    }
    nodes[curr].wordCnt++;
  }

  // Check if string s exists
  bool search(string s) {
    int curr = 0;
    for (char &ch : s) {
      int base = getBase(ch);
      if (nodes[curr].next[base] == -1) return false;
      curr = nodes[curr].next[base];
    }
    return nodes[curr].wordCnt > 0;
  }
  // Delete one occurrence of s
  void erase(string s) {
    if (!search(s)) return; // Check existence first
    int curr = 0;
    nodes[curr].pfxCnt--;
    for (char &ch : s) {
      int base = getBase(ch);
      curr = nodes[curr].next[base];
      nodes[curr].pfxCnt--;
    }
    nodes[curr].wordCnt--;
    if (nodes[curr].wordCnt == 0)
      distWords--; // Word completely removed
  }

  // Count words that have s as a prefix
  int prefixCount(string s) {
    int curr = 0;
    for (char &ch : s) {
      int base = getBase(ch);
      if (nodes[curr].next[base] == -1)
        return 0; // Prefix not found
      curr = nodes[curr].next[base];
    }
    return nodes[curr].pfxCnt;
  }
};
