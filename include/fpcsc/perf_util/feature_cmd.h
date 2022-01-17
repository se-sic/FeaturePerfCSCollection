#ifndef FPCSC_PERFUTIL_FEATURECMD_H
#define FPCSC_PERFUTIL_FEATURECMD_H

#include <string>

namespace fpcsc {

inline bool isFeatureEnabled(int argc, char* argv[], std::string FeatureName) {
  for (int CurrentArg = 1; CurrentArg < argc; ++CurrentArg) {
    if (argv[CurrentArg] == FeatureName) {
      return true;
    }
  }

  return false;
}

} // namespace fpcsc

#endif // FPCSC_PERFUTIL_FEATURECMD_H
