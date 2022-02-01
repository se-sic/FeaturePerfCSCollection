#ifndef FPCSC_PERFUTIL_FEATURECMD_H
#define FPCSC_PERFUTIL_FEATURECMD_H

#include <string>
#include <stdlib.h>

namespace fpcsc {

inline bool isFeatureEnabled(int argc, char* argv[], std::string FeatureName) {
  for (int CurrentArg = 1; CurrentArg < argc; ++CurrentArg) {
    if (argv[CurrentArg] == FeatureName) {
      return true;
    }
  }

  return false;
}

inline bool getFeatureValue (int argc, char* argv[], std::string FeatureName, long int *Value) {
  int CurrentArg = 1;
  for (; CurrentArg < argc; ++CurrentArg) {
    if (argv[CurrentArg] == FeatureName) {
      ++CurrentArg;
      break;
    }
  }

  if (CurrentArg >= argc)
    return false;

  *Value = strtol (argv[CurrentArg], NULL, 0);

  return true;
}

} // namespace fpcsc

#endif // FPCSC_PERFUTIL_FEATURECMD_H
