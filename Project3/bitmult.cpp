/**
 * Copyright 2018 Hunter Damron
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

const size_t S = sizeof(char);

string bfmult(string A, string B) {
  return "-1";
}

string kmult(string A, string B) {
  return "-1";
}

int main() {
  string A, B;
  getline(cin, A);
  getline(cin, B);
  cout << "Brute force:  " << bfmult(A, B) << endl;
  cout << "Karatsuba:  " << kmult(A, B) << endl;
}
