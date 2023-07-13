#include "fp_util/feature_cmd.h"

int main(int argc, char *argv[]) {
  bool __attribute__((feature_variable("Encryption"))) UseEncryption = false;
  bool __attribute__((feature_variable("Compression"))) UseCompression = false;

  return 0;
}
