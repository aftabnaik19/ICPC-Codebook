/**
 * Generic Matrix Template
 * * Purpose: Matrix Exponentiation and Operations
 * * Usage:
 * Matrix A(n, n, 1e9+7); // Modular Arithmetic
 * Matrix B(n, n);        // Standard Arithmetic (mod = 0)
 * * Complexity: Multiplication O(N^3), Power O(N^3 log Exp)
 */
struct Matrix {
  using ll = long long;
  vector<vector<ll>> mat;
  int rows, cols;
  ll mod; // mod = 0 implies Standard Arithmetic (No Modulo)

  // Constructor: Default mod is 0 (No Mod)
  Matrix(int r, int c, ll m = 0)
      : rows(r), cols(c), mod(m) {
    mat.assign(rows, vector<ll>(cols, 0));
  }

  // Input Matrix
  void input() {
    for (int i = 0; i < rows; ++i)
      for (int j = 0; j < cols; ++j) cin >> mat[i][j];
  }

  // Print Matrix
  void print() const {
    for (const auto &row : mat) {
      for (const auto &val : row) cout << val << " ";
      cout << endl;
    }
  }

  // Addition
  Matrix operator+(const Matrix &other) const {
    Matrix result(rows, cols, mod);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        result.mat[i][j] = mat[i][j] + other.mat[i][j];
        if (mod) result.mat[i][j] %= mod;
      }
    }
    return result;
  }

  // Subtraction
  Matrix operator-(const Matrix &other) const {
    Matrix result(rows, cols, mod);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        result.mat[i][j] = mat[i][j] - other.mat[i][j];
        if (mod)
          result.mat[i][j] =
          (result.mat[i][j] % mod + mod) % mod;
      }
    }
    return result;
  }

  // Multiplication O(N^3)
  Matrix operator*(const Matrix &other) const {
    // Assert matching dimensions if needed: assert(cols ==
    // other.rows);
    Matrix result(rows, other.cols, mod);
    for (int i = 0; i < rows; ++i) {
      for (int k = 0; k < cols;
           ++k) { // Optimized loop order (i-k-j is cache
                  // friendly)
        if (mat[i][k] == 0)
          continue; // Optimization for sparse matrices
        for (int j = 0; j < other.cols; ++j) {
          if (mod) {
            result.mat[i][j] =
            (result.mat[i][j] +
             mat[i][k] * other.mat[k][j]) %
            mod;
          } else {
            result.mat[i][j] += mat[i][k] * other.mat[k][j];
          }
        }
      }
    }
    return result;
  }

  // Matrix Exponentiation O(N^3 log Exp)
  Matrix power(ll exp) const {
    // Identity Matrix
    Matrix result(rows, cols, mod);
    for (int i = 0; i < rows; ++i) result.mat[i][i] = 1;

    Matrix base = *this;
    while (exp > 0) {
      if (exp & 1) result = result * base;
      base = base * base;
      exp >>= 1;
    }
    return result;
  }
};
