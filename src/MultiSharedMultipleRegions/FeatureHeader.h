#ifndef FEATURE_HEADER_H
#define FEATURE_HEADER_H

extern bool __attribute__((feature_variable("Extern"))) ExternFeature;

static inline bool __attribute__((feature_variable("Header"))) HeaderFeature = false;

inline void enableExternFeature() {
  ExternFeature = true;
}

void enableCppFeature();
bool isCppFeatureEnabled();

#endif // FEATURE_HEADER_H
