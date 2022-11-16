#ifndef FPCSC_PERFUTIL_SLEEP_H
#define FPCSC_PERFUTIL_SLEEP_H

#include <chrono>
#include <iostream>
#include <thread>

namespace fpcsc {

inline void sleep_for_secs(unsigned Secs) {
  std::cout << "Sleeping for " << Secs << " seconds" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(Secs));
}

inline void busy_sleep_for_secs(unsigned Secs) {
  std::cout << "Sleeping for " << Secs << " seconds" << std::endl;
  auto start_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now().time_since_epoch());
  auto end_ms = start_ms + std::chrono::seconds(Secs);
  auto current_ms = start_ms;

  while (current_ms < end_ms) {
    for (long counter = 0; counter < 100'000'000; ++counter) {
      asm volatile("" : "+g"(counter) : :); // prevent optimization
    }
    current_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now().time_since_epoch());
  }
}

inline void sleep_for_millisecs(unsigned Millisecs) {
  std::cout << "Sleeping for " << Millisecs << " milliseconds" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(Millisecs));
}
} // namespace fpcsc

#endif // FPCSC_PERFUTIL_SLEEP_H
