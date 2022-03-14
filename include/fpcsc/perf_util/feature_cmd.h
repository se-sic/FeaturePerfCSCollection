#ifndef FPCSC_PERFUTIL_FEATURECMD_H
#define FPCSC_PERFUTIL_FEATURECMD_H

#include <string>
#include <stdlib.h>
#include <exception>

#define FEATURE_MISSING -1

namespace fpcsc
{
  inline bool isFeatureEnabled(int argc, char *argv[], std::string FeatureName)
  {
    for (int CurrentArg = 1; CurrentArg < argc; ++CurrentArg)
    {
      if (argv[CurrentArg] == FeatureName)
      {
        return true;
      }
    }

    return false;
  }

  inline long getFeatureValue(int argc, char *argv[], std::string FeatureName)
  {
    int CurrentArg = 1;
    for (; CurrentArg < argc; ++CurrentArg)
    {
      if (argv[CurrentArg] == FeatureName)
      {
        ++CurrentArg;
        break;
      }
    }

    if (CurrentArg >= argc)
      return FEATURE_MISSING;

    return strtol(argv[CurrentArg], NULL, 0);
  }

} // namespace fpcsc

#endif // FPCSC_PERFUTIL_FEATURECMD_H
