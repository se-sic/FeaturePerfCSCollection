//
// Created by abeltluk on 10/10/23.
//

#ifndef FEATUREPERFORMANCECASESTUDIE_ALGORITHM_H
#define FEATUREPERFORMANCECASESTUDIE_ALGORITHM_H
#include "Specializations.h"
#include "fp_util/sleep.h"

using namespace std;
using fp_util::busy_sleep_for_millisecs;
using fp_util::busy_sleep_for_secs;

struct Algorithm {
  void init() { busy_sleep_for_millisecs(1000); };

  template <typename StorageTy> void step1(StorageTy &S) {
    busy_sleep_for_millisecs(1000);
    access(S, 0);
    busy_sleep_for_millisecs(1000);
  }

  template <typename StorageTy> void step2(StorageTy &S) {
    busy_sleep_for_millisecs(1000);
    solve(S);
    busy_sleep_for_millisecs(1000);
  }

private:
  template <typename StorageTy>
  __attribute__((feature_variable("Solver"))) void solve(StorageTy &S) {
    access(S, 1);
  }
};

struct DirectSolvingAlgorithm {
  template <typename StorageTy>
  __attribute__((feature_variable("Solver"))) void
  solveForSolution(StorageTy &S) {
    busy_sleep_for_millisecs(1000);
    access(S, 1);
    busy_sleep_for_millisecs(1000);
  }
};

struct SmoothingAlgorithm {
  __attribute__((feature_variable("Smoother"))) void init() {
    busy_sleep_for_millisecs(1000);
  };

  void precomputeSmoothingParameters(size_t l) {
    busy_sleep_for_millisecs(1000);
  }

  template <typename StorageTy> void step1(StorageTy &S) {
    busy_sleep_for_millisecs(1000);
    access(S, 0);
    busy_sleep_for_millisecs(1000);
  }

  template <typename StorageTy> void step2(StorageTy &S) {
    busy_sleep_for_millisecs(1000);
    access(S, 1);
    busy_sleep_for_millisecs(1000);
  }

  template <typename StorageTy>
  __attribute__((feature_variable("Smoother"))) void smooth(StorageTy &S) {
    busy_sleep_for_millisecs(1000);
    access(S, 1);
    busy_sleep_for_millisecs(1000);
  }
};

template <typename AlgoTy>
__attribute__((feature_variable("Algorithm"))) void initAlgorithm(AlgoTy &A) {
  A.init();
}

template <>
__attribute__((feature_variable("Algorithm"))) void
initAlgorithm(SmoothingAlgorithm &A) {
  A.init();

  A.precomputeSmoothingParameters(42);
}

template <typename AlgoTy, typename StorageTy>
__attribute__((feature_variable("Algorithm"))) void runAlgorithm(AlgoTy &A,
                                                                 StorageTy &S) {
  A.step1(S);

  A.step2(S);
}

template <typename StorageTy>
__attribute__((feature_variable("Algorithm"))) void
runAlgorithm(DirectSolvingAlgorithm &A, StorageTy &S) {
  A.solveForSolution(S);
}

template <typename StorageTy>
__attribute__((feature_variable("Algorithm"))) void
runAlgorithm(SmoothingAlgorithm &A, StorageTy &S) {
  A.step1(S);

  A.smooth(S);

  A.step2(S);
}

#endif // FEATUREPERFORMANCECASESTUDIE_ALGORITHM_H
