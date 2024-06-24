//
// Created by abeltluk on 6/24/24.
//
#include "functions.h"

bool FeatureA [[clang::feature_variable("A")]] = false;
bool FeatureB [[clang::feature_variable("B")]] = false;
bool FeatureC [[clang::feature_variable("C")]] = false;

void foo() { fp_util::busy_sleep_for_millisecs(10); }

void bar() { fp_util::busy_sleep_for_millisecs(15); }

void hotCode() {
  for (int i = 0; i < 10; ++i) {
    fp_util::busy_sleep_for_millisecs(100);
  }

  if (FeatureA) {
    for (int i = 0; i < 5; ++i) {
      fp_util::busy_sleep_for_millisecs(100);
    }
  }
}

void hotCode2() { fp_util::busy_sleep_for_millisecs(1200); }

void hotWithB() {
  unsigned sleepTime = 10;

  if (FeatureB) {
    sleepTime = 2000;
  }

  fp_util::busy_sleep_for_millisecs(sleepTime);
}

void hotWithoutC() {
  unsigned sleepTime = 2000;

  if (FeatureC) {
    sleepTime = 10;
  }

  fp_util::busy_sleep_for_millisecs(sleepTime);
}

void processFeatures() {
  foo();
  hotCode();

  bar();
  hotWithB();

  foo();
  bar();
  hotWithoutC();

  if (FeatureB) {
    hotCode2();
  }
}
