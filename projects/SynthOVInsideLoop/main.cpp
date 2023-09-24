#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>

/// This synthetic case study targets cases where configurability is used
/// inside a hot loop.
///
/// --reverse   : reverse input order
/// --verbose   : print all target steps
/// --sum       : the sum the subarray should have
///
/// The key idea is that configuration-specific code is sometimes located
/// inside hot loops, applying additional presure to measurement code.
///
std::vector<uint32_t> findMaxLenSubarray(std::vector<uint32_t> DataArray, int S,
                                         bool Verbose = false) {
  int MaxLength = 0;
  int EndingIndex = -1;

  for (int i = 0; i < DataArray.size(); i++) {
    int Target = 0;

    for (int j = i; j < DataArray.size(); j++) {
      Target += DataArray[j];
      if (Verbose) {
        std::cout << "CurrentTarget " << Target << '\n';
      }

      fp_util::busy_sleep_for_millisecs(10);
      if (Target == S) {
        if (MaxLength < j - i + 1) {
          MaxLength = j - i + 1;
          EndingIndex = j;
        }
      }
    }
  }

  // printf("[%d, %d]\n", EndingIndex - MaxLength + 1, EndingIndex);

  return {std::next(DataArray.begin(), EndingIndex - MaxLength + 1),
          std::next(DataArray.begin(), EndingIndex + 1)};
}

// ./InsideLoop --sum X INPUT_DATA
// where INPUT_DATA = 1,2,3,4,5,6
// INPUT_DATA needs to be at least one value
//
int main(int argc, char *argv[]) {

  uint32_t TargetSum = fp_util::getFeatureValue(argc, argv, "--sum", 1);
  bool __attribute__((feature_variable("Reverse"))) Reverse =
      fp_util::isFeatureEnabled(argc, argv, "--reverse");
  bool __attribute__((feature_variable("Verbose"))) Verbose =
      fp_util::isFeatureEnabled(argc, argv, "--verbose");
  std::string_view InputData = argv[argc - 1];

  std::vector<uint32_t> Values;
  size_t Start = 0;
  while (Start < InputData.length()) {
    size_t NextDelim =
        std::min(InputData.find_first_of(',', Start), InputData.length());
    uint32_t Val =
        std::stol(std::string(InputData.substr(Start, NextDelim - Start)));
    Values.push_back(Val);

    Start = NextDelim + 1;
  }
  if (Reverse) {
    std::reverse(Values.begin(), Values.end());
  }

  auto SubArray = findMaxLenSubarray(Values, TargetSum, Verbose);

  std::string Sep;
  std::cout << "Subarray: [";
  for (auto Val : SubArray) {
    std::cout << Sep << Val;
    Sep = ", ";
  }
  std::cout << "]\n";

  return 0;
}
