#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

#include <bit>
#include <cstdint>
#include <cstdio>
#include <limits>

/// This synthetic case study depcits a small computation tool that
///
/// The key idea is that lowerBoundPowerOfTwo needs a context sensitive static
/// analysis, otherwise the non-feature-related usages would be detected and
/// instrumented as well.

unsigned lowerBoundPowerOfTwo(unsigned Val) {
  // TODO: check if the analysis can look through this call
  return 1 << (std::numeric_limits<unsigned>::digits - 1 - __builtin_clzl(Val));
}

unsigned compute(unsigned BaseValue, unsigned Bound) {
  unsigned PowOf2 = lowerBoundPowerOfTwo(Bound);
  // Delay compute (indirectly based on MemoryLimit)
  fp_util::sleep_for_millisecs(PowOf2 * 100);

  fp_util::sleep_for_millisecs(BaseValue * Bound * 2);

  return BaseValue * Bound;
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

  if (lowerBoundPowerOfTwo(MemoryLimit) < 256) { // 0 =< x < 256
    if (Compress) {
      Result = compute(UserInput, 9); // leads to less imprecise results
    } else {
      Result = compute(UserInput, 8); // leads to imprecise results
    }
  } else if (lowerBoundPowerOfTwo(MemoryLimit) < 1024) { // 256 =< x < 1024
    Result = compute(UserInput, 16); // leads to imprecise results
  } else {
    Result = compute(UserInput, 250);
  }

  std::printf("Result: %lu\n", Result);

  return 0;
}
