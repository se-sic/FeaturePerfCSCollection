#include "service.h"
#include "compute.h"
#include "config.h"

uint64_t countPattern(std::string_view Data, std::string_view Pattern) {
  return getPatternIdxs(Data, Pattern).size();
}

std::vector<uint64_t> getPatternIdxs(std::string_view Data,
                                     std::string_view Pattern) {
  if (Fast) {
    return librarySearch(Data, Pattern);
  }
  return naiveSearch(Data, Pattern);
}
