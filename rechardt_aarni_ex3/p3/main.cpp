#include <iostream>
#include <vector>
#include <time.h>
#include <sys/time.h>
#include <fstream>

// Run the code:
// g++ -std=c++23 main.cpp -o main && ./main

int main() {
    constexpr int n {3'000};
    std::vector<std::vector<long>> vec(n);
    for (int i {0}; i < n; i++) {
        for (int j {0}; j < n; j++) {
            vec[i].push_back(j + 1);
        }
    }
    timeval wall_clock_1;
    timeval wall_clock_2;
    remove("data.txt");
    auto t1 {clock()};
    std::ofstream file("data.txt");
    gettimeofday(&wall_clock_1, NULL);
    for (int i {0}; i < n; i++) {
        for (int j {0}; j < n; j++) {
            file << vec[j][i] * vec[i][j] % n << " ";
        }
        file << std::endl;
    }
    file.close();
    gettimeofday(&wall_clock_2, NULL);
    auto t2 {clock()};

    auto cpu_time {double(t2-t1)/double(CLOCKS_PER_SEC)};
    auto wall_clock_time = ((wall_clock_2.tv_sec - wall_clock_1.tv_sec) *
                1'000'000 + wall_clock_2.tv_usec - wall_clock_1.tv_usec) / 1e6;
    
    std::cout << "CPU time: " << cpu_time << '\n';
    std::cout << "Wall clock time: " << wall_clock_time << "\n";
}