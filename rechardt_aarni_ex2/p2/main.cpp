#include <cmath>
#include <format>
#include <iostream>
#include <time.h>

// run g++ -std=c++23 main.cpp -o main -O2
// run ./main

template <typename T>
void calc_sum(T& result, long n = 10'000'000) {
    clock_t start_time;
    clock_t end_time;
    
    start_time = clock();
    for (long k = 0; k < n; k++) {
        result += std::exp(std::sin(static_cast<T>(k)/static_cast<T>(1'000'000)));
    }
    end_time = clock();
    double cputime = double(end_time-start_time)/CLOCKS_PER_SEC;
    std::cout << std::format("FP size: {}, CPU time in seconds {}\n", sizeof(T)*8, cputime);
}


int main() {
    float r1 {0};
    double r2 {0};
    long double r3 {0};
    calc_sum(r1);
    calc_sum(r2);
    calc_sum(r3);
    std::cout << std::format("\n{} bit result: {}\n{} bit result: {}\n{} bit result: {}\n",
    sizeof(r1)*8, r1, sizeof(r2)*8, r2, sizeof(r3)*8, r3);
    
    return 0;
}