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

  __attribute__((feature_variable("Transformer"))) void teardown() {
    this->underlying().teardown();
  }
};

struct DefaultTransformer : Transformer<DefaultTransformer> {
  void init() { busy_sleep_for_millisecs(1000); }

  template <typename STy> void transformOperation1(Storage<STy> &S) {
    busy_sleep_for_millisecs(1000);
  }

  template <typename STy> void transformOperation2(Storage<STy> &S) {
    busy_sleep_for_millisecs(1000);
    S.getElement(0);
  }

  template <typename STy> void transformOperation3(Storage<STy> &S) {
    busy_sleep_for_millisecs(1000);
    S.setElement(1, 42.0);
  }

  void teardown() { busy_sleep_for_millisecs(1000); }
};

struct SmoothingTransformer : Transformer<SmoothingTransformer> {
  void init() {
    busy_sleep_for_millisecs(1000);
    initSmoother();
  }

  template <typename STy> void transformOperation1(Storage<STy> &S) {
    busy_sleep_for_millisecs(1000);
  }

  template <typename STy> void transformOperation2(Storage<STy> &S) {
    busy_sleep_for_millisecs(1000);
    S.getElement(0);
  }

  template <typename STy> void transformOperation3(Storage<STy> &S) {
    busy_sleep_for_millisecs(1000);
    smoothData(S);
  }

  void teardown() { busy_sleep_for_millisecs(1000); }

private:
  template <class STy>
  __attribute__((feature_variable("Smoother"))) void
  smoothData(Storage<STy> &S) {
    busy_sleep_for_millisecs(1000);
    S.setElement(1, 42.0);
    // Smooth operator... smooooth operator
    busy_sleep_for_millisecs(1000);
  }

  __attribute__((feature_variable("Smoother"))) void initSmoother() {
    busy_sleep_for_millisecs(1000);
  }
};

struct PreconditioningTransformer : Transformer<PreconditioningTransformer> {
  void init() { busy_sleep_for_millisecs(1000); }

  template <typename STy> void transformOperation1(Storage<STy> &S) {
    busy_sleep_for_millisecs(1000);
    preconditionData(S);
  }

  template <typename STy> void transformOperation2(Storage<STy> &S) {
    busy_sleep_for_millisecs(1000);
    S.setElement(0, 13.37);
  }

  template <typename STy> void transformOperation3(Storage<STy> &S) {
    busy_sleep_for_millisecs(1000);
  }

  void teardown() {
    busy_sleep_for_millisecs(1000);
    resetPreconditioner();
  }

private:
  template <typename STy>
  __attribute__((feature_variable("Preconditioner"))) void
  preconditionData(Storage<STy> &S) {
    S.getElement(0);
    busy_sleep_for_millisecs(1000);
  }

  __attribute__((feature_variable("Preconditioner"))) void
  resetPreconditioner() {
    busy_sleep_for_millisecs(1000);
  }
};

#endif // FEATUREPERFORMANCECASESTUDIE_TRANSFORMER_H
