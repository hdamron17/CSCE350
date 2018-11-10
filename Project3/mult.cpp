/**
 * Copyright 2018 Hunter Damron
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <algorithm>
using std::reverse;

const char numminus = '-' - '0';

// NOTE: For doing math, large numbers are represented as strings with
//       each decimal digit in a char in little endian. These are refered to as
//       number strings as opposed to raw strings.

/**
 * Adds a variable number of unsigned integers represented as number strings
 */
string uadd(const string nums[], const size_t n) {
  string result = "";
  bool done = false;
  unsigned int carry = 0, digitsum = 0;

  for (size_t i = 0; !done; ++i) {
    done = true;
    digitsum = carry;
    if (carry)
      done = false;
    for (size_t j = 0; j < n; ++j) {
      if (i < nums[j].length()) {
        digitsum += nums[j][i];
        done = false;
      }
    }
    if (!done) {
      carry = digitsum / 10;
      result += digitsum % 10;
    }
  }
  return result;
}

/**
 * Adds two unsigned integers as in `uadd`
 */
string uadd2(const string& A, const string& B) {
  return uadd((const string[]){A, B}, 2);
}

/**
 * Subtracts two unsigned integers as number strings
 */
string sub2(const string& A, const string& B) {
  bool neg = false;
  int n = (A.length() > B.length()) ? A.length() : B.length();

  // Iterate until one is different from the other
  for (n = A.length() - 1; n >= 0; --n) {
    char a = (n < A.length()) ? A[n] : 0;
    char b = (n < B.length()) ? B[n] : 0;
    if (a != b) {
      neg = a < b;
      break;
    }
  }
  n += 1;
  if (n == 0)
    return string() + (char) 0;  // If they are exactly equal, A - B = 0

  // references to longer and shorter strings so we can carry without worry
  const string &longer = (neg) ? B : A,
               &shorter = (neg) ? A : B;

  string result = "";
  bool stolen = false;  // Tells if the previous digit stole from current
  for (int i = 0; i < longer.length() && i < n; ++i) {
    // Iterate over the different digits and subtract stealing if necessary
    char top = longer[i],
         bottom = (i < shorter.length()) ? shorter[i] : 0;
    if (stolen) {
      // Subtracts one because it was stolen and resets the stolen flag
      top -= 1;
      stolen = false;
    }
    if (top < bottom) {
      // There is more to subtract then available so steal from next digit
      top += 10;
      stolen = true;
    }
    result += (top - bottom);  // Append the subtracted result
  }
  if (neg)
    result += numminus;  // Make it negative if it B > A
  return result;
}

/**
 * Pads a number string with zeros
 */
string pad(const string& N, const unsigned int shift=0) {
  return string(shift, '\0') + N;
}

/**
 * Multiplies a number string by a single digit factor
 */
string digitmult(const string& N, const char factor) {
  string result = N;
  char carry = 0;
  for (int i = 0; i < result.length(); ++i) {
    int digitsum = result[i] * factor + carry;
    carry = digitsum / 10;
    result[i] = digitsum % 10;
  }
  if (carry)
    result += carry;
  return result;
}

/**
 * Converts a regular string to a number string
 */
string num(const string &N) {
  string result = N;
  reverse(result.begin(), result.end());
  for (char &c : result)
    c -= '0';
  return result;
}

/**
 * Converts a number string back to a regular string
 */
string str(const string &N) {
  string result = "";
  // for (char c : N) {
  bool zeros = true;
  for (int i = N.length() - 1; i >= 0; --i) {
    if (zeros && !N[i])
      continue;
    result += N[i] + '0';
    zeros = false;
  }
  if (result.empty())
    return "0";  // If empty string, this represents 0
  return result;
}

/**
 * Does brute force multiplication of unsigned integers as number strings
 */
string bfmult(string A, string B) {
  size_t n = B.length();
  string nums[n];
  for (size_t i = 0; i < n; ++i) {
    // Multiplies A by each digit of B with padding
    nums[i] = pad(digitmult(A, B[i]), i);
  }
  return uadd(nums, n);  // Sums the result
}

/**
 * Does Karatsuba multiplication of unsigned integers as number strings
 */
string kmult(string A, string B) {
  // If either is empty, the result is 0
  if (A.length() == 0 || B.length() == 0) {
    return string() + (char) 0;
  }
  // If both are one digit, multiply them normally
  if (A.length() == 1 && B.length() == 1) {
    int value = A[0] * B[0];
    string ret = "";
    ret += value % 10;
    if (value >= 10)
      ret += value / 10;
    return ret;
  }

  size_t Al = A.length(), Bl = B.length();
  size_t m = ((Al > Bl) ? Al : Bl) / 2;  // Sets m to be half of longer length

  // Split up inputs using m
  string A0 = A.substr(0, m),
         A1 = (m < Al) ? A.substr(m, m+1) : "",
         B0 = B.substr(0, m),
         B1 = (m < Bl) ? B.substr(m, m+1) : "";

  // Multiply each part recursively
  string C0 = kmult(A0, B0),
         C2 = kmult(A1, B1),
         C1 = sub2(kmult(uadd2(A0, A1), uadd2(B0, B1)), uadd2(C2, C0));

  // Applies padding for each part of Karatsuba multiplication
  string pC1 = C1.empty() ? C1 : pad(C1, m),
         pC2 = C2.empty() ? C2 : pad(C2, 2*m);
  string toadd[] = {pC2, pC1, C0};

  return uadd(toadd, 3);
}

enum mtype { BRUTE_FORCE, KARATSUBA };

/**
 * Multiplies two signed integers as regular strings using a specified method
 */
string mult(const string &A, const string &B, const mtype &type) {
  bool Aneg = !A.empty() && A.front() == '-',
       Bneg = !B.empty() && B.front() == '-';
  string nA = Aneg ? num(A.substr(1)) : num(A),
         nB = Bneg ? num(B.substr(1)) : num(B);

  string nproduct;
  switch (type) {
    case BRUTE_FORCE:
      nproduct = bfmult(nA, nB);
      break;
    case KARATSUBA:
      nproduct = kmult(nA, nB);
      break;
  }
  string product = str(nproduct);
  if (Aneg != Bneg)
    product = "-" + product;  // Negative if one is negative and not the other
  return product;
}

int main() {
  string A, B;
  getline(cin, A);
  getline(cin, B);

  cout << "Brute Force:  " << mult(A, B, BRUTE_FORCE) << endl;
  cout << "Karatsuba:  " << mult(A, B, KARATSUBA) << endl;
}
