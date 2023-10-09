#include "Storage.h"
#include "Transformer.h"

template <typename StorageTy, typename TransformerTy> struct GenericAlgorithm {
  void run() {
    initComponents();
    process();
  }

private:
  void initComponents() {
    _strg.init();
    _transform.init();
  }

  void process() {
    _transform.transformOperation1(_strg);
    _transform.transformOperation2(_strg);
    _transform.transformOperation3(_strg);
  }

  StorageTy _strg{};
  TransformerTy _transform{};
};

int main(/* int argc, char *argv[] */) {
  using StorageTy = Storage<DefaultStoragePolicy, DevNullPolicy>;
  using TransformerTy = Transformer<DefaultTransformerPolicy, DevNullPolicy>;

  GenericAlgorithm<StorageTy, TransformerTy> Impl{};
  Impl.run();

  return 0;
}
