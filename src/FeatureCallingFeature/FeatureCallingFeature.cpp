#include "fpcsc/perf_util/feature_cmd.h"
#include "fpcsc/perf_util/sleep.h"

#include <iostream>
#include <string>

void featureC(bool c){

 if(!c)
   fpcsc::sleep_for_secs(2); // If a=1, b=1, c=1 or b=1, c=1
  else
    fpcsc::sleep_for_secs(1); // If a=1, b=1, c=0 or b=1, c=0

}

void featureB(bool c){
  fpcsc::sleep_for_secs(2);

  featureC(c);
}

void featureA(bool b, bool c){
  fpcsc::sleep_for_secs(2);
    if (b) {
      featureB(c);
    }
}

void featureAB(){
  fpcsc::sleep_for_secs(3);
}

int main(int argc, char *argv[]) {

  bool a = false;
  bool b = false;
  bool c = false;

  if (fpcsc::isFeatureEnabled(argc, argv, std::string("--a"))) {
    a = true;
  }
  if (fpcsc::isFeatureEnabled(argc, argv, std::string("--b"))) {
    b = true;
  }
  if (fpcsc::isFeatureEnabled(argc, argv, std::string("--c"))) {
    c = true;
  }

  fpcsc::sleep_for_secs(1); //spending time in base feature

  if (a)
    featureA(b,c);
  featureC(c);


  if (a && b){
    featureAB(); // Enters function once
  }

  if (a && b){
    fpcsc::sleep_for_secs(1);
  }

  fpcsc::sleep_for_secs(1); //spending time in base feature

  if(a && b && c){
    fpcsc::sleep_for_secs(1);
  }

  return 0;
}
/* Expected results:
 * {} = 4s
 * a = 6s
 * b = 6s
 * a, b = 2 + 6 + 2 + 4  = 14
 * a, c = 5s
 * b, c = 5s
 * a, b, c = 2 + 5 + 1 + 4 + 1 = 13
 *
 * */