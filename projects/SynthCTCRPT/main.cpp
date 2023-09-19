#include "fp_util/sleep.h"
#include <vector>

using namespace std;
using fp_util::busy_sleep_for_millisecs;
using fp_util::busy_sleep_for_secs;

template <typename T> class CRPT {
protected:
  T &underlying() { return static_cast<T &>(*this); }
};

template <typename T> struct DataManipulator : CRPT<T> {

  std::vector<double> createData(std::size_t n) {
    return this->underlying().createData(n);
  }

  void manipulateData(std::vector<double> &Data) {
    this->underlying().manipulateData(Data);
  }
};

template <typename T> struct Caching : CRPT<T> {
  void init() { this->underlying().init(); }

  void createCache() { this->underlying().createCache(); }

  void getCached() { this->underlying().getCached(); }
};

template <typename T> struct Transformer : CRPT<T> {
  void init() { this->underlying().init(); }

  void prepareTransformation() { this->underlying().prepareTransformation(); }

  void transform(std::vector<double> &Data) {
    this->underlying().transform(Data);
  }
};

template <typename T1>
class TransformingStorage : public DataManipulator<TransformingStorage<T1>> {
  Transformer<T1> &Transformer;

public:
  explicit TransformingStorage(::Transformer<T1> &Transformer)
      : Transformer(Transformer) {}

  std::vector<double> createData(std::size_t n) {
    // TODO
    busy_sleep_for_millisecs(1000);

    return {};
  }

  void manipulateData(std::vector<double> &Data) {
    busy_sleep_for_millisecs(1000);

    Transformer.transform(Data);

    busy_sleep_for_millisecs(1000);
  }
};

template <typename T1>
class CachingTransformer : public Transformer<CachingTransformer<T1>> {
  Caching<T1> &Cache;

public:
  explicit CachingTransformer(Caching<T1> &Cache) : Cache(Cache) {}

  void init() { busy_sleep_for_millisecs(1000); }

  void prepareTransformation() {
    busy_sleep_for_millisecs(1000);

    Cache.createCache();

    busy_sleep_for_millisecs(1000);
  }

  void transform(std::vector<double> &Data) {
    busy_sleep_for_millisecs(1000);

    Cache.getCached();

    busy_sleep_for_millisecs(1000);
  }
};

class Weights : public Caching<Weights> {
public:
  void init() { busy_sleep_for_millisecs(1000); }

  void createCache() { busy_sleep_for_millisecs(1000); }

  void getCached() { busy_sleep_for_millisecs(1000); }
};

template <typename T1, typename T2, typename T3>
void runAlgorithm(Caching<T1> &Cache, Transformer<T2> &Transformer,
                  DataManipulator<T3> &Storage) {
  // Perform "algorithm"
  busy_sleep_for_secs(1);

  // Single feature "Storage"
  auto Data = Storage.createData(10);

  busy_sleep_for_secs(1);

  // Single Feature "Transformer"
  Transformer.init();

  busy_sleep_for_secs(1);

  // Single Feature "Cache"
  Cache.init();

  busy_sleep_for_secs(1);

  // Interaction "Cache" & "Transformer"
  Transformer.prepareTransformation();

  busy_sleep_for_secs(1);

  // Interaction of all features
  Storage.manipulateData(Data);

  busy_sleep_for_secs(1);
}

int main(/* int argc, char *argv[] */) {
  // Specify the Weights
  Weights W{};

  // Specify a Transformer
  CachingTransformer<Weights> Transformer{W};

  // Specify a Storage
  TransformingStorage<CachingTransformer<Weights>> Storage{Transformer};

  runAlgorithm(W, Transformer, Storage);
  return 0;
}
