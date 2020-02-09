#include <iostream>

const int MaxCnadiesCount = 2000;

unsigned int total_candies_count;
unsigned int start_jump_height;

int candiesTypes[MaxCnadiesCount];
int candiesPositions[MaxCnadiesCount];
int candiesWeight[MaxCnadiesCount];

int calucalteCandiesNumber(int start_type)
{
    bool candiesUsed[MaxCnadiesCount];
    unsigned long final_jump_height = start_jump_height;
    int candies_number = 0;
    int next_candy_type = start_type;
    
    for (int i = 0; i < total_candies_count; i++) {
        candiesUsed[i] = 0;
    }
    
    while (true) {
        int candidateIndex = -1;
        int candidateWeight = 0;
        for (int i = 0; i < total_candies_count; i++) {
            if (!candiesUsed[i] && candidateWeight < candiesWeight[i] && next_candy_type == candiesTypes[i] && final_jump_height >= candiesPositions[i]) {
                candidateIndex = i;
                candidateWeight = candiesWeight[i];
            }
        }
        
        if (candidateIndex != -1) {
            final_jump_height += candiesWeight[candidateIndex];
            candiesUsed[candidateIndex] = 1;
            candies_number++;
            next_candy_type = !next_candy_type;
        } else {
            break;
        }
    }
    
    return candies_number;
}


int main()
{
    std::cin >> total_candies_count;
    std::cin >> start_jump_height;
    
    for (int i = 0; i < total_candies_count; i++) {
        std::cin >> candiesTypes[i];
        std::cin >> candiesPositions[i];
        std::cin >> candiesWeight[i];
    }
    
    int candies_count = calucalteCandiesNumber(0);
    int caramels_count = calucalteCandiesNumber(1);
    
    std::cout << ((candies_count > caramels_count) ? candies_count : caramels_count) << std::endl;
    
    return 0;
}