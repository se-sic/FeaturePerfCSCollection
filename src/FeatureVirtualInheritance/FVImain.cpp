#include "fpcsc/perf_util/feature_cmd.h"
#include "fpcsc/perf_util/sleep.h"

class __attribute__((feature_variable("FeatureGroup"))) FeatureGroup {
public:
  virtual void doWork() { fpcsc::sleep_for_secs(5); }

  virtual ~FeatureGrexioup() = default;
};

class __attribute__((feature_variable("FValue1"))) FValue1
    : public FeatureGroup {
public:
  void doWork() override { fpcsc::sleep_for_secs(1); }
};

class __attribute__((feature_variable("FValue2"))) FValue2
    : public FeatureGroup {
public:
  void doWork() override { fpcsc::sleep_for_secs(2); }
};

class __attribute__((feature_variable("FValue3"))) FValue3
    : public FeatureGroup {
public:
  void doWork() override { fpcsc::sleep_for_secs(3); }
};

// This should not appear in traces as there is no implementation different
// from the base class
class __attribute__((feature_variable("FValueOther"))) FValueOther
    : public FeatureGroup {};

int main(int argc, char *argv[]) {
  FeatureGroup *feature __attribute__((feature_variable("FG_variable"))) =
      nullptr;

  if (fpcsc::isFeatureEnabled(argc, argv, std::string("--value1"))) {
    feature = new FValue1();
  } else if (fpcsc::isFeatureEnabled(argc, argv, std::string("--value2"))) {
    feature = new FValue2();
  } else if (fpcsc::isFeatureEnabled(argc, argv, std::string("--value3"))) {
    feature = new FValue3();
  } else if (fpcsc::isFeatureEnabled(argc, argv, std::string("--other"))) {
    feature = new FValueOther();
  }

  if (feature) {
    feature->doWork(); // Feature dependent time cost

    delete feature;
  }
  return 0;
}
