/*
 * Case study for time-inhomogeneous memory usage of a program.
 * A small synthetic case study with 4 configuration options
 * that exhibits different memory usage depending based on the
 * activated knobs
 */

#include "fp_util/feature_cmd.h"
#include "fp_util/memory.h"
#include "fp_util/sleep.h"

#include <string>

int main(int argc, char *argv[]) {
  using fp_util::free_memory;
  using fp_util::get_memory;
  using fp_util::use_memory;

  /*
   * 4 configuration options that simulate differing behavior
   * - Slow: Does not influence memory usage per-se, but shifts all
   * (de-)allocations by 2 seconds if activated. Interacts with "Cache".
   * - PreAlloc: Simulates cases where we pre-allocate some larger memory chunks
   * in advance
   * - Cache:    Uses more memory when activated, but introduces delay when
   * deactivated.
   * - Feature4: Generic feature. Allocates more memory when activated.
   */
  bool __attribute__((feature_variable("Slow"))) Slow = false;
  bool __attribute__((feature_variable("PreAlloc"))) PreAlloc = false;
  bool __attribute__((feature_variable("Cache"))) Cache = false;
  bool __attribute__((feature_variable("Feature4"))) Feature4 = false;

  if (fp_util::isFeatureEnabled(argc, argv, std::string("--slow"))) {
    Slow = true;
  }

  if (fp_util::isFeatureEnabled(argc, argv, std::string("--prealloc"))) {
    PreAlloc = true;
  }

  if (fp_util::isFeatureEnabled(argc, argv, std::string("--cache"))) {
    Cache = true;
  }

  if (fp_util::isFeatureEnabled(argc, argv, std::string("--f4"))) {
    Feature4 = true;
  }

  void *BaseMemory;
  void *SMemory;
  void *PAMemory;
  void *CMemory;
  void *FMemory;

  // Base memory usage of 10kB
  BaseMemory = get_memory(10 * 1024);

  // Delay if Slow is selected
  if (Slow) {
    fp_util::sleep_for_secs(5);
  } else {
    fp_util::sleep_for_secs(3);
  }

  // Allocate memory associated with Slow feature
  SMemory = get_memory(2 * 1024);

  fp_util::sleep_for_secs(2); // General waiting time

  if (PreAlloc) {
    // Preallocate a chunk of memory
    PAMemory = get_memory(3 * 1024);
  } else {
    // Preallocate a smaller chunk of memory
    PAMemory = get_memory(1 * 1024);
  }

  fp_util::sleep_for_secs(2); // General wait time

  // Cache usage: More memory usage when activated
  //              But longer runtime when deactivated
  if (Cache) {
    CMemory = get_memory(512);
  } else {
    CMemory = get_memory(128);
    fp_util::sleep_for_secs(1);
  }

  fp_util::sleep_for_secs(2); // General waiting time

  // "Touch" memory regions to avoid optimization
  use_memory(BaseMemory);
  use_memory(SMemory);
  use_memory(CMemory);
  use_memory(PAMemory);

  // New "Baseline" memory usage depending on configuration
  free_memory(BaseMemory);

  if (PreAlloc && Feature4) {
    BaseMemory = get_memory(7 * 1024);
  } else {
    BaseMemory = get_memory(4 * 1024);
  }

  fp_util::sleep_for_secs(2); // General waiting time

  // Feature4 causes higher memory usage
  if (Feature4) {
    FMemory = get_memory(7 * 512);
  } else {
    FMemory = get_memory(16);
  }

  fp_util::sleep_for_secs(1); // General wait time

  // Slow feature introduces a delay
  if (Slow) {
    fp_util::sleep_for_secs(1);
  } else {
    free_memory(SMemory);
    // Allocate a small memory chunk to avoid double free
    SMemory = get_memory(16);
  }

  fp_util::sleep_for_secs(2); // General waiting time

  // Change in memory behavior of PreAlloc feature
  free_memory(PAMemory);
  if (PreAlloc) {
    PAMemory = get_memory(2 * 128);
  } else {
    PAMemory = get_memory(5 * 512);
  }

  fp_util::sleep_for_secs(1); // General wait time

  // Change in memory behavior of Cache feature
  free_memory(CMemory);
  if (Cache) {
    CMemory = get_memory(7 * 1024);
  } else {
    CMemory = get_memory(512);
    fp_util::sleep_for_secs(1);
  }

  // Feature Interaction of Slow and Cache
  if (Slow && Cache) {
    free_memory(SMemory);
    free_memory(CMemory);

    // Alloc a small memory chunks to avoid double free
    SMemory = get_memory(8);
    CMemory = get_memory(8);
  }

  fp_util::sleep_for_secs(2);

  free_memory(BaseMemory);
  free_memory(CMemory);
  free_memory(SMemory);
  free_memory(PAMemory);
  free_memory(FMemory);

  return 0;
}
