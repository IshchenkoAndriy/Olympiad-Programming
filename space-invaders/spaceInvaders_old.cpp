#include <iostream>

int main ()
{
    unsigned int invaders_count[100];
    unsigned int columns_count;
    unsigned int start_position;
    unsigned int number_of_actions = 0;
    
    unsigned int invaders_left = 0;
    unsigned int invaders_right = 0;
    unsigned int columns_left = 0;
    unsigned int columns_right = 0;
    
    std::cin >> columns_count;
    std::cin >> start_position;
    
    for (int i = 0; i < columns_count; i++) {
        std::cin >> invaders_count[i];
        
        if (i < start_position) {
            invaders_left += invaders_count[i];
        } else if (i > start_position) {
            invaders_right += invaders_count[i];
        }
    }
    
    number_of_actions = invaders_count[start_position] + invaders_left + invaders_right;
    
    columns_left = start_position > 0 ? start_position - 1 : 0;
    columns_right = (columns_count - start_position) > 0 ? columns_count - start_position : 0;
    
    number_of_actions += (columns_left >= columns_right) ? columns_left + 2 * columns_right : 2 * columns_left + columns_right;
    
    std::cout << invaders_count[start_position] << std::endl;
    std::cout << invaders_left << std::endl;
    std::cout << invaders_right << std::endl;
    
    std::cout << number_of_actions << std::endl;
    
    return 0;
}