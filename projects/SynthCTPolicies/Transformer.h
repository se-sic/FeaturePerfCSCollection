//
// Created by abeltluk on 10/9/23.
//

#ifndef FEATUREPERFORMANCECASESTUDIE_TRANSFORMER_H
#define FEATUREPERFORMANCECASESTUDIE_TRANSFORMER_H
#include "Logging.h"

template <typename TransformerPolicy, typename LoggingPolicy = DevNullPolicy>
struct Transformer {
  __attribute__((feature_variable("Transformer"))) void init() {
    LoggingPolicy::log("Initializing transformer...");
    Policy.init();
    LoggingPolicy::log("Transformer initialized!");
  }

  template <class StorageTy>
  __attribute__((feature_variable("Transformer"))) void
  transformOperation1(StorageTy &S) {
    LoggingPolicy::log("Applying operation 1");
    Policy.applyOp1(S);
  }

  template <class StorageTy>
  __attribute__((feature_variable("Transformer"))) void
  transformOperation2(StorageTy &S) {
    LoggingPolicy::log("Applying operation 2");
    Policy.applyOp2(S);
  }

  template <class StorageTy>
  __attribute__((feature_variable("Transformer"))) void
  transformOperation3(StorageTy &S) {
    LoggingPolicy::log("Applying operation 3");
    Policy.applyOp3(S);
  }

private:
  TransformerPolicy Policy;
};

struct DefaultTransformerPolicy {
  void init() { busy_sleep_for_millisecs(1000); }

  template <class StorageTy> void applyOp1(StorageTy &S) {
    busy_sleep_for_millisecs(1000);
    S.get(0);
    busy_sleep_for_millisecs(1000);
  }

  template <class StorageTy> void applyOp2(StorageTy &S) {
    busy_sleep_for_millisecs(1000);
    S.get(0);
    busy_sleep_for_millisecs(1000);
  }

  template <class StorageTy> void applyOp3(StorageTy &S) {
    busy_sleep_for_millisecs(1000);
    S.get(0);
    busy_sleep_for_millisecs(1000);
  }
};

struct SmoothingTransformerPolicy {
  void init() { initSmoother(); }

  template <class StorageTy> void applyOp1(StorageTy &S) {
    busy_sleep_for_millisecs(1000);
    S.get(0);
    smoothData(S);
    busy_sleep_for_millisecs(1000);
  }

  template <class StorageTy> void applyOp2(StorageTy &S) {
    busy_sleep_for_millisecs(1000);
    smoothData(S);
    S.get(0);
    busy_sleep_for_millisecs(1000);
  }

  template <class StorageTy> void applyOp3(StorageTy &S) {
    busy_sleep_for_millisecs(1000);
    S.get(0);
    busy_sleep_for_millisecs(1000);
  }

private:
  template <class StorageTy>
  __attribute__((feature_variable("Smoother"))) void smoothData(StorageTy &S) {
    busy_sleep_for_millisecs(1000);
    S.get(0);
    // Smooth operator... smooooth operator
    busy_sleep_for_millisecs(1000);
  }

  __attribute__((feature_variable("Smoother"))) void initSmoother() {
    busy_sleep_for_millisecs(1000);
  }
};
#endif // FEATUREPERFORMANCECASESTUDIE_TRANSFORMER_H
