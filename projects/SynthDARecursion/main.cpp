#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

/// This synthetic case study targets measurements inside a recursion.
///
/// --rev    : reverse input
/// --limit  : recursion-depth limit
/// --base   : base string to start from
///
/// The key idea is that configuration code is inside a recursion and therefore
/// triggers one measurement per recursive call.

int __attribute__((feature_variable("RecursionLimit"))) RecLimit;

bool checkPalindrome(std::string_view MaybePalindrom) {
  int Length = MaybePalindrom.size();
  int Idx = 0, BackwardsIdx = Length - 1;
  while (Idx < BackwardsIdx) {
    if (MaybePalindrom[Idx] != MaybePalindrom[BackwardsIdx])
      return false;
    Idx++;
    BackwardsIdx--;
  }
  return true;
}

void Partition(std::vector<std::vector<std::string>> &Result,
               std::string_view BaseString, int Idx,
               std::vector<std::string> &Tmp, int Depth = 0) {
  if (Idx == BaseString.size() || Depth == RecLimit) {
    Result.push_back(Tmp);
    return;
  }

  std::string SubString;
  for (int i = Idx; i < BaseString.size(); i++) {
    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    SubString.push_back(BaseString[i]);

    if (checkPalindrome(SubString)) {
      Tmp.push_back(SubString);

      if (RecLimit > Depth) {
        Partition(Result, BaseString, i + 1, Tmp, Depth + 1);
      }

      Tmp.pop_back();
    }
  }
}

// ./Recursion (--rev) (--limit X) --base INPUT_DATA
// where INPUT_DATA = foobar
int main(int argc, char *argv[]) {

  std::string InputString =
      fp_util::getFeatureValueStr(argc, argv, "--base", "");
  bool __attribute__((feature_variable("Reverse"))) Reverse =
      fp_util::isFeatureEnabled(argc, argv, "--rev");
  RecLimit = fp_util::getFeatureValue(argc, argv, "--limit", 4096);

  if (Reverse) {
    std::reverse(InputString.begin(), InputString.end());
  }

  std::vector<std::vector<std::string>> Results;
  std::vector<std::string> TmpStorage;

  Partition(Results, InputString, 0, TmpStorage);

  std::string Sep;
  for (auto &Res : Results) {
    for (auto &Permut : Res) {
      std::cout << Sep << Permut;
      Sep = " ";
    }
    Sep = "";
    std::cout << "\n";
  }

  return 0;
}
