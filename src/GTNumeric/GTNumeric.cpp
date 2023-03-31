#include "fpcsc/perf_util/feature_cmd.h"
#include "fpcsc/perf_util/sleep.h"

#include <string>

int main(int argc, char *argv[]) {

  bool a = false;
  bool b = false;
  bool c = false;
  int d = 0;

  if (fpcsc::isFeatureEnabled(argc, argv, std::string("--a"))) {
    a = true;
  }
  if (fpcsc::isFeatureEnabled(argc, argv, std::string("--b"))) {
    b = true;
  }
  if (fpcsc::isFeatureEnabled(argc, argv, std::string("--c"))) {
    c = true;
  }
  if (fpcsc::isFeatureEnabled(argc, argv, std::string("--d1"))) {
    d = 1;
  }
    if (fpcsc::isFeatureEnabled(argc, argv, std::string("--d2"))) {
    d = 2;
  }

  fpcsc::sleep_for_secs(2); //spending time in base feature

  if(a)
    fpcsc::sleep_for_secs(1);

  if(b)
    fpcsc::sleep_for_secs(2);

  if(c)
    fpcsc::sleep_for_secs(1);

  if(d == 1)
    fpcsc::sleep_for_secs(2);

  if(d == 2)
    fpcsc::sleep_for_secs(1);

  if(a && b)
    fpcsc::sleep_for_secs(2);

  if(c && d)
    fpcsc::sleep_for_secs(0);

  return 0;
}
