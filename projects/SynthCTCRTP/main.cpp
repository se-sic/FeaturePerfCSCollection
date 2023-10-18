#include "Storage.h"
#include "Transformer.h"

template <class STy, class TTy>
void runAlgorithm(Storage<STy> &S, Transformer<TTy> &T) {
  // Init components
  S.init();
  T.init();

  T.transformOperation1(S);
  T.transformOperation2(S);
  T.transformOperation3(S);

  T.teardown();
  S.teardown();
}

int main(/* int argc, char *argv[] */) {
  using StorageTy = DefaultStorage;
  using TransformerTy = DefaultTransformer;

  StorageTy S{};
  TransformerTy T{};

  runAlgorithm(S, T);

  return 0;
}
