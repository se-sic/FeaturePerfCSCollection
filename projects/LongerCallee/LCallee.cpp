//
// Created by blubub on 2/5/24.
//

#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

#include <iostream>
#include <string>

long __attribute__((feature_variable("LongerCallee"))) LongerCallee;

char* hellow() {
  char* str[11];

  asm volatile (
      "mov %[size], #44 \n"       // size = 11 * 4 = 44 (size of pointers array)
      "sub sp, sp, %[size] \n"    // Allocate space on stack for the pointers array

      // Assign each element of the array with corresponding string literals
      "ldr %[val], =0x48 \n"     // ASCII value of 'H'
      "str %[val], [%[arr], #0] \n"  // str[0] = "H"
      "ldr %[val], =0x65 \n"     // ASCII value of 'e'
      "str %[val], [%[arr], #4] \n"  // str[1] = "e"
      "ldr %[val], =0x6C \n"     // ASCII value of 'l'
      "str %[val], [%[arr], #8] \n"  // str[2] = "l"
      "str %[val], [%[arr], #12] \n" // str[3] = "l"
      "ldr %[val], =0x6F \n"     // ASCII value of 'o'
      "str %[val], [%[arr], #16] \n" // str[4] = "o"
      "ldr %[val], =0x20 \n"     // ASCII value of space
      "str %[val], [%[arr], #20] \n" // str[5] = " "
      "ldr %[val], =0x57 \n"     // ASCII value of 'W'
      "str %[val], [%[arr], #24] \n" // str[6] = "W"
      "ldr %[val], =0x6F \n"     // ASCII value of 'o'
      "str %[val], [%[arr], #28] \n" // str[7] = "o"
      "ldr %[val], =0x72 \n"     // ASCII value of 'r'
      "str %[val], [%[arr], #32] \n" // str[8] = "r"
      "ldr %[val], =0x6C \n"     // ASCII value of 'l'
      "str %[val], [%[arr], #36] \n" // str[9] = "l"
      "ldr %[val], =0x64 \n"     // ASCII value of 'd'
      "str %[val], [%[arr], #40] \n" // str[10] = "d"

      : // Output operands
      : [arr] "r" (str), [size] "r" (44), [val] "r" (0) // Input operands
      : "memory" // Clobbered memory
  );
  return *str;
}


int main(int argc, char **argv) {
  LongerCallee = fp_util::getFeatureValue(argc,argv,"--call");

  if (LongerCallee!=0) {
    hellow();
  }

  fp_util::sleep_for_secs(2);

  return 0;
}
