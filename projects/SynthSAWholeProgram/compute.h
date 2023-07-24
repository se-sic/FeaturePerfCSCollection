#ifndef COMPUTE_H
#define COMPUTE_H

#include <cassert>
#include <cinttypes>
#include <string_view>
#include <vector>

std::vector<uint64_t> naiveSearch(std::string_view Data,
                                  std::string_view Pattern);

std::vector<uint64_t> librarySearch(std::string_view Data,
                                    std::string_view Pattern);

#endif // COMPUTE_H
