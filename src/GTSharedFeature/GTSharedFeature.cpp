#include "fpcsc/perf_util/feature_cmd.h"
#include "fpcsc/perf_util/sleep.h"

#include <string>

int main(int argc, char *argv[]) {

  bool a = false;
  bool b = false;
  bool c = false;
  std::string de = "00";

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
    de[0] = '1';
  }
  if (fpcsc::isFeatureEnabled(argc, argv, std::string("--e"))) {
    de[1] = '1';
  }

  fpcsc::sleep_for_secs(2); //spending time in base feature

  if(a)
    fpcsc::sleep_for_secs(1);

  if(b)
    fpcsc::sleep_for_secs(2);

  if(c)
    fpcsc::sleep_for_secs(1);

  if(de[0] == '1')
    fpcsc::sleep_for_secs(2);

  if(de[1] == '1')
    fpcsc::sleep_for_secs(1);

  if(a && b)
    fpcsc::sleep_for_secs(2);

  if(c && de[0] == '1')
    fpcsc::sleep_for_secs(0);

  return 0;
}
