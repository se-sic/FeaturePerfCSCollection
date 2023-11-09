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

  void initC() { busy_sleep_for_millisecs(1000); }

  void processC() { busy_sleep_for_millisecs(1000); }
};

struct OtherStorageWithC : public NullStorage {
  void get() { busy_sleep_for_millisecs(1000); };

  void initC() { busy_sleep_for_millisecs(2000); }

  void processC() {}
};

struct StorageWithD : public NullStorage {
  void get(){};

  void processD() { busy_sleep_for_millisecs(1000); }
};

struct StorageWithCD : public NullStorage {
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
  __attribute__((feature_variable("C"))) static bool HasComponentC;
  __attribute__((feature_variable("D"))) static bool HasComponentD;
};


template <> struct StorageTraits<OtherStorageWithC> {
  __attribute__((feature_variable("C"))) static bool HasComponentC;
  __attribute__((feature_variable("D"))) static bool HasComponentD;
};

template <> struct StorageTraits<StorageWithD> {
  __attribute__((feature_variable("C"))) static bool HasComponentC;
  __attribute__((feature_variable("D"))) static bool HasComponentD;
};

template <> struct StorageTraits<StorageWithCD> {
  __attribute__((feature_variable("C"))) static bool HasComponentC;
  __attribute__((feature_variable("D"))) static bool HasComponentD;
};

template <> struct StorageTraits<NullStorage> {
  __attribute__((feature_variable("C"))) static bool HasComponentC;
  __attribute__((feature_variable("D"))) static bool HasComponentD;
};


bool StorageTraits<NullStorage>::HasComponentC = false;
bool StorageTraits<NullStorage>::HasComponentD = false;
bool StorageTraits<StorageWithC>::HasComponentC = true;
bool StorageTraits<StorageWithC>::HasComponentD = false;
bool StorageTraits<OtherStorageWithC>::HasComponentC = true;
bool StorageTraits<OtherStorageWithC>::HasComponentD = false;
bool StorageTraits<StorageWithD>::HasComponentC = false;
bool StorageTraits<StorageWithD>::HasComponentD = true;
bool StorageTraits<StorageWithCD>::HasComponentC = true;
bool StorageTraits<StorageWithCD>::HasComponentD = true;


#endif // FEATUREPERFORMANCECASESTUDIE_STORAGE_H
