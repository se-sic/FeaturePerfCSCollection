#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

long __attribute__((feature_variable("LongerCaller"))) LongerCaller;

long randomInc() {
  long Counter = 0;
  asm volatile("" : "+g"(Counter) : :);
  asm volatile("" : "+g"(Counter) : :);

  return Counter;
}

int main(int argc, char **argv) {
  LongerCaller = fp_util::getFeatureValue(argc,argv,"--call");

  long MainCounter = 0;
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

  if (LongerCaller!=0) {
    randomInc();
  }

  fp_util::sleep_for_secs(2);

  return 0;
}
