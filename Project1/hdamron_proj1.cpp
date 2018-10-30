/**
 * Hunter Damron - 2018
 */

#include <iostream>

int main() {
  unsigned int slices[4] = {0, 0, 0, 0};
  unsigned int sum = 0;
  while(true) {
    std::cin >> slices[0] >> slices[1] >> slices[2] >> slices[3];
    sum = slices[0] + slices[1] + slices[2] + slices[3];
    if (sum != 0) {
      std::cout << sum << std::endl;
    } else {
      break;
    }
  }
}
