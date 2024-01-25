/*
 2. Самый дешевый путь
В каждой клетке прямоугольной таблицы N×M записано некоторое число. Изначально
игрок находится в левой верхней клетке. За один ход ему разрешается перемещаться
в соседнюю клетку либо вправо, либо вниз (влево и вверх перемещаться запрещено).
При проходе через клетку с игрока берут столько килограммов еды, какое число
записано в этой клетке (еду берут также за первую и последнюю клетки его пути).

Требуется найти минимальный вес еды в килограммах, отдав которую игрок может
попасть в правый нижний угол.

Формат ввода
Вводятся два числа N и M — размеры таблицы (1≤N≤20,1≤M≤20). Затем идет N строк
по M чисел в каждой — размеры штрафов в килограммах за прохождение через
соответствующие клетки (числа от 0 до 100).

Формат вывода
Выведите минимальный вес еды в килограммах, отдав которую можно попасть в правый
нижний угол.

Пример 1
Ввод
5 5
1 1 1 1 1
3 100 100 100 100
1 1 1 1 1
2 2 2 2 1
1 1 1 1 1
Вывод
11
*/
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
