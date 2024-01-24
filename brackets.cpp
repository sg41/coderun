#include <iostream>
#include <string>
void generate(const std::string &str, int open, int close, int n) {
  if (str.size() == 2 * n) {
    std::cout << str;
    return;
  }
  if (open < n) generate(str + "(", open + 1, close, n);
  if (close < open) generate(str + ")", open, close + 1, n);
}

int main(void) {
  int n;
  std::cin >> n;
  generate("", 0, 0, n);
  return 0;
}