#include <iostream>

#include "matrix.h"

static const int SIZE = 10;
static const int PRINT_SIZE = 9;


int main() {
    Matrix<int, 0> matrix;

    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; ++j) {
            if (i == j) {
                matrix[i][j] = i;
            }
            if (i + j == SIZE - 1) {
                matrix[i][j] = j;
            }
        }
    }

    for (int i = 1; i < PRINT_SIZE; ++i) {
        for (int j = 1; j < PRINT_SIZE; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Size: " << matrix.size() << std::endl;

    return 0;
}
