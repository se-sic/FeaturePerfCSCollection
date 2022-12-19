#ifndef FPCSC_PERFUTIL_SLEEP_H
#define FPCSC_PERFUTIL_SLEEP_H

#include <chrono>
#include <iostream>
#include <thread>

namespace fpcsc {

inline void busy_sleep_for_secs(unsigned Secs) {
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

inline void busy_sleep_for_millisecs(unsigned Millisecs) {
  auto start_us = std::chrono::duration_cast<std::chrono::microseconds>(
      std::chrono::high_resolution_clock::now().time_since_epoch());
  auto end_us = start_us + std::chrono::milliseconds(Millisecs);
  auto current_us = start_us;

  while (current_us < end_us) {
    for (long counter = 0; counter < 100'000; ++counter) {
      asm volatile("" : "+g"(counter) : :); // prevent optimization
    }
    current_us = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch());
  }
}

inline void sleep_for_secs(unsigned Secs) {
  std::cout << "Sleeping for " << Secs << " seconds" << std::endl;
#ifdef USE_BUSY_SLEEPING
  busy_sleep_for_secs(Secs);
#else
  std::this_thread::sleep_for(std::chrono::seconds(Secs));
#endif
}

inline void sleep_for_millisecs(unsigned Millisecs) {
  std::cout << "Sleeping for " << Millisecs << " milliseconds" << std::endl;
#ifdef USE_BUSY_SLEEPING
  busy_sleep_for_millisecs(Millisecs);
#else
  std::this_thread::sleep_for(std::chrono::milliseconds(Millisecs));
#endif
}
} // namespace fpcsc

#endif // FPCSC_PERFUTIL_SLEEP_H
