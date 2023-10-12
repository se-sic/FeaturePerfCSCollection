//
// Created by abeltluk on 10/12/23.
//

#ifndef FEATUREPERFORMANCECASESTUDIE_TRANSFORMER_H
#define FEATUREPERFORMANCECASESTUDIE_TRANSFORMER_H
#include "CRTP.h"
#include "Storage.h"

template <typename T> struct Transformer : CRTP<T> {
  __attribute__((feature_variable("Transformer"))) void init() {
    this->underlying().init();
  }

  template <typename STy>
  __attribute__((feature_variable("Transformer"))) void
  transformOperation1(Storage<STy> &S) {
    this->underlying().transformOperation1(S);
  }

  template <typename STy>
  __attribute__((feature_variable("Transformer"))) void
  transformOperation2(Storage<STy> &S) {
    this->underlying().transformOperation2(S);
  }

  template <typename STy>
  __attribute__((feature_variable("Transformer"))) void
  transformOperation3(Storage<STy> &S) {
    this->underlying().transformOperation3(S);
  }
};

struct SmoothingTransformer : Transformer<SmoothingTransformer> {};

struct PreconditioningTransformer : Transformer<PreconditioningTransformer> {};

#endif // FEATUREPERFORMANCECASESTUDIE_TRANSFORMER_H
