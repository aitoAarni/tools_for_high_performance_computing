#include <format>
#include <iostream>

// you can choose whether to use the stack or the BSS segment.
// choose my choosing by altering the stack variable

// to compile use g++ -std=c++23 main.cpp -o main
// to run do ./main
// to get results to a file run ./main > output.txt

int a[10];
int main() {
    bool stack {false};
    int b[10]; 
    int i = 10;
    if (stack) {

        while (true) {
            std::cout << std::format("b[i]: {}, i: {}\n", b[i], i++);
        }
    } else {
        while (true) {
            std::cout << std::format("a[i]: {}, i: {}\n", a[i], i++);
        }
    }
    return 0;
}