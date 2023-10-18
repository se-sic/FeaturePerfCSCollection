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
    if (AlgoTraits::HasComponentA) {
      _alg.initA();
    }

    if (AlgoTraits::HasComponentB) {
      _alg.initB();
    }

    if (StrgTraits::HasComponentC) {
      _strg.initC();
    }

    if (StrgTraits::HasComponentD) {
      _strg.initD();
    }
  }

  void process() {

    _strg.get();
    _alg.run(_strg);

    if (AlgoTraits::HasComponentA) {
      _alg.processA(_strg);
    }

    if (AlgoTraits::HasComponentB) {
      _alg.processB(_strg);
    }

    if (AlgoTraits::HasComponentA && AlgoTraits::HasComponentB) {
      _alg.processAB(_strg);
    }

    if (StrgTraits::HasComponentC) {
      _strg.processC();
    }

    if (StrgTraits::HasComponentD) {
      _strg.processD();
    }
  }

  AlgoTy _alg{};
  StorageTy _strg{};
};

int main() {
  GenericImpl<NullAlgorithm, NullStorage> Impl{};
  Impl.run();

  return 0;
}
