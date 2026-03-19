#include <iostream>
#include <time.h>
#include <format>



void part_a_original() {
    const int n = 10000000;
    
    static float a[n];
    static float b[n];

    for (int i = 0; i < n; ++i) {
        a[i] = 0.0f;
        b[i] = 1.5f;
    }

    clock_t start_time = clock();

    for (int i = 0; i < n - 1; ++i) {
        if (i < 499) {
            a[i] = 4.0f * b[i] + b[i+1];
        } else {
            a[i] = 4.0f * b[i+1] + b[i];
        }
    }

    clock_t end_time = clock();
    double cputime = double(end_time - start_time) / CLOCKS_PER_SEC;
    
    std::cout << std::format("Part A (Original): {:.6f} seconds (Check: {})\n", cputime, a[n/2]);
}


void part_a_optimized() {
    const int n = 10'000'000;
    
    static float a[n+8];
    static float b[n+8];

    for (int i = 0; i < n; ++i) {
        a[i] = 0.0f;
        b[i] = 1.5f;
    }

    clock_t start_time = clock();
    int i {0};
    for (;i < 499; i++) {
        a[i] = 4.0f * b[i] + b[i+1];
    }
    for (; i < n - 1; i = i + 8) {
            a[i] = 4.0f * b[i+1] + b[i];
            a[i+1] = 4.0f * b[i+1+1] + b[i+1];
            a[i+2] = 4.0f * b[i+1+2] + b[i+2];
            a[i+3] = 4.0f * b[i+1+3] + b[i+3];
            a[i+4] = 4.0f * b[i+1+4] + b[i+4];
            a[i+5] = 4.0f * b[i+1+5] + b[i+5];
            a[i+6] = 4.0f * b[i+1+6] + b[i+6];
            a[i+7] = 4.0f * b[i+1+7] + b[i+7];
    }

    clock_t end_time = clock();
    double cputime = double(end_time - start_time) / CLOCKS_PER_SEC;
    
    std::cout << std::format("Part A (optimized): {:.6f} seconds (Check: {})\n", cputime, a[n/2]);
}




int main() {
    
    part_a_original();

    std::cout << "\n";
    part_a_optimized();
    std::cout << "\n";
    
    return 0;
}