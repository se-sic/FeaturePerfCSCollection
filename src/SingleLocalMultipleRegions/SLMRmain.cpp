#include "fp_util/sleep.h"

#include <string>

int main(int argc, char *argv[]) {

  bool Slow = false;

  if ((argc >= 2 && argv[1] == std::string("--slow")) ||
      (argc >= 3 && argv[2] == std::string("--slow"))) {
    Slow = true;
  }

  // Multiple regions related to --slow that take different amounts of time.

  if (Slow) {
    fp_util::sleep_for_secs(5);
  } else {
    fp_util::sleep_for_secs(2);
  }

  fp_util::sleep_for_secs(3); // General waiting time

  if (Slow) {
    fp_util::sleep_for_secs(3);
  } else {
    fp_util::sleep_for_secs(1);
  }

  fp_util::sleep_for_secs(4); // General waiting time

  if (Slow) {
    fp_util::sleep_for_secs(6);
  }

  return 0;
}
