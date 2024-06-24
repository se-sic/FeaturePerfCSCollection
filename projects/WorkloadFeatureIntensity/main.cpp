//
// Created by abeltluk on 6/21/24.
//
#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

using fp_util::busy_sleep_for_millisecs;

// FeatureA -- Higher intensity of same feature region with differing workloads
bool FeatureA [[clang::feature_variable("A")]] = false;

// FeatureB -- Lower intensity of same feature region with differing workloads
bool FeatureB [[clang::feature_variable("B")]] = false;

// FeatureC -- More feature regions overall but with same intensity each
bool FeatureC [[clang::feature_variable("C")]] = false;

// Mixed behaviour
bool FeatureD [[clang::feature_variable("D")]] = false;

void processStep1(unsigned workload) {
  busy_sleep_for_millisecs(100);

  if (FeatureB) {
    busy_sleep_for_millisecs(50);
  }

  for (int i = 0; i < 3; ++i) {
    if (FeatureC) {
      busy_sleep_for_millisecs(30);
    }
  }

  for (int i = 0; i < workload + 1; ++i) {
    if (FeatureA) {
      busy_sleep_for_millisecs(10);
    }

    if (FeatureD) {
      busy_sleep_for_millisecs(15);
    }
  }

  if (FeatureD) {
    busy_sleep_for_millisecs(30);
  }

  if (workload > 2) {
    for (int i = 0; i < 3; ++i) {
      if (FeatureC) {
        busy_sleep_for_millisecs(30);
      }
    }
  }

  busy_sleep_for_millisecs(200);
}

void processStep2(unsigned workload) {
  busy_sleep_for_millisecs(150);

  for (int i = 0; i < 10 - workload; ++i) {
    if (FeatureB) {
      busy_sleep_for_millisecs(20);
    }

    if (FeatureD) {
      busy_sleep_for_millisecs(15);
    }
  }

  if (workload > 3) {
    for (int i = 0; i < 3; ++i) {
      if (FeatureC) {
        busy_sleep_for_millisecs(30);
      }

      if (FeatureD) {
        busy_sleep_for_millisecs(15);
      }
    }
  }

  unsigned repetitions = 3;

  if (FeatureA) {
    repetitions = 7;
  }

  for (int i = 0; i < repetitions; ++i) {
    if (FeatureB) {
      busy_sleep_for_millisecs(20);
    }

    if (FeatureD) {
      busy_sleep_for_millisecs(15);
    }
  }

  busy_sleep_for_millisecs(50);
}

int main(int argc, char **argv) {
  FeatureA = fp_util::isFeatureEnabled(argc, argv, "-fA");
  FeatureB = fp_util::isFeatureEnabled(argc, argv, "-fB");
  FeatureC = fp_util::isFeatureEnabled(argc, argv, "-fC");
  FeatureD = fp_util::isFeatureEnabled(argc, argv, "-fD");

  unsigned workload = fp_util::getFeatureValue(argc, argv, "--workload");

  busy_sleep_for_millisecs(20);

  if (FeatureA) {
    busy_sleep_for_millisecs(50);

    if (FeatureB) {
      busy_sleep_for_millisecs(30);
    }
  }

  busy_sleep_for_millisecs(80);

  if (FeatureB) {
    busy_sleep_for_millisecs(30);
  }

  busy_sleep_for_millisecs(30);

  for (int i = 0; i < 3; ++i) {
    if (FeatureC) {
      busy_sleep_for_millisecs(30);
    }
  }

  processStep1(workload);

  busy_sleep_for_millisecs(25);

  if (FeatureD) {
    busy_sleep_for_millisecs(60);
  }

  processStep2(workload);

  if (workload > 4) {
    for (int i = 0; i < 3; ++i) {
      if (FeatureC) {
        busy_sleep_for_millisecs(30);
      }
    }
  }
}
