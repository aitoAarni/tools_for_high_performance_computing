#include <iostream>
#include <format>
#include <time.h>

constexpr int N = 1'000;
long a[N][N];
long b[N][N];
long c[N][N];
long t[N][N];

void fill_matrix(long matrix[N][N]) {
    long seed {43248};
    for (int i {0}; i < N; i++) {
        for (int j {0}; j < N; j++) {
            seed = (seed * 3 + 2) % 6103828;
            matrix[i][j] = seed;
        }
    }
}

void print_matrix(long matrix[N][N]) {
    for (int i {0}; i < N; i++) {
        for (int j {0}; j < N; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void transpose_matrix(long m[N][N]) {
    for (int i {0}; i < N; i++) {
        for (int j {i+1}; j < N; j++) {
            std::swap(m[i][j], m[j][i]);
        }
    }
}

double matrix_multiplication(long a[N][N], long b[N][N], long c[N][N]) {
    // I have used a better memory access pattern here than the default
    // B has to be transpoed before so it is same as C=A*B
    auto t1 = clock();
    for (int row {0}; row < N; row++) {
        for (int column {0}; column < N; column++) {
            for (int i {0}; i < N; i++) {
                c[row][column] += a[row][i] * b[column][i];
            }
        }
    }
    auto t2 = clock();
    auto cputime = (double)(t2-t1)/CLOCKS_PER_SEC;
    return cputime;
}



int main() {
    fill_matrix(a);
    fill_matrix(b);
    auto time = matrix_multiplication(a, b, c);
    std::cout << "Matrix multiplication A*B^T=C took: " << time << " seconds. (" << c[4][3] << ")\n";
    return 0;
}