#ifndef SERVICE_H
#define SERVICE_H

#include <cinttypes>
#include <string_view>
#include <vector>

uint64_t countPattern(std::string_view Data, std::string_view Pattern);
std::vector<uint64_t> getPatternIdxs(std::string_view Data,
                                     std::string_view Pattern);

#endif // SERVICE_H
