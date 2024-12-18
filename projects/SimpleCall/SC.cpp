//
// Created by blubub on 2/5/24.
//

#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

#include <iostream>
#include <string>

long __attribute__((feature_variable("SimpleCall"))) SimpleCall;

long moreThan10() {
  long Counter = 0;

  asm volatile ("mfence":: : "memory");
  asm volatile("" : "+g"(Counter) : :);
  asm volatile ("mfence":: : "memory");
  asm volatile("" : "+g"(Counter) : :);
  asm volatile("" : "+g"(Counter) : :);
  asm volatile ("mfence":: : "memory");
  asm volatile("" : "+g"(Counter) : :);
  asm volatile("" : "+g"(Counter) : :);
  asm volatile("" : "+g"(Counter) : :);
  asm volatile ("mfence":: : "memory");
  asm volatile("" : "+g"(Counter) : :);
  asm volatile("" : "+g"(Counter) : :);
  asm volatile("" : "+g"(Counter) : :);
  asm volatile("" : "+g"(Counter) : :);
  asm volatile ("mfence":: : "memory");


  return Counter;
}

int main(int argc, char **argv) {
  SimpleCall = fp_util::getFeatureValue(argc,argv,"--call");

  if (SimpleCall>10) {
    moreThan10();
  }

  fp_util::sleep_for_secs(2);

  return 0;
}