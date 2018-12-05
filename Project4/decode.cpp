/**
 * Copyright 2018 Hunter Damron
 */

/**
 * Calculates the number of decodings of the encoding provided by Steranko
 * Uses dynamic programming algorithm for the following recurrence:
 *
 *   Input: list S[0, ..., n-1]
 *   Recurrence:
 *     P[n] = 0
 *     P[n-1] = 1
 *             / P[i+1] + P[i+2]  if  (S[i] = 1 or (S[i] = 2 and S[i+1] < 6)
 *     P[i] = {
 *             \ P[i+1]           otherwise
 *
 * P[n] signifies the empty list after the end of the list which has no decoding
 * P[n-1] signifies the last character which can only be decoded as 1
 * The first case of P[i] is when the first two numbers can signify either a
 *   letter >= 10 or two letters < 10 so we add the number of possibilities for
 *   decoding the remaining strings in each case.
 * The second case of P[i] is when the first number can only be treated as a
 *   single character so there are exactly as many decodings as there are of the
 *   remaining string.
 *
 * If n is 0, doing the above operation would cause an out of bounds error so 0
 *   is returned immediately.
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <cstdbool>

bool is_two_digit(const string& s, const int i) {
  return s[i] == '1' || (s[i] == '2' && s[i+1] <= '6');
}

int num_decodings(string s) {
  int n = s.length();
  if (n == 0)
    return 0;  // Empty string cannot be decoded in any way

  int partial_decodings[n+1];  // Answer to subproblem filled in from end
  partial_decodings[n] = 1;    // The empty string again gets 0
  partial_decodings[n-1] = 1;  // A single character can only be single digit

  for (int i = n - 2; i >= 0; --i) {
    partial_decodings[i] = partial_decodings[i+1];  // Can always be single
    if (is_two_digit(s, i)) {
      // If a two digit number could be formed with the first two, add remaining
      partial_decodings[i] += partial_decodings[i+2];
    }
  }
  return partial_decodings[0];  // This is the solution for the whole string
}

char decode(char c) {
  return (c - '0') + 'a';  // Convert to letter < 10
}

char decode(char c1, char c0) {
  return (c1 - '0') * 10 + (c0 - '0') + 'a';  // Convert to letter >= 10
}

void print_decodings(string s, string prefix="") {
  int n = s.length();
  if (n == 0) {
    cout << prefix << endl;  // Print only the prefix for empty string
  } else if (n == 1) {
    cout << prefix << decode(s[0]) << endl;  // Single letter only one way
  } else {
    // Print decodings for single character encoding
    print_decodings(s.substr(1), prefix + decode(s[0]));
    if (is_two_digit(s, 0)) {
      // Print decodings when treating first two as a letter
      print_decodings(s.substr(2), prefix + decode(s[0], s[1]));
    }
    // Note this will be alphabetical because strings beginning with a letter
    //   < 10 are always printed before strings starting with a letter >= 10
  }
}

int main() {
  string s;  // String containing encoded message
  int n;  // Number of decodings
  cin >> s;
  do {
    n = num_decodings(s);
    cout << n << endl;
    if (n <= 30 && n > 0)  // Print when less than 30 and there are any
      print_decodings(s);
    cin >> s;
  } while (cin);
}
