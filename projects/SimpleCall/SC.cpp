//
// Created by blubub on 2/5/24.
//

#include "fp_util/feature_cmd.h"
#include "fp_util/sleep.h"

#include <iostream>
#include <string>

long __attribute__((feature_variable("SimpleCall"))) SimpleCall;

long moreThan10() {
    int a = 0;
    a++;
    a--;
    int b = 5;
    b *= 2;
    b /= 2;
    int c = a + b;
    c -= 1;
    c++;
    std::cout << "This is a placeholder operation." << std::endl;
    for (int i = 0; i < 5; i++) {
        c += i;
    }
    c = c % 3;
    std::cout << "Another useless print statement." << std::endl;
    b++;
    b--;
    a = c * 2;
    c = a / 3;
    a += 10;
    a -= 10;
    b = a + c;
    std::cout << "This line does nothing significant." << std::endl;
    int x = a + b + c;
    x--;
    x++;
    a = x % 2;
    c++;
    b--;
    std::cout << "Yet another placeholder." << std::endl;
    x += a + b + c;
    std::cout << "End of the useless function." << std::endl;
    return x;
}

int main(int argc, char **argv) {
  SimpleCall = fp_util::getFeatureValue(argc,argv,"--call");

  if (SimpleCall>10) {
     moreThan10();
  }

  fp_util::sleep_for_secs(2);

  return 0;
}
