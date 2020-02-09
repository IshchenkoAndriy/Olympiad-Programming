#include <iostream>

const int MaxColumnsCount = 2000;

enum SpiderDirections { UP = 0x1, DOWN = 0x2, LEFT = 0x4, RIGHT = 0x8 };

static inline int countBits(char value) {
    int count = 0;
    while (value) {
        count++;
        value &= value - 1;
    }
    return count;
}

int main()
{
    unsigned int rows_count;
    unsigned int columns_count;
    unsigned int spiders_count;

    char park_field[MaxColumnsCount][MaxColumnsCount];
    unsigned int spiders[MaxColumnsCount];
    
    std::cin >> rows_count;
    std::cin >> columns_count;
    std::cin >> spiders_count;
    
    for (int i = 0; i < rows_count; i++) {
        for (int j = 0; j < columns_count; j++) {
            char cellInhabitant;
            std::cin >> cellInhabitant;
            if (cellInhabitant == '.') {
                park_field[i][j] = 0;
            }
            else if (cellInhabitant == 'R') {
                park_field[i][j] = RIGHT;
            }
            else if (cellInhabitant == 'L') {
                park_field[i][j] = LEFT;
            }
            else if (cellInhabitant == 'U') {
                park_field[i][j] = UP;
            }
            else if (cellInhabitant == 'D') {
                park_field[i][j] = DOWN;
            }
        }
    }
    
    for (int i = 0; i < columns_count; i++) {
        spiders[i] = 0;
    }
    
    for (int i = 0; i < rows_count; i++) {
        for (int j = 0; j < columns_count; j++) {
            spiders[j] += countBits(park_field[i][j]);
        }
        
        for (int k = i; k < rows_count; k++) {
            for (int m = 0; m < columns_count; m++) {
               if (park_field[k][m] & LEFT) {
                    park_field[k][m] ^= LEFT;
                    if (m - 1 >= 0) {
                        park_field[k][m - 1] |= LEFT;
                    }
                }
               if (park_field[k][m] & UP) {
                    park_field[k][m] ^= UP;
                    if (k - 1 >= 0) {
                        park_field[k - 1][m] |= UP;
                    }
                }
            }
        }
        
        for (int k = rows_count - 1; k >= i; k--) {
            for (int m = columns_count - 1; m >= 0; m--) {
                if (park_field[k][m] & RIGHT) {
                    park_field[k][m] ^= RIGHT;
                    if (m + 1 < columns_count) {
                        park_field[k][m + 1] |= RIGHT;
                    }
                }
               if (park_field[k][m] & DOWN) {
                    park_field[k][m] ^= DOWN;
                    if (k + 1 < rows_count) {
                        park_field[k + 1][m] |= DOWN;
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < columns_count; i++) {
        std::cout << spiders[i];
        if (i + 1 < columns_count) {
            std::cout << " ";
        }
        else {
            std::cout << std::endl;
        }
    }
    
    return 0;
}