//
// Created by blubub on 2/5/24.
//

#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

#include <iostream>
#include <string>
#include <vector>

long __attribute__((feature_variable("LongerCallee"))) LongerCallee;

void hellow() {
  asm volatile("" : "+g"(MainCounter) : :);
  asm volatile("" : "+g"(MainCounter) : :);
  asm volatile("" : "+g"(MainCounter) : :);
  asm volatile("" : "+g"(MainCounter) : :);
  asm volatile("" : "+g"(MainCounter) : :);
  asm volatile("" : "+g"(MainCounter) : :);
  asm volatile("" : "+g"(MainCounter) : :);
  asm volatile("" : "+g"(MainCounter) : :);
  asm volatile("" : "+g"(MainCounter) : :);
  asm volatile("" : "+g"(MainCounter) : :);
  asm volatile("" : "+g"(MainCounter) : :);
  asm volatile("" : "+g"(MainCounter) : :);
  asm volatile("" : "+g"(MainCounter) : :);
  asm volatile("" : "+g"(MainCounter) : :);
  asm volatile("" : "+g"(MainCounter) : :);
}


int main(int argc, char **argv) {
  LongerCallee = fp_util::getFeatureValue(argc,argv,"--call");

  if (LongerCallee!=0) {
    hellow();
  }

  fp_util::sleep_for_secs(2);

  return 0;
}
