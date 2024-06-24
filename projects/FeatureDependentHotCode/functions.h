//
// Created by abeltluk on 6/24/24.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

extern bool FeatureA [[clang::feature_variable("A")]];
extern bool FeatureB [[clang::feature_variable("B")]];
extern bool FeatureC [[clang::feature_variable("C")]];

void hotCode();
void hotCode2();
void hotWithB();
void hotWithoutC();

void processFeatures();
#endif // FUNCTIONS_H
