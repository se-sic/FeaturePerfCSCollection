//
// Created by abeltluk on 10/9/23.
//

#ifndef FEATUREPERFORMANCECASESTUDIE_STORAGE_H
#define FEATUREPERFORMANCECASESTUDIE_STORAGE_H
#include <cstdlib>
#include <vector>

#include "Logging.h"

using namespace std;

template <typename StoragePolicy, typename LoggingPolicy = DevNullPolicy>
struct Storage {
  __attribute__((feature_variable("Storage"))) void init() {
    LoggingPolicy::log("Initializing Storage...");
    P.init(_data);
    LoggingPolicy::log("Initialization finished!");
  }

  __attribute__((feature_variable("Storage"))) void get(size_t n) {
    P.get(_data, n);
    LoggingPolicy::log("Getting element at index " + std::to_string(n));
  }

private:
  std::vector<double> _data;
  StoragePolicy P{};
};

struct DefaultStoragePolicy {
  void init(std::vector<double> &) { busy_sleep_for_millisecs(1000); }

  void get(std::vector<double> &, size_t) { busy_sleep_for_millisecs(1000); }
};

struct CachingStoragePolicy {
  void init(std::vector<double> &Data) {
    defaultInit(Data);
    initCache(Data);
  }

  void get(std::vector<double> &, size_t n) {
    busy_sleep_for_millisecs(1000);
    getCached(n);
    busy_sleep_for_millisecs(1000);
  }

private:
  void defaultInit(std::vector<double> &) { busy_sleep_for_millisecs(1000); }

  __attribute__((feature_variable("Cache"))) void
  initCache(std::vector<double> &) {
    busy_sleep_for_millisecs(1000);
  }

  __attribute__((feature_variable("Cache"))) void getCached(size_t) {
    busy_sleep_for_millisecs(1000);
  }
};

#endif // FEATUREPERFORMANCECASESTUDIE_STORAGE_H
