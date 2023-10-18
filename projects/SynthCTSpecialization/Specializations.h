//
// Created by abeltluk on 10/10/23.
//

#ifndef FEATUREPERFORMANCECASESTUDIE_SPECIALIZATIONS_H
#define FEATUREPERFORMANCECASESTUDIE_SPECIALIZATIONS_H
#include "Algorithm.h"
#include "Storage.h"

#include "fp_util/sleep.h"
using fp_util::busy_sleep_for_millisecs;

template <typename StorageTy>
__attribute__((feature_variable("Storage"))) void initStorage(StorageTy &G) {
  G.init();
}

template <typename StorageTy>
__attribute__((feature_variable("Storage"))) void access(StorageTy &G,
                                                         std::size_t n) {
  G.getElement(n);
}

template <>
__attribute__((feature_variable("Storage"))) void
initStorage(CachableStorage &G) {
  G.init();

  busy_sleep_for_millisecs(1000);
  // CachableStorage should prepare its cache
  G.prepareCache();
}

template <>
__attribute__((feature_variable("Storage"))) void
access(BoundCheckingStorage &G, std::size_t n) {
  G.getSafe(n);
}

#endif // FEATUREPERFORMANCECASESTUDIE_SPECIALIZATIONS_H
