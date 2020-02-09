#include <iostream>

#define MIN(X, Y) ((X < Y) ? X : Y)

int main ()
{
    unsigned long number_of_actions = 0;
    unsigned int columns_count;
    unsigned int start_position;
    
    std::cin >> columns_count;
    std::cin >> start_position;
    
    for (int i = 0; i < columns_count; i++) {
        unsigned int invaders_count = 0;
        std::cin >> invaders_count;
        number_of_actions += invaders_count;
    }
    
//    int columns_left = start_position > 1 ? start_position - 1 : 0;
//    int columns_right = (columns_count - start_position) > 0 ? columns_count - start_position : 0;
//    
//    if (columns_left >= columns_right) {
//        number_of_actions += columns_left + 2 * columns_right;
//    } else {
//        number_of_actions += 2 * columns_left + columns_right;
//    }
    
    number_of_actions += (columns_count - 1) + MIN(start_position - 1, columns_count - start_position);
    
    std::cout << number_of_actions << std::endl;
    
	return 0;
}