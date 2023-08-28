#include "fp_util/feature_cmd.h"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>
#include <tuple>
#include <unordered_map>
#include <vector>

class PairSearcher {
public:
  PairSearcher(const std::vector<uint32_t> &Data) : Data(Data) {}
  virtual ~PairSearcher() = default;

  virtual std::optional<std::tuple<uint32_t, uint32_t>>
  findPair(uint32_t Sum) = 0;

protected:
  const std::vector<uint32_t> &Data;
};

class __attribute__((feature_variable("brut-force"))) BrutForceSearcher
    : public PairSearcher {
public:
  BrutForceSearcher(const std::vector<uint32_t> &Data) : PairSearcher(Data) {}

  std::optional<std::tuple<uint32_t, uint32_t>>
  findPair(uint32_t TargetSum) override {
    std::cout << "Running brut-force search\n";

    for (int i = 0; i < Data.size() - 1; i++) {
      for (int j = i + 1; j < Data.size(); j++) {
        if (Data[i] + Data[j] == TargetSum) {
          return {std::tuple<uint32_t, uint32_t>{Data[i], Data[j]}};
        }
      }
    }

    return std::nullopt;
  }
};

class __attribute__((feature_variable("sorting"))) SortingSearcher
    : public PairSearcher {
public:
  SortingSearcher(const std::vector<uint32_t> &Data) : PairSearcher(Data) {}

  std::optional<std::tuple<uint32_t, uint32_t>>
  findPair(uint32_t TargetSum) override {
    std::cout << "Running sort search\n";

    std::vector<uint32_t> LocalData = Data;

    std::sort(LocalData.begin(), LocalData.end());

    int Low = 0;
    int High = LocalData.size() - 1;

    while (Low < High) {
      if (LocalData[Low] + LocalData[High] == TargetSum) {
        return {
            std::tuple<uint32_t, uint32_t>{LocalData[Low], LocalData[High]}};
      }

      if (LocalData[Low] + LocalData[High] < TargetSum) {
        Low++;
      } else {
        High--;
      }
    }

    return std::nullopt;
  }
};

class __attribute__((feature_variable("hashing"))) HashSearcher
    : public PairSearcher {
public:
  HashSearcher(const std::vector<uint32_t> &Data) : PairSearcher(Data) {}

  std::optional<std::tuple<uint32_t, uint32_t>>
  findPair(uint32_t TargetSum) override {
    std::cout << "Running hash search\n";
    std::unordered_map<int, int> Map;

    for (int i = 0; i < Data.size(); i++) {
      if (auto Entry = Map.find(TargetSum - Data[i]); Entry != Map.end()) {
        return {std::tuple<uint32_t, uint32_t>{Data[Entry->second], Data[i]}};
      }

      Map[Data[i]] = i;
    }

    return std::nullopt;
  }
};

// ./VirtualInheritance (--sorting | --hashing) --sum SUM INPUT_DATA
// where INPUT_DATA = 1,3,4,5,5,7
int main(int argc, char *argv[]) {

  std::unique_ptr<PairSearcher> Searcher;
  uint32_t TargetSum = fp_util::getFeatureValue(argc, argv, "--sum", 0);
  std::vector<uint32_t> InputData;

  // Input data
  std::string_view SV(argv[argc - 1]);
  size_t Start = 0;
  while (Start < SV.length()) {
    size_t NextDelim = std::min(SV.find_first_of(',', Start), SV.length());
    uint32_t Val = std::stol(std::string(SV.substr(Start, NextDelim - Start)));
    InputData.push_back(Val);

    Start = NextDelim + 1;
  }
  std::cout << "Got input data: ";
  std::string Sep;
  for (const auto &Val : InputData) {
    std::cout << Sep << Val;
    Sep = ", ";
  }
  std::cout << '\n';

  if (fp_util::isFeatureEnabled(argc, argv, "--sorting")) {
    Searcher = std::make_unique<SortingSearcher>(InputData);
  } else if (fp_util::isFeatureEnabled(argc, argv, "--hashing")) {
    Searcher = std::make_unique<HashSearcher>(InputData);
  } else {
    Searcher = std::make_unique<BrutForceSearcher>(InputData);
  }

  auto MaybePair = Searcher->findPair(TargetSum);
  if (MaybePair) {
    std::cout << "Got pair (" << std::get<0>(MaybePair.value()) << ", "
              << std::get<1>(MaybePair.value()) << ")\n";
  } else {
    std::cerr << "Could not find matching pair for sum\n";
  }

  return 0;
}
