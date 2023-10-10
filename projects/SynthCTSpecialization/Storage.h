//
// Created by abeltluk on 10/9/23.
//

#ifndef FEATUREPERFORMANCECASESTUDIE_STORAGE_H
#define FEATUREPERFORMANCECASESTUDIE_STORAGE_H
#include "fp_util/sleep.h"
#include <cstdlib>

using fp_util::busy_sleep_for_millisecs;

struct Storage {
  void init() { busy_sleep_for_millisecs(1000); }

  void getElement(std::size_t n) { busy_sleep_for_millisecs(1000); }
};

struct CachableStorage {
  void init() { busy_sleep_for_millisecs(1000); }

  __attribute__((feature_variable("Cache"))) void prepareCache() {
    busy_sleep_for_millisecs(1000);
  }

  __attribute__((feature_variable("Cache"))) void getElement(size_t n) {
    busy_sleep_for_millisecs(1000);
  }
};

struct BoundCheckingStorage {
  void init() { busy_sleep_for_millisecs(1000); }

  void getSafe(size_t n) {
    busy_sleep_for_millisecs(1000);
    checkBounds(n);
    busy_sleep_for_millisecs(1000);
  }

private:
  __attribute__((feature_variable("BoundsCheck"))) void checkBounds(size_t n) {
    busy_sleep_for_millisecs(1000);
  }
};

#endif // FEATUREPERFORMANCECASESTUDIE_STORAGE_H
