#include <iostream>
#include <string>
#include <vector>

void horse_move(int n, int m, int x, int y, int &counter) {
  if (x == m - 1 && y == n - 1) {
    counter++;
    return;
  }
  if (x + 2 < m && y + 1 < n) {
    horse_move(n, m, x + 2, y + 1, counter);
  }
  if (x + 1 < m && y + 2 < n) {
    horse_move(n, m, x + 1, y + 2, counter);
  }
}

int table_dp(int n, int m) {
  std::vector<std::vector<int>> table(n + 1, std::vector<int>(m + 1, 0));
  table[1][1] = 1;
  for (int i = 2; i <= n; i++) {
    for (int j = 2; j <= m; j++) {
      table[i][j] = (table[i - 2][j - 1] + table[i - 1][j - 2]);
    }
  }
  return table[n][m];
}

int main(void) {
  int n, m, counter = 0;
  std::cin >> n >> m;

  //   horse_move(n, m, 0, 0, counter);
  counter = table_dp(n, m);
  std::cout << counter << "\n";
  return 0;
}