#ifndef FEATUREPERFORMANCECASESTUDIE_TRAITDEFINITIONS_H
#define FEATUREPERFORMANCECASESTUDIE_TRAITDEFINITIONS_H

template <typename AlgoTy> struct AlgorithmTraits {
  __attribute__((feature_variable("A"))) static constexpr bool HasComponentA =
      false;
  __attribute__((feature_variable("B"))) static constexpr bool HasComponentB =
      false;
};

template <typename StorageTy> struct StorageTraits {
  __attribute__((feature_variable("C"))) static constexpr bool HasComponentC =
      false;
  __attribute__((feature_variable("D"))) static constexpr bool HasComponentD =
      false;
};

#endif // FEATUREPERFORMANCECASESTUDIE_TRAITDEFINITIONS_H
