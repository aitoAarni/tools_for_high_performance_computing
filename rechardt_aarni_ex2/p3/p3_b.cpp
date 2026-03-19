#include <iostream>
#include <time.h>
#include <format>

// run g++ -std=c++23 p3_b.cpp -o p3_b -O0
// run ./p3_b

void part_b_original() {
    const int n = 3000;
    
    static float a[n][n];
    static float b[n][n];
    static float c[n];

    for (int i = 0; i < n; ++i) {
        c[i] = 5.0f;
        for (int j = 0; j < n; ++j) {
            a[i][j] = 0.0f;
            b[i][j] = 2.0f;
        }
    }

    clock_t start_time = clock();

    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            a[i][j] = b[i][j] / c[i];
        }
    }

    clock_t end_time = clock();
    double cputime = double(end_time - start_time) / CLOCKS_PER_SEC;

    std::cout << std::format("Part B (Original): {:.6f} seconds (Check: {})\n", cputime, a[n/2][n/2]);
}

void part_b_optimized() {
    const int n = 3000;
    
    static float a[n][n];
    static float b[n][n];
    static float c[n];

    for (int i = 0; i < n; ++i) {
        c[i] = 5.0f;
        for (int j = 0; j < n; ++j) {
            a[i][j] = 0.0f;
            b[i][j] = 2.0f;
        }
    }

    clock_t start_time = clock();

    for (int i = 0; i < n; ++i) {
        auto inverse = 1.0f / c[i];
        for (int j = 0; j < n; ++j) {
            a[i][j] = b[i][j] * inverse;
        }
    }
    clock_t end_time = clock();
    double cputime = double(end_time - start_time) / CLOCKS_PER_SEC;

    std::cout << std::format("Part B (optimized): {:.6f} seconds (Check: {})\n", cputime, a[n/2][n/2]);
}

int main() {
    
    part_b_original();

    std::cout << "\n";
    part_b_optimized();
    

    return 0;
}