#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

int dfs(const std::vector<int> &price, int s, int n, int &coupon,
        int total_cost, std::vector<int> &cd, int used) {
  int res = total_cost + (used == 0 ? price[s] : 0);
  if (used == 1) coupon--;
  if (price[s] > 100 && used == 0) coupon++;
  cd[s] = used;
  for (int i = s + 1; i < n; i++) {
    if (coupon > 0) {
      std::vector<int> r1_cd(cd), r2_cd(cd);
      int r1 = 0, r2 = 0, c1 = coupon, c2 = coupon;
      res = std::min(r1 = dfs(price, i, n, c1, res, r1_cd, 0),
                     r2 = dfs(price, i, n, c2, res, r2_cd, 1));
      if (r1 < r2) {
        cd = std::move(r1_cd);
        coupon = c1;
      } else if (r1 > r2) {
        cd = std::move(r2_cd);
        coupon = c2;
      } else {
        if (c1 > c2) {
          cd = std::move(r1_cd);
          coupon = c1;
        } else {
          cd = std::move(r2_cd);
          coupon = c2;
        }
      }
      break;
    } else {
      cd[i] = 0;
      res += price[i];
      if (price[i] > 100) coupon++;
    }
  }
  return res;
}

int main() {
  // Data input
  int n;
  std::cin >> n;
  std::vector<int> price(n);
  std::vector<int> used_days(n, 0);
  std::set<int> coupon_days;
  int K1 = 0, total_cost = 0, K2 = 0;
  if (n > 0 && n <= 100) {
    for (int i = 0; i < n; i++) {
      std::cin >> price[i];
    }
    // Main section
    total_cost = dfs(price, 0, n, K1, 0, used_days, 0);
    for (int i = 0; i < n; i++) {
      if (used_days[i] == 1) {
        coupon_days.insert(i);
        K2++;
      }
    }
  }
  // Result output
  std::cout << total_cost << "\n" << K1 << " " << K2 << "\n";
  for (auto day : coupon_days) {
    std::cout << day + 1 << "\n";
  }
  return 0;
}