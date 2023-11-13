#ifndef FEATUREPERFORMANCECASESTUDIE_STORAGE_H
#define FEATUREPERFORMANCECASESTUDIE_STORAGE_H
#include "TraitDefinitions.h"
#include "fp_util/sleep.h"

using namespace std;
using fp_util::busy_sleep_for_millisecs;
using fp_util::busy_sleep_for_secs;

struct NullStorage {
  void get(){};
  void initC(){};
  void initD(){};
  void processC(){};
  void processD(){};
};

struct StorageWithC : public NullStorage {
  void get(){};

  __attribute__((feature_variable("C"))) void initC() {
    busy_sleep_for_millisecs(1000);
  }

  __attribute__((feature_variable("C"))) void processC() {
    busy_sleep_for_millisecs(1000);
  }
};

struct OtherStorageWithC : public NullStorage {
  __attribute__((feature_variable("C"))) void get() {
    busy_sleep_for_millisecs(1000);
  };

  __attribute__((feature_variable("C"))) void initC() {
    busy_sleep_for_millisecs(2000);
  }

  __attribute__((feature_variable("C"))) void processC() {}
};

struct StorageWithD : public NullStorage {
  void get(){};

  __attribute__((feature_variable("D"))) void processD() {
    busy_sleep_for_millisecs(1000);
  }
};

struct StorageWithCD : public NullStorage {
  void get() {}

  __attribute__((feature_variable("C"))) void initC() {
    busy_sleep_for_millisecs(1000);
  }

  __attribute__((feature_variable("D"))) void initD() {
    busy_sleep_for_millisecs(1000);
  }

  __attribute__((feature_variable("C"))) void processC() {
    busy_sleep_for_millisecs(1000);
    processD();
    busy_sleep_for_millisecs(1000);
  }

  __attribute__((feature_variable("D"))) void processD() {
    busy_sleep_for_millisecs(1000);
  }
};

template <> struct StorageTraits<StorageWithC> {
  __attribute__((feature_variable("C"))) static const bool HasComponentC = true;
  __attribute__((feature_variable("D"))) static const bool HasComponentD =
      false;
};

template <> struct StorageTraits<OtherStorageWithC> {
  __attribute__((feature_variable("C"))) static const bool HasComponentC = true;
  __attribute__((feature_variable("D"))) static const bool HasComponentD =
      false;
};

template <> struct StorageTraits<StorageWithD> {
  __attribute__((feature_variable("C"))) static const bool HasComponentC =
      false;
  __attribute__((feature_variable("D"))) static const bool HasComponentD = true;
};

template <> struct StorageTraits<StorageWithCD> {
  __attribute__((feature_variable("C"))) static const bool HasComponentC = true;
  __attribute__((feature_variable("D"))) static const bool HasComponentD = true;
};

#endif // FEATUREPERFORMANCECASESTUDIE_STORAGE_H
