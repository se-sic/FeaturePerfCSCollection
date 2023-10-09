//
// Created by abeltluk on 10/9/23.
//

#ifndef FEATUREPERFORMANCECASESTUDIE_LOGGING_H
#define FEATUREPERFORMANCECASESTUDIE_LOGGING_H
#include "fp_util/sleep.h"
#include <string>

using fp_util::busy_sleep_for_millisecs;
using fp_util::busy_sleep_for_secs;

struct DevNullPolicy {
  __attribute__((feature_variable("Logging"))) static void
  log(const std::string &) {}
};

struct ExpensiveLogger {
  __attribute__((feature_variable("Logging"))) static void
  log(const std::string &) {
    busy_sleep_for_millisecs(1000);
  }
};

struct DataBaseLogger {
  __attribute__((feature_variable("Logging"))) static void
  log(const std::string &s) {
    busy_sleep_for_millisecs(1000);
    logToDB(s);
    busy_sleep_for_millisecs(1000);
  }

private:
  __attribute__((feature_variable("Database"))) static void
  logToDB(const std::string &) {
    busy_sleep_for_millisecs(1000);
  }
};

#endif // FEATUREPERFORMANCECASESTUDIE_LOGGING_H
