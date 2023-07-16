#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

#include <cstdio>

/// This synthetic case study depicts a TODO with three feature flags.
///
/// The key idea is that come code is only feature dependent after a specific
/// point in the program. Hence, an analysis needs to be flow sensitivity to
/// differentiate that one location should be measured where the other does
/// not.

const unsigned MAX_CUTOFF = 80;

__attribute__((noinline)) uint64_t compute_fib_inc(unsigned N) {
  uint64_t Res;
  uint64_t Res_1 = 0, Res_2 = 1;

  if (N == 0) {
    return Res_1;
  }

  for (int i = 2; i <= N; i++) {
    Res = Res_1 + Res_2;
    Res_1 = Res_2;
    Res_2 = Res;

    fp_util::sleep_for_millisecs(500);
  }

  return Res;
}

__attribute__((noinline)) uint64_t compute_fib_rec(unsigned N) {
  if (N == 0) {
    return 0;
  }
  if (N == 1) {
    return 1;
  }

  fp_util::sleep_for_millisecs(500);
  return compute_fib_rec(N - 1) + compute_fib_rec(N - 2);
}

int main(int argc, char *argv[]) {

  // Flag: compute recursive
  volatile bool Recursive __attribute__((feature_variable("Recursive"))) =
      fp_util::isFeatureEnabled(argc, argv, "--rec");

  // Flag:
  unsigned __attribute__((feature_variable("CutOff"))) CutOff =
      fp_util::getFeatureValue(argc, argv, "--cutoff", 20);

  unsigned UserInput = std::stoul(argv[argc - 1]);

  volatile bool DoRecursive = argc >= 2;
  uint64_t Result{};
  uint64_t PreResult{};

  CutOff = CutOff < MAX_CUTOFF ? CutOff : MAX_CUTOFF;
  unsigned TargetN = UserInput > CutOff ? CutOff : UserInput;

  // Pre-run (Just always do a pre-run but reuse variable to require flow
  // sensitivity)
  if (DoRecursive) { // Should not be instrumented
    PreResult = compute_fib_inc(TargetN);
  }

  // Make next run, feature dependent. Hence, only an analysis that is flow
  // sensitive will find the one below but not above.
  DoRecursive = Recursive;

  if (DoRecursive) {
    Result = compute_fib_rec(TargetN);
  } else {
    // Take care, without config information, we only attribute this to Feature
    // Recursive
    Result = compute_fib_inc(TargetN);
  }

  fp_util::sleep_for_secs(3);
  if (PreResult != Result) {
    std::printf("Computation Error: %lu != %lu\n", Result, PreResult);
  }
  std::printf("Result: %lu\n", Result);

  return 0;
}
