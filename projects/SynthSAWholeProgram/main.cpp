#include "fp_util/sleep.h"

#include "config.h"
#include "service.h"

#include <cstdio>
#include <string_view>

/// This synthetic case study for whole program analysis.
///
/// --sieve : amount of precomputed values
/// pattern :
/// text    :
///
/// The key idea is that configuration code is spread all over the code base,
/// an inter-procedural whole program analysis.

int main(int argc, char *argv[]) {

  parseConfigOptions(argc, argv);

  std::string_view Pattern = argv[argc - 2];
  std::string_view Text = argv[argc - 1];

  uint64_t Result{};

  if (CountPattern) {
    Result = countPattern(Text, Pattern);
    std::printf("Got %lu patterns\n", Result);
  }

  if (PrintPattern) {
    auto PatternIdxs = getPatternIdxs(Text, Pattern);
    std::printf("Patterns: ");
    for (auto Idx : PatternIdxs) {
      std::printf("%lu, ", Idx);
    }
    std::printf("\n");
  }

  fp_util::sleep_for_secs(3);
  return 0;
}
