#ifndef FEATUREPERFORMANCECASESTUDIE_TRAITDEFINITIONS_H
#define FEATUREPERFORMANCECASESTUDIE_TRAITDEFINITIONS_H

template <typename AlgoTy> struct AlgorithmTraits {
  __attribute__((feature_variable("A"))) static bool HasComponentA;
  __attribute__((feature_variable("B"))) static bool HasComponentB;
};

template <typename StorageTy> struct StorageTraits {
  __attribute__((feature_variable("C"))) static bool HasComponentC;
  __attribute__((feature_variable("D"))) static bool HasComponentD;
};

#endif // FEATUREPERFORMANCECASESTUDIE_TRAITDEFINITIONS_H
