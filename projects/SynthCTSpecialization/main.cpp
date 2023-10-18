#include "Algorithm.h"
#include "Storage.h"

template <typename AlgoTy, typename StorageTy> void run() {
  StorageTy S{};
  AlgoTy A{};

  initStorage(S);
  initAlgorithm(A);

  runAlgorithm(A, S);
}

int main(/* int argc, char *argv[] */) {
  run<DefaultAlgorithm, DefaultStorage>();

  return 0;
}
