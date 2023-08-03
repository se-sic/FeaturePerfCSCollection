#include "config.h"

#include "fp_util/feature_cmd.h"

static bool __attribute__((feature_variable("count"))) CountPattern = false;
bool isCountPattern() { return CountPattern; }

static bool __attribute__((feature_variable("print"))) PrintPattern = false;
bool isPrintPattern() { return PrintPattern; }

static bool __attribute__((feature_variable("fast"))) Fast = false;
bool isFast() { return Fast; }

void parseConfigOptions(int argc, char *argv[]) {
  CountPattern = fp_util::isFeatureEnabled(argc, argv, "--count");
  PrintPattern = fp_util::isFeatureEnabled(argc, argv, "--print");
  Fast = fp_util::isFeatureEnabled(argc, argv, "--fast");

  // SieveLimit = fp_util::getFeatureValue(argc, argv, "--sieve", 0);
}
