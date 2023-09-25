#ifndef FEATUREPERFORMANCECASESTUDIE_STORAGE_H
#define FEATUREPERFORMANCECASESTUDIE_STORAGE_H
#include "TraitDefinitions.h"
#include "fp_util/sleep.h"

using namespace std;
using fp_util::busy_sleep_for_millisecs;
using fp_util::busy_sleep_for_secs;

struct NullStorage {
  void get(){};
};

struct StorageWithC {
  void get(){};

  void initC() { busy_sleep_for_millisecs(1000); }

  void processC() { busy_sleep_for_millisecs(1000); }
};

struct OtherStorageWithC {
  void get() { busy_sleep_for_millisecs(1000); };

  void initC() { busy_sleep_for_millisecs(2000); }

  void processC() {}
};

struct StorageWithD {
  void get(){};

  void processD() { busy_sleep_for_millisecs(1000); }
};

struct StorageWithCD {
  void get() {}

  void initC() { busy_sleep_for_millisecs(1000); }

  void initD() { busy_sleep_for_millisecs(1000); }

  void processC() {
    busy_sleep_for_millisecs(1000);
    processD();
    busy_sleep_for_millisecs(1000);
  }

  void processD() { busy_sleep_for_millisecs(1000); }
};

template <> struct StorageTraits<StorageWithC> {
  __attribute__((feature_variable("C"))) static constexpr bool HasComponentC =
      true;
  __attribute__((feature_variable("D"))) static constexpr bool HasComponentD =
      false;
};

template <> struct StorageTraits<OtherStorageWithC> {
  __attribute__((feature_variable("C"))) static constexpr bool HasComponentC =
      true;
  __attribute__((feature_variable("D"))) static constexpr bool HasComponentD =
      false;
};

template <> struct StorageTraits<StorageWithD> {
  __attribute__((feature_variable("C"))) static constexpr bool HasComponentC =
      false;
  __attribute__((feature_variable("D"))) static constexpr bool HasComponentD =
      true;
};

template <> struct StorageTraits<StorageWithCD> {
  __attribute__((feature_variable("C"))) static constexpr bool HasComponentC =
      true;
  __attribute__((feature_variable("D"))) static constexpr bool HasComponentD =
      true;
};

#endif // FEATUREPERFORMANCECASESTUDIE_STORAGE_H
