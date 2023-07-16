#ifndef CONFIG_H
#define CONFIG_H

#include <cinttypes>

inline bool __attribute__((feature_variable("count"))) CountPattern = false;

inline bool __attribute__((feature_variable("print"))) PrintPattern = false;

inline bool __attribute__((feature_variable("fast"))) Fast = false;

void parseConfigOptions(int argc, char *argv[]);

#endif // CONFIG_H
