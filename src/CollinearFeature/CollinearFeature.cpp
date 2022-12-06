#include "fpcsc/perf_util/feature_cmd.h"
#include "fpcsc/perf_util/sleep.h"

#include <string>

int main(int argc, char *argv[]) {

  bool a = false;
  bool b = false;
  bool c = false;
  bool d = false;

  if (fpcsc::isFeatureEnabled(argc, argv, std::string("--a"))) {
    a = true;
  }
  if (fpcsc::isFeatureEnabled(argc, argv, std::string("--b"))) {
    b = true;
  }
  if (fpcsc::isFeatureEnabled(argc, argv, std::string("--c"))) {
    c = true;
  }
  if (fpcsc::isFeatureEnabled(argc, argv, std::string("--d"))) {
    d = true;
  }

  if ((c && !d) || (!c && d)){
    c = false;
    d = false;
  }

  fpcsc::sleep_for_secs(2); //spending time in base feature

  if(a)
    fpcsc::sleep_for_secs(1);

  if(b)
    fpcsc::sleep_for_secs(2);

  if(c)
    fpcsc::sleep_for_secs(1);

  if(d)
    fpcsc::sleep_for_secs(2);

  if(a && b)
    fpcsc::sleep_for_secs(2);

  if(c && d)
    fpcsc::sleep_for_secs(2);

  return 0;
}