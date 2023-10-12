//
// Created by abeltluk on 10/12/23.
//

#ifndef FEATUREPERFORMANCECASESTUDIE_STORAGE_H
#define FEATUREPERFORMANCECASESTUDIE_STORAGE_H

#include "CRTP.h"

template <typename T> struct Storage : CRTP<T> {
  __attribute__((feature_variable("Storage"))) void init() {
    this->underlying().init();
  }

  __attribute__((feature_variable("Storage"))) void getElement(size_t n) {
    this->underlying().getElement(n);
  }

  __attribute__((feature_variable("Storage"))) void setElement(size_t n,
                                                               double d) {
    this->underlying().setElement(n, d);
  }

  __attribute__((feature_variable("Storage"))) void teardown() {
    this->underlying().teardown();
  }
};

struct DefaultStorage : Storage<DefaultStorage> {
  void init() { busy_sleep_for_millisecs(1000); }

  void getElement(size_t n) { busy_sleep_for_millisecs(1000); }

  void setElement(size_t n, double d) { busy_sleep_for_millisecs(1000); }

  void teardown() { busy_sleep_for_millisecs(1000); }
};

struct CachingStorage : Storage<CachingStorage> {
  void init() {
    busy_sleep_for_millisecs(1000);
    initCache();
  }

  void getElement(size_t n) {
    busy_sleep_for_millisecs(1000);
    getCached(n);
    busy_sleep_for_millisecs(1000);
  }

  void setElement(size_t n, double d) {
    busy_sleep_for_millisecs(1000);
    invalidateCache(n);
  }

  void teardown() {
    busy_sleep_for_millisecs(1000);
    destroyCache();
  }

private:
  __attribute__((feature_variable("Cache"))) void initCache() {
    busy_sleep_for_millisecs(1000);
  }

  __attribute__((feature_variable("Cache"))) void getCached(size_t n) {
    busy_sleep_for_millisecs(1000);
  }

  __attribute__((feature_variable("Cache"))) void invalidateCache(size_t n) {
    busy_sleep_for_millisecs(1000);
  }

  __attribute__((feature_variable("Cache"))) void destroyCache() {
    busy_sleep_for_millisecs(1000);
  }
};

struct BoundsCheckingStorage : Storage<BoundsCheckingStorage> {
  void init() {
    busy_sleep_for_millisecs(1000);
    calculateBounds();
  }

  void getElement(size_t n) {
    busy_sleep_for_millisecs(1000);
    inBounds(n);
  }

  void setElement(size_t n, double d) {
    busy_sleep_for_millisecs(1000);
    inBounds(n);
  }

  void teardown() { busy_sleep_for_millisecs(1000); }

private:
  __attribute__((feature_variable("BoundsCheck"))) void calculateBounds() {
    busy_sleep_for_millisecs(1000);
  }

  __attribute__((feature_variable("BoundsCheck"))) bool inBounds(size_t n) {
    busy_sleep_for_millisecs(1000);
    return true;
  }
};

#endif // FEATUREPERFORMANCECASESTUDIE_STORAGE_H
