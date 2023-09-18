#include "fp_util/sleep.h"
#include <vector>

using namespace std;
using fp_util::busy_sleep_for_millisecs;
using fp_util::busy_sleep_for_secs;

struct RandomStoragePolicy;
struct DefaultCachingPolicy;
struct DefaultTransformerPolicy;

template <typename CreationPolicy = RandomStoragePolicy> class Storage {
  vector<double> Data;

public:
  explicit Storage(size_t n) {
    CreationPolicy Create{};

    Data = Create.createData(n);
  }
};

template <typename CachingPolicy> class Weights {
  CachingPolicy C{};
  std::vector<int> _weights;

public:
  __attribute__((feature_variable("Weights"))) explicit Weights(size_t n) {
    busy_sleep_for_millisecs(1000);
    _weights = std::vector<int>(n, 2);
  }

  void createCache() { C.create(); }

  void getCached() { C.access(); }
};

template <typename TransformerPolicy = DefaultTransformerPolicy>
class Transformer {
  TransformerPolicy T{};

public:
  Transformer() { T.init(); }

  template <typename Ty> void setupWeights(Weights<Ty> &W) { T.initWeights(W); }

  template <typename Ty> void apply(Storage<> S, Weights<Ty> W) {
    T.transform(S, W);
  }
};

struct RandomStoragePolicy {
  __attribute__((feature_variable("Storage"))) vector<double>
  createData(size_t n) {
    // TODO
    busy_sleep_for_millisecs(1000);
    return {};
  }
};

struct DefaultCachingPolicy {
  __attribute__((feature_variable("Weights"))) void create() {
    busy_sleep_for_millisecs(1000);
  }

  __attribute__((feature_variable("Weights"))) void access() {
    busy_sleep_for_millisecs(1000);
  }
};

struct DefaultTransformerPolicy {
  __attribute__((feature_variable("Transformer"))) void init() {
    busy_sleep_for_millisecs(1000);
  }

  template <typename T>
  __attribute__((feature_variable("Transformer"))) void
  initWeights(Weights<T> &W) {
    busy_sleep_for_millisecs(1000);
    W.createCache();
    busy_sleep_for_millisecs(1000);
  }

  template <typename T>
  __attribute__((feature_variable("Transformer"))) void
  transform(Storage<> S, Weights<T> W) {
    busy_sleep_for_millisecs(1000);
    W.getCached();
    busy_sleep_for_millisecs(1000);
  }
};

template <typename StorageTy, typename TransformerTy, typename WeightsTy>
__attribute__((feature_variable("Storage"))) void
manipulateStorage(StorageTy Storage, TransformerTy Transform,
                  WeightsTy Weights) {

  busy_sleep_for_millisecs(1000);
  Transform.apply(Storage, Weights);
  busy_sleep_for_millisecs(1000);
}

int main(/* int argc, char *argv[] */) {
  busy_sleep_for_secs(1);

  // Specific to storage
  Storage<> DataStorage{10};

  busy_sleep_for_secs(1);

  // Specific to feature B
  Transformer<> T{};

  busy_sleep_for_secs(1);

  // Specific to feature C
  Weights<DefaultCachingPolicy> W{10};

  busy_sleep_for_secs(1);

  // Interaction B&C
  T.setupWeights(W);

  busy_sleep_for_secs(1);

  // Interaction A&B&C
  manipulateStorage(DataStorage, T, W);

  busy_sleep_for_secs(1);

  return 0;
}
