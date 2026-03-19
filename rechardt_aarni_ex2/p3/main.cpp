#include <iostream>
#include <time.h>
#include <format>

void part_a_original() {
    const int n = 100000000;
    
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
    const int n = 100'000'000;
    
    static float a[n];
    static float b[n];

    for (int i = 0; i < n; ++i) {
        a[i] = 0.0f;
        b[i] = 1.5f;
    }

    clock_t start_time = clock();
    int i {0};
    for (;i < 499; i++) {
        a[i] = 4.0f * b[i] + b[i+1];
    }
    for (; i < n - 1; i++) {
            a[i] = 4.0f * b[i+1] + b[i];
    }

    clock_t end_time = clock();
    double cputime = double(end_time - start_time) / CLOCKS_PER_SEC;
    
    std::cout << std::format("Part A (optimized): {:.6f} seconds (Check: {})\n", cputime, a[n/2]);
}



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

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = b[i][j] / c[i];
        }
    }

    clock_t end_time = clock();
    double cputime = double(end_time - start_time) / CLOCKS_PER_SEC;

    std::cout << std::format("Part B (Original): {:.6f} seconds (Check: {})\n", cputime, a[n/2][n/2]);
}

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

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = b[i][j] / c[i];
        }
    }

    clock_t end_time = clock();
    double cputime = double(end_time - start_time) / CLOCKS_PER_SEC;

    std::cout << std::format("Part B (Original): {:.6f} seconds (Check: {})\n", cputime, a[n/2][n/2]);
}

int main() {
    
    part_a_original();

    std::cout << "\n";
    part_a_optimized();
    std::cout << "\n";
    
    // part_b_optimized(); 

    return 0;
}