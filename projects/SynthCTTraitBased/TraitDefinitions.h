#ifndef FEATUREPERFORMANCECASESTUDIE_TRAITDEFINITIONS_H
#define FEATUREPERFORMANCECASESTUDIE_TRAITDEFINITIONS_H

template <typename AlgoTy> struct AlgorithmTraits {
  __attribute__((feature_variable("A"))) static const bool HasComponentA =
      false;
  __attribute__((feature_variable("B"))) static const bool HasComponentB =
      false;
};

template <typename StorageTy> struct StorageTraits {
  __attribute__((feature_variable("C"))) static const bool HasComponentC =
      false;
  __attribute__((feature_variable("D"))) static const bool HasComponentD =
      false;
};

#endif // FEATUREPERFORMANCECASESTUDIE_TRAITDEFINITIONS_H
