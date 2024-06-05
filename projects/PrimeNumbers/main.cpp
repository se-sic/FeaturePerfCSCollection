#include "fp_util/feature_cmd.h"
#define USE_BUSY_SLEEPING
#include "fp_util/sleep.h"
#include <iostream>
#include <vector>

/// This prime numbers case study is a simple programm for calculating  prime numbers.

bool isPrime(int n){
    if (n ==1 || n ==0){
        return false;
    }
    for (int i = 2 ; i < n; i++)
    {
        if(n % i == 0){
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    bool __attribute__((feature_variable("feature_1"))) F1 =
      fp_util::isFeatureEnabled(argc, argv, "--f1");
    bool __attribute__((feature_variable("feature_2"))) F2 =
      fp_util::isFeatureEnabled(argc, argv, "--f2");

    int n = 100000;
    std::vector<int> primeArray;
    for (int i = 1; i <= n; i++){
        if (isPrime(i)){
            primeArray.push_back(i);
        }
        if (F1){
          fp_util::sleep_for_millisecs(30);
        }
    }
    /*
    std::cout << "Prime numbers up to " << n << ":" << std::endl;
    for (int prime : primeArray) {
        std::cout << prime << " ";
        if (F2){
        fp_util::sleep_for_millisecs(10);
        }
    }
    */
    std::cout << std::endl;
    
    return 0;
}