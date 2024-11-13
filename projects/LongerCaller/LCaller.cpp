#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

long __attribute__((feature_variable("LongerCaller"))) LongerCaller;

void a() {
  std::cout << "Function a() nonsense begins.\n";
  int z = 7;
  z *= 2;
  z -= 5;
  std::cout << "z after operations: " << z << "\n";

  std::string randomWord = "nonsense";
  randomWord += "_function";
  std::cout << "Random word: " << randomWord << "\n";

  double someCalculation = (z / 3.0) + 1.5;
  std::cout << "Calculation in a(): " << someCalculation << "\n";

  std::cout << "Function a() nonsense ends.\n";
}

int main(int argc, char **argv) {
  LongerCaller = fp_util::getFeatureValue(argc,argv,"--call");

  int x = 5;
  double y = 3.14;
  std::string message = "Hello, nonsense!";
  std::vector<int> numbers(10, 42);

  std::cout << "Starting nonsense operations...\n";

  for (int i = 0; i < 5; ++i) {
    x += i;
    y *= 1.1;
    std::cout << "Iteration " << i << ": x = " << x << ", y = " << y << "\n";
  }

  message += " Adding more nonsense.";
  std::cout << message << "\n";

  for (auto& num : numbers) {
    num -= 10;
  }

  for (size_t i = 0; i < numbers.size(); ++i) {
    std::cout << "numbers[" << i << "] = " << numbers[i] << "\n";
  }

  int counter = 0;
  while (counter < 10) {
    std::cout << "Counter at: " << counter << " doing nonsense check.\n";
    counter++;
  }

  if (x > 10) {
    std::cout << "X is sufficiently nonsense.\n";
  } else {
    std::cout << "X is still too sensible.\n";
  }

  std::cout << "Performing a nonsensical calculation.\n";
  double result = (x * y) / 3.0;
  std::cout << "Result: " << result << "\n";

  for (int i = 0; i < 3; ++i) {
    std::cout << "Repeating nonsense: " << i << "\n";
  }

  // Call function a() that does some nonsense
  a();

  std::cout << "End of main nonsense.\n";

  if (LongerCaller!=0) {
    a();
  }

  fp_util::sleep_for_secs(2);

  return 0;
}
