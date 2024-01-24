#include <cstdint>
#include <iostream>
#include <vector>

int main() {
  int m, n;
  std::cin >> n >> m;
  std::vector<std::vector<int>> matrix(n, std::vector<int>(m));
  std::vector<std::vector<int>> res(n + 1, std::vector<int>(m + 1, -1));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> matrix[i][j];
    }
  }
  res[0][1] = 0;
  res[1][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      res[i][j] = matrix[i - 1][j - 1] + std::max(res[i - 1][j], res[i][j - 1]);
    }
  }
  std::cout << res[n][m] << "\n";

  std::vector<char> path;
  for (int i = n, j = m; i > 1 || j > 1;) {
    char letter;
    if (res[i - 1][j] > res[i][j - 1]) {
      letter = 'D';
      i--;
    } else {
      letter = 'R';
      j--;
    }
    path.insert(path.begin(), letter);
  }
  for (auto letter : path) {
    std::cout << letter << " ";
  }
  std::cout << "\n";

  return 0;
}