#include <cstdint>
#include <iostream>
#include <vector>
enum Direction { RIGHT, DOWN, START };
int global_total = INT32_MAX;
int dfs(const std::vector<std::vector<int>>& matrix, int n, int m, int total,
        int x, int y, Direction direction) {
  if (total >= global_total) {
    return total;
  }
  if (direction == RIGHT) {
    x++;
  } else if (direction == DOWN) {
    y++;
  } else if (direction == START) {
    total = 0;
  }

  if (y < n - 1 && x < m - 1) {
    int r1 = 0, r2 = 0;
    r1 = dfs(matrix, n, m, total + matrix[y][x], x, y, RIGHT);
    r2 = dfs(matrix, n, m, total + matrix[y][x], x, y, DOWN);
    total = std::min(r1, r2);
  } else {
    if (y == n - 1 && x < m - 1) {
      total = dfs(matrix, n, m, total + matrix[y][x], x, y, RIGHT);
    } else if (y < n - 1) {
      total = dfs(matrix, n, m, total + matrix[y][x - 1], x, y, DOWN);
    }
  }
  global_total = std::min(global_total, total);
  return total;
}

int dp(const std::vector<std::vector<int>>& matrix, int n, int m) {
  std::vector<std::vector<int>> res(n + 1, std::vector<int>(m + 1, INT32_MAX));

  res[0][1] = 0;
  res[1][0] = 0;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      res[i][j] = matrix[i - 1][j - 1] + std::min(res[i - 1][j], res[i][j - 1]);
    }
  }
  return res[n][m];
}

int main() {
  int n, m, res = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> matrix(n, std::vector<int>(m));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> matrix[i][j];
    }
  }

  // res = dfs(matrix, n, m, 0, 0, 0, START);
  res = dp(matrix, n, m);
  std::cout << res << "\n";
  return 0;
}
