#include "config.h"

#include "fp_util/feature_cmd.h"

void parseConfigOptions(int argc, char *argv[]) {
  CountPattern = fp_util::isFeatureEnabled(argc, argv, "--count");
  PrintPattern = fp_util::isFeatureEnabled(argc, argv, "--print");
  Fast = fp_util::isFeatureEnabled(argc, argv, "--fast");

  // SieveLimit = fp_util::getFeatureValue(argc, argv, "--sieve", 0);
}
