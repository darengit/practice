#include <string>
#include <stdio.h>


int maxNumberOfDivisorsPermutation(int n) {

  std::string digits = std::to_string(n);
  std::sort(digits.begin(), digits.end());
  int bestDivCnt = 1;
  int bestNumber = n;
  while (true) {
    // Checking the number of divisors.
    int cur = std::stoi(digits);
    int divisors = 0;
    for (int i = 1; i <= cur; i++) {
      if (cur % i == 0) {
        divisors++;
      }
    }
    if (divisors >= bestDivCnt) {
      bestDivCnt = divisors;
      bestNumber = cur;
    }

    // Obtaining the next permutation.
    int first;
    for (first = (int)digits.size() - 2; first >= 0; first--) {
      if (digits[first] < digits[first + 1]) {
        break;
      }
    }
    if (first == -1) {
      break;
    }
    int second = first + 1;
    while (second+1 < (int)digits.size() && digits[first] < digits[second+1]) {
      second++;
    }
    std::swap(digits[first], digits[second]);
    first++;
    second = (int)digits.size() - 1;
    while (first < second) {
      std::swap(digits[first], digits[second]);
      first++;
      second--;
    }

	printf("%s\n", digits.c_str());
  }

  return bestNumber;
}

int main() {
	maxNumberOfDivisorsPermutation(12345);
	return 0;
}
