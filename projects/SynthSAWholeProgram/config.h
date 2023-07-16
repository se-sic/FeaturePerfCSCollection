#ifndef CONFIG_H
#define CONFIG_H

#include <cinttypes>

bool isCountPattern();
bool isPrintPattern();
bool isFast();

void parseConfigOptions(int argc, char *argv[]);

#endif // CONFIG_H
