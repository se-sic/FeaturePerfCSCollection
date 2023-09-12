#include "fp_util/sleep.h"

using namespace std;
using fp_util::busy_sleep_for_millisecs;
using fp_util::busy_sleep_for_secs;

template <typename AlgoTy> struct ConfigTraits {
  __attribute__((feature_variable("A"))) static void featureA(AlgoTy &Algo,
                                                              size_t n) {
    Algo.runFeatureA(n);
  }

  __attribute__((feature_variable("B"))) static void featureB(AlgoTy &Algo,
                                                              size_t n) {
    Algo.runFeatureB(n);
  }

  __attribute__((feature_variable("C"))) static void featureC(AlgoTy &Algo,
                                                              size_t n) {
    Algo.runFeatureC(n);
  }

  __attribute__((feature_variable("C"))) static void IndFeatureC(AlgoTy &Algo,
                                                                 size_t n) {
    Algo.runFeatureC(n);
  }

  __attribute__((feature_variable("B"))) static void interactionBC(AlgoTy &Algo,
                                                                   size_t n) {
    busy_sleep_for_secs(1);

    // Interaction code:
    IndFeatureC(Algo, n);

    busy_sleep_for_secs(1);
  }

  __attribute__((feature_variable("A"))) static void
  interactionABC(AlgoTy &Algo, size_t n) {
    busy_sleep_for_secs(1);

    // Interaction Code:
    interactionBC(Algo, n);

    busy_sleep_for_secs(1);
  }
};

template <typename AlgoTy> struct GenericImpl {
  void run(size_t n) {
    busy_sleep_for_secs(1);

    // Specific to feature A
    ConfigTraits<AlgoTy>::featureA(_alg, n);

    busy_sleep_for_secs(1);

    // Specific to feature B
    ConfigTraits<AlgoTy>::featureB(_alg, n);

    busy_sleep_for_secs(1);

    // Specific to feature C
    ConfigTraits<AlgoTy>::featureC(_alg, n);

    busy_sleep_for_secs(1);

    // Interaction B&C
    ConfigTraits<AlgoTy>::interactionBC(_alg, n);

    busy_sleep_for_secs(1);

    // Interaction A&B&C
    ConfigTraits<AlgoTy>::interactionABC(_alg, n);

    busy_sleep_for_secs(1);
  }

private:
  AlgoTy _alg{};
};

struct AlgorithmOne {
  void runFeatureA(size_t n) { busy_sleep_for_millisecs(n); }

  void runFeatureB(size_t n) { busy_sleep_for_millisecs(n); }

  void runFeatureC(size_t n) { busy_sleep_for_millisecs(n); }
};

int main() {
  GenericImpl<AlgorithmOne> Impl{};
  Impl.run(2000);

  return 0;
}
