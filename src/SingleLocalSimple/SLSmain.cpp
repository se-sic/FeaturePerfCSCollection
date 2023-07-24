#include "fp_util/sleep.h"

#include <string>

int main(int argc, char *argv[]) {

  bool Slow = false;

  if ((argc >= 2 && argv[1] == std::string("--slow")) ||
      (argc >= 3 && argv[2] == std::string("--slow"))) {
    Slow = true;
  }

  if (Slow) {
    fp_util::sleep_for_secs(5);
  } else {
    fp_util::sleep_for_secs(2);
  }

  return 0;
}
