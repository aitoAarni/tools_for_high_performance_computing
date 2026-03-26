#include <iostream>
#include <fstream>
#include <cstdio>
#include <time.h>


constexpr int N = 10'000'000;
float a[N];
int sample_size {20};

clock_t formatted() {
    std::remove("formatted.txt");
    auto* file = fopen("formatted.txt", "w");
    auto t1 = clock();
    for (int i {0}; i < N; i++) {
        fprintf(file, "%g\n", a[i]);
    }
    auto t2 = clock();
    fclose(file);
    return t2-t1;
}

clock_t unformatted() {
    std::remove("unfromatted.datc");
    auto fu = fopen("unformatted.datc", "wb");
    auto t1 = clock();
    for (int i {0}; i < N; i++) {
        fwrite((void*) &a[i], sizeof(a[i]), 1, fu);
    }
    auto t2 = clock();
    fclose(fu);
    return t2-t1;

}

int main() {
    float num {1};
    for (int i {0}; i < N; i++) {
        num += 1 + (1 / float(i+1));
        a[i] = num;
    }
    clock_t formatted_time {0};
    clock_t unformatted_time {0};

    for (int i {0}; i < sample_size; i++) {
        formatted_time += formatted();
        unformatted_time += unformatted();
    }

    auto formatted_seconds {double(formatted_time)/double(CLOCKS_PER_SEC*sample_size)};
    auto unformatted_seconds {double(unformatted_time)/double(CLOCKS_PER_SEC*sample_size)};

    std::cout << "formatted time average: " << formatted_seconds << " seconds\n";
    std::cout << "unformatted time average: " << unformatted_seconds << " seconds\n";
    return 0;
}