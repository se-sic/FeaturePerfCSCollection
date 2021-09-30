#ifndef FPCSC_PERFUTIL_SLEEP_H
#define FPCSC_PERFUTIL_SLEEP_H

#include <chrono>
#include <thread>
#include <iostream>

namespace fpcsc {

inline void sleep_for_secs(unsigned Secs) {
  std::cout << "Sleeping for " << Secs << " seconds"<< std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(Secs));
}

} // namespace fpcsc

#endif // FPCSC_PERFUTIL_SLEEP_H
