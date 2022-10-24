#include "fpcsc/perf_util/sleep.h"
#include "fpcsc/perf_util/feature_cmd.h"

class FeatureGroup {
public:
  virtual void doWork() {
    fpcsc::sleep_for_secs(5);
  }

  virtual ~FeatureGroup() = default;
};

class FValue1 : public FeatureGroup {
  void doWork() override {
    fpcsc::sleep_for_secs(1);
  }
};

class FValue2 : public FeatureGroup {
  void doWork() override {
    fpcsc::sleep_for_secs(2);
  }
};

class FValue3 : public FeatureGroup {
  void doWork() override {
    fpcsc::sleep_for_secs(3);
  }
};

class FValueOther : public FeatureGroup {};

int main(int argc, char *argv[]) {
  FeatureGroup *feature = nullptr;

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
