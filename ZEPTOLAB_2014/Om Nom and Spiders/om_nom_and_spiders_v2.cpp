#include <iostream>

const int MaxColumnsCount = 2000;

int main()
{
    unsigned int rows_count;
    unsigned int columns_count;
    unsigned int spiders_count;
    
    unsigned int spiders[MaxColumnsCount];
    
    std::cin >> rows_count;
    std::cin >> columns_count;
    std::cin >> spiders_count;
    
    for (int i = 0; i < columns_count; i++) {
        spiders[i] = 0;
    }
    
    int current_spider = 0;
    for (int i = 0; i < rows_count; i++) {
        for (int j = 0; j < columns_count; j++) {
            char cellInhabitant;
            std::cin >> cellInhabitant;
            
            if (cellInhabitant == '.' || cellInhabitant == 'D' ) {
                continue;
            }
            
            if (cellInhabitant == 'U') {
                if (!(i & 1)) {
                    spiders[j]++;
                }
                continue;
            }
            
            if (cellInhabitant == 'R') {
                if (j + i < columns_count) {
                    spiders[j + i]++;
                }
                continue;
            }
            
            if (cellInhabitant == 'L') {
                if (j - i >= 0) {
                    spiders[j - i]++;
                }
                continue;
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