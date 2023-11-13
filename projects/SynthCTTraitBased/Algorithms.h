#ifndef FEATUREPERFORMANCECASESTUDIE_ALGORITHMS_H
#define FEATUREPERFORMANCECASESTUDIE_ALGORITHMS_H
#include "TraitDefinitions.h"
#include "fp_util/sleep.h"

using namespace std;
using fp_util::busy_sleep_for_millisecs;
using fp_util::busy_sleep_for_secs;

// Empty default implementations
// We currently cannot analyse if constexpr, so we need those
struct NullAlgorithm {
  void initA(){};
  void initB(){};
  template <typename StorageTy> void processA(StorageTy &S){};
  template <typename StorageTy> void processB(StorageTy &S){};
  template <typename StorageTy> void processAB(StorageTy &S){};
  template <typename StorageTy> void run(StorageTy &) {}
};

struct AlgorithmWithA : public NullAlgorithm {
  __attribute__((feature_variable("A"))) void initA() {
    busy_sleep_for_millisecs(1000);
  }

  template <typename StorageTy>
  __attribute__((feature_variable("A"))) void processA(StorageTy &S) {
    busy_sleep_for_millisecs(1000);

    S.get();

    busy_sleep_for_millisecs(1000);
  }
};

struct OtherAlgorithmWithA : public NullAlgorithm {
  __attribute__((feature_variable("A"))) void initA() {
    busy_sleep_for_millisecs(1000);
  }

  template <typename StorageTy>
  __attribute__((feature_variable("A"))) void processA(StorageTy &S) {
    busy_sleep_for_millisecs(1000);

    S.get();

    if (StorageTraits<StorageTy>::HasComponentC) {
      S.processC();
    }

    busy_sleep_for_millisecs(1000);
  }

  template <typename StorageTy> void run(StorageTy &S) {
    if (StorageTraits<StorageTy>::HasComponentD) {
      S.processD();
    }
  }
};

struct AlgorithmWithB : public NullAlgorithm {
  __attribute__((feature_variable("B"))) void initB() {
    busy_sleep_for_millisecs(1000);
  }

  template <typename StorageTy>
  __attribute__((feature_variable("B"))) void processB(StorageTy &S) {
    busy_sleep_for_millisecs(1000);

    S.get();

    busy_sleep_for_millisecs(1000);
  }
};

struct AlgorithmWithAB : public NullAlgorithm {
  __attribute__((feature_variable("A"))) void initA() {
    busy_sleep_for_millisecs(1000);
  }

  __attribute__((feature_variable("B"))) void initB() {
    busy_sleep_for_millisecs(1000);
  }

  template <typename StorageTy>
  __attribute__((feature_variable("A"))) void processA(StorageTy &S) {
    busy_sleep_for_millisecs(1000);

    S.get();

    busy_sleep_for_millisecs(1000);
  }

  template <typename StorageTy>
  __attribute__((feature_variable("B"))) void processB(StorageTy &S) {
    busy_sleep_for_millisecs(1000);
    if (StorageTraits<StorageTy>::HasComponentC &&
        StorageTraits<StorageTy>::HasComponentD) {
      S.get();
    }
    busy_sleep_for_millisecs(1000);
  }

  template <typename StorageTy>
  __attribute__((feature_variable("A"), feature_variable("B"))) void
  processAB(StorageTy &S) {
    busy_sleep_for_millisecs(1000);

    if (StorageTraits<StorageTy>::HasComponentD) {
      S.processD();
    }

    S.get();

    busy_sleep_for_millisecs(1000);
  }
};

// Trait specializations
template <> struct AlgorithmTraits<AlgorithmWithA> {
  __attribute__((feature_variable("A"))) static const bool HasComponentA = true;
  __attribute__((feature_variable("B"))) static const bool HasComponentB =
      false;
};

template <> struct AlgorithmTraits<OtherAlgorithmWithA> {
  __attribute__((feature_variable("A"))) static const bool HasComponentA = true;
  __attribute__((feature_variable("B"))) static const bool HasComponentB =
      false;
};

template <> struct AlgorithmTraits<AlgorithmWithB> {
  __attribute__((feature_variable("A"))) static const bool HasComponentA =
      false;
  __attribute__((feature_variable("B"))) static const bool HasComponentB = true;
};

template <> struct AlgorithmTraits<AlgorithmWithAB> {
  __attribute__((feature_variable("A"))) static const bool HasComponentA = true;
  __attribute__((feature_variable("B"))) static const bool HasComponentB = true;
};
#endif // FEATUREPERFORMANCECASESTUDIE_ALGORITHMS_H
