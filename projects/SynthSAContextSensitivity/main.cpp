#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

#include <bit>
#include <cstdint>
#include <cstdio>
#include <limits>

/// This synthetic case study depcits a small computation tool that
///
/// The key idea is that boundsChecks needs a context sensitive static
/// analysis, otherwise the non-feature-related usages would be detected and
/// instrumented as well.

unsigned countLeadingZeros(unsigned Val) {
  if (!Val)
    return std::numeric_limits<unsigned>::digits;

  // Bisection method.
  unsigned ZeroBits = 0;
  for (unsigned Shift = std::numeric_limits<unsigned>::digits >> 1; Shift;
       Shift >>= 1) {
    unsigned Tmp = Val >> Shift;
    if (Tmp)
      Val = Tmp;
    else
      ZeroBits |= Shift;
  }
  return ZeroBits;
}

unsigned lowerBoundPowerOfTwo(unsigned Val) {
  return 1 << (std::numeric_limits<unsigned>::digits - 1 -
               countLeadingZeros(Val));
}

__attribute__((noinline)) unsigned boundsChecks(unsigned Val) {
  if (Val > 32768) {
    return 32768;
  };

  return Val; // Can be feature dependent
}

unsigned compute(unsigned BaseValue, unsigned Bound) {
  unsigned CheckedBound = boundsChecks(Bound);
  unsigned CheckedBaseValue = boundsChecks(BaseValue);

  unsigned PowOf2 = lowerBoundPowerOfTwo(CheckedBound);
  // Delay compute (indirectly based on MemoryLimit)
  fp_util::sleep_for_millisecs(PowOf2 * 100);

  // Delay compute (Based on user input and indirectly on MemoryLimit)
  fp_util::sleep_for_millisecs(CheckedBaseValue * CheckedBound * 2);

  return CheckedBaseValue * CheckedBound;
}

int main(int argc, char *argv[]) {
  bool __attribute__((feature_variable("Compress"))) Compress =
      fp_util::isFeatureEnabled(argc, argv, "--compress");
  unsigned __attribute__((feature_variable("MemoryLimit"))) MemoryLimit = 0;
  MemoryLimit = fp_util::getFeatureValue(argc, argv, "--mem");

  unsigned UserInput = std::stoul(argv[argc - 1]);
  std::printf("Running config (compress=%u, mem=%u, input=%u)\n", Compress,
              MemoryLimit, UserInput);

  uint64_t Result{};
  // load up time
  fp_util::sleep_for_secs(2);

  if (boundsChecks(MemoryLimit) < 256) { // 0 =< x < 256
    if (Compress) {
      Result = compute(UserInput, 9); // leads to less imprecise results
    } else {
      Result = compute(UserInput, 8); // leads to imprecise results
    }
  } else if (boundsChecks(MemoryLimit) < 1024) { // 256 =< x < 1024
    Result = compute(UserInput, 16);             // leads to imprecise results
  } else {
    Result = compute(UserInput, 250);
  }

  // shutdown time
  fp_util::sleep_for_secs(3);
  std::printf("Result: %lu\n", Result);

  return 0;
}
