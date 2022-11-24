#include "fpcsc/perf_util/feature_cmd.h"
#include "fpcsc/perf_util/sleep.h"

#include <iostream>
#include <string>

void featureB(){
  fpcsc::sleep_for_secs(2);
}

void featureA(bool b){
  fpcsc::sleep_for_secs(2);
    if (b) {
      featureB();
    }
}

void featureAB(){
  fpcsc::sleep_for_secs(3);
}

int main(int argc, char *argv[]) {

  bool a = false;
  bool b = false;

  if (fpcsc::isFeatureEnabled(argc, argv, std::string("--a"))) {
    a = true;
  }
  if (fpcsc::isFeatureEnabled(argc, argv, std::string("--b"))) {
    b = true;
  }

  fpcsc::sleep_for_secs(2); //spending time in base feature

  if (a)
    featureA(b);
  if (b)
    featureB();

  if (a && b){
    featureAB();
  }


  return 0;
}

