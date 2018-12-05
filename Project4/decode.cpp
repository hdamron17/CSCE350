/**
 * Copyright 2018 Hunter Damron
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

unsigned long num_decodings(string s) {
  return 0;  // TODO not implemented
}

void print_decodings(string s) {
  std::cout << "Not implemented" << endl;  // TODO not implemented
}

int main() {
  string s;  // String containing encoded message
  unsigned long n;  // Number of decodings
  cin >> s;
  do {
    n = num_decodings(s);
    cout << n << endl;
    if (n <= 30)
      print_decodings(s);
    cin >> s;
  } while (cin);
}
