//
// Created by abeltluk on 10/12/23.
//

#ifndef FEATUREPERFORMANCECASESTUDIE_CRTP_H
#define FEATUREPERFORMANCECASESTUDIE_CRTP_H
#include "fp_util/sleep.h"

using namespace std;
using fp_util::busy_sleep_for_millisecs;
using fp_util::busy_sleep_for_secs;

template <typename T> class CRTP {
protected:
  T &underlying() { return static_cast<T &>(*this); }
};

#endif // FEATUREPERFORMANCECASESTUDIE_CRTP_H
