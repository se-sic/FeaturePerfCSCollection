#include "compute.h"

#include "fp_util/sleep.h"

#include <cstring>
#include <iostream>

std::vector<uint64_t> naiveSearch(std::string_view Data,
                                  std::string_view Pattern) {
  std::vector<uint64_t> FoundIdxs;
  int M = Pattern.size();
  int N = Data.size();

  for (int i = 0; i <= N - M; i++) {
    int j;

    for (j = 0; j < M; j++) {
      fp_util::sleep_for_millisecs(30);
      if (Data[i + j] != Pattern[j]) {
        break;
      }
    }

    if (j == M) { // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
      FoundIdxs.push_back(i);
    }
  }

  return FoundIdxs;
}

std::vector<uint64_t> librarySearch(std::string_view Data,
                                    std::string_view Pattern) {
  std::vector<uint64_t> FoundIdxs;

  size_t LastPos = 0;
  while (LastPos != Data.npos) {
    LastPos = Data.find(Pattern, LastPos);

    fp_util::sleep_for_millisecs(30);
    if (LastPos != Data.npos) {
      FoundIdxs.push_back(LastPos);
      LastPos++;
    }
  }

  return FoundIdxs;
}
