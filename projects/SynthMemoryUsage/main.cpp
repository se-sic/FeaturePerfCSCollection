#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"
#include "fp_util/memory.h"

#include <string>

int main(int argc, char *argv[]) {
  bool __attribute__((feature_variable("Slow"))) Slow = false;
  bool __attribute__((feature_variable("PreAlloc"))) PreAlloc = false;
  bool __attribute__((feature_variable("Header"))) Header = false;
  bool __attribute__((feature_variable("Feature4"))) Feature4 = false;

  if (fp_util::isFeatureEnabled(argc, argv, std::string("--slow"))) {
    Slow = true;
  }

  if (fp_util::isFeatureEnabled(argc, argv, std::string("--prealloc"))) {
    PreAlloc = true;
  }

  if (fp_util::isFeatureEnabled(argc, argv, std::string("--header"))) {
    Header = true;
  }

  if (fp_util::isFeatureEnabled(argc, argv, std::string("--f4"))) {
    Feature4 = true;
  }

  void *BaseMemory;
  void *SMemory;
  void *PAMemory;
  void *HMemory;
  void *FMemory;

  // Multiple regions related to --slow that take different amounts of time.
  BaseMemory = get_memory(10 * 1024);

  if (Slow) {
    fp_util::sleep_for_secs(5);
  } else {
    fp_util::sleep_for_secs(3);
  }

  SMemory = get_memory(2 * 1024);

  fp_util::sleep_for_secs(2); // General waiting time

  if (PreAlloc) {
    PAMemory = get_memory(3 * 1024);
  } else {
    PAMemory = get_memory(1 * 1024);
  }

  fp_util::sleep_for_secs(2);

  if (Header) {
    HMemory = get_memory(512);
  } else {
    HMemory = get_memory(128);
    fp_util::sleep_for_secs(1);
  }

  fp_util::sleep_for_secs(2); // General waiting time
  use_memory(BaseMemory);
  use_memory(SMemory);
  use_memory(HMemory);
  use_memory(PAMemory);

  free_memory(BaseMemory);

  if (PreAlloc && Feature4) {
    BaseMemory = get_memory(7 * 1024);
  } else {
    BaseMemory = get_memory(4 * 1024);
  }

  fp_util::sleep_for_secs(2); // General waiting time

  if (Feature4) {
    FMemory = get_memory(7 * 512);
  } else {
    FMemory = get_memory(16);
  }

  fp_util::sleep_for_secs(1);

  if (Slow) {
    fp_util::sleep_for_secs(1);
  } else {
    free_memory(SMemory);
    SMemory = get_memory(16);
  }

  fp_util::sleep_for_secs(2); // General waiting time

  free_memory(PAMemory);
  if (PreAlloc) {
    PAMemory = get_memory(2 * 128);
  } else {
    PAMemory = get_memory(5 * 512);
  }

  fp_util::sleep_for_secs(1);

  free_memory(HMemory);
  if (Header) {
    HMemory = get_memory(7 * 1024);
  } else {
    HMemory = get_memory(512);
    fp_util::sleep_for_secs(1);
  }

  if (Slow && Header) {
    free_memory(SMemory);
    free_memory(HMemory);

    SMemory = get_memory(8);
    HMemory = get_memory(8);
  }

  free_memory(BaseMemory);
  free_memory(HMemory);
  free_memory(SMemory);
  free_memory(PAMemory);
  free_memory(FMemory);

  return 0;
}
