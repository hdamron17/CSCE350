/**
 * Hunter Damron - Copyright 2018
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

long long comparisons = 0;  // Number of comparisons used in specific sorting algorithm

// Selection sort algorithm as discussed in class
void selectionsort(vector<int> &numbers) {
  int n = numbers.size();
  for (int i = 0; i < n-1; ++i) {
    int min = i;
    for (int j = i + 1; j < n; ++j) {
      if (numbers[j] < numbers[min]) {
        min = j;
      }
      ++comparisons;
    }
    int tmp = numbers[i];
    numbers[i] = numbers[min];
    numbers[min] = tmp;
  }
}

// Comparison used in qsort function which increments comparisons
// From project description
int qsortcmp(const void *ap, const void *bp) {
  ++comparisons;
  int a = *(int*)ap, b = *(int*)bp;
  if (a < b)  return -1;
  if (a == b) return 0;
  return 1;
}

// Comparison used in stl sort function which increments comparisons
// From project description
bool stlcmp(int i, int j) {
  ++comparisons;
  return i < j;
}

// Reads from stdin string name of sorting algorithm then a list of integers on
//   separate lines ending with 0
// Uses specific sorting algorithm according to specified input
// Outputs sorted list with each element on a line and the final line displaying the number of comparisons used (form "Comparisons: %d")
int main() {
  string alg;
  vector<int> numbers;

  cin >> alg;
  int input;
  cin >> input;
  while (input != 0) {
    numbers.push_back(input);
    cin >> input;
  }

  if (alg == "selection") {
    selectionsort(numbers);
  } else if (alg == "qsort") {
    qsort(&numbers[0], numbers.size(), sizeof(int), qsortcmp);
  } else if (alg == "stl") {
    sort(numbers.begin(), numbers.end(), stlcmp);
  }

  for (vector<int>::iterator v = numbers.begin(); v < numbers.end(); ++v) {
    cout << *v << endl;
  }
  cout << "Comparisons: " << comparisons << endl;
}
