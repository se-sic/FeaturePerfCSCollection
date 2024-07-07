//
// Created by blubub on 2/5/24.
//

#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

#include <iostream>
#include <string>

long __attribute__((feature_variable("RecursiveCalls"))) RecursiveCalls;

long randomInc() {
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

long recursive() {
  long counter = 0;
  if (counter <= RecursiveCalls){
    randomInc();
    counter++;
  }
  return counter;
}



int main(int argc, char **argv) {
  RecursiveCalls = fp_util::getFeatureValue(argc,argv,"--call");

  recursive();
  fp_util::sleep_for_secs(2);

  return 0;
}
