#include "Algorithms.h"
#include "Storage.h"

template <typename AlgoTy, typename StorageTy> struct GenericImpl {
  void run() {
    initComponents();

    process();
  }

private:
  using AlgoTraits = AlgorithmTraits<AlgoTy>;
  using StrgTraits = StorageTraits<StorageTy>;

  void initComponents() {
    if constexpr (AlgoTraits::HasComponentA) {
      _alg.initA();
    }

    if constexpr (AlgoTraits::HasComponentB) {
      _alg.initB();
    }

    if constexpr (StrgTraits::HasComponentC) {
      _strg.initC();
    }

    if constexpr (StrgTraits::HasComponentD) {
      _strg.initD();
    }
  }

  void process() {

    _strg.get();
    _alg.run(_strg);

    if constexpr (AlgoTraits::HasComponentA) {
      _alg.processA(_strg);
    }

    if constexpr (AlgoTraits::HasComponentB) {
      _alg.processB(_strg);
    }

    if constexpr (AlgoTraits::HasComponentA && AlgoTraits::HasComponentB) {
      _alg.processAB(_strg);
    }

    if constexpr (StrgTraits::HasComponentC) {
      _strg.processC();
    }

    if constexpr (StrgTraits::HasComponentD) {
      _strg.processD();
    }
  }

  AlgoTy _alg{};
  StorageTy _strg{};
};

int main() {
  GenericImpl<NullAlgorithm, StorageWithCD> Impl{};
  Impl.run();

  return 0;
}
