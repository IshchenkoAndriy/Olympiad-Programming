#include <inttypes.h>
#include <iostream>
#include <vector>

struct item{
	item(int32_t elem_index, int32_t elem_count, int32_t elem_value){
		index = elem_index;
		count = elem_count;
		value = elem_value;
	}
	
	item(int32_t elem_index, int32_t elem_value){
		index = elem_index;
		count = 1;
		value = elem_value;
	}
	
	int32_t index;
	int32_t count;
	int32_t value;
};

int main() {
	char c;					// Поточна операцыя
	int32_t count;			// Лічильник кількості різних елементів
	int32_t n, 				// n кількість чисел - початковий вміст масиву
			m, 				// m кількість рядків, які містять опис операцій
			x, 				// x – ціле число, позиція в масиві в якій потрібно замінити поточне значення на число y (0 <= x < n)
			y;				// або  x, y – цілі числа, відповідно початок і кінець відрізка, на якому потрібно порахувати кількість різних чисел (0 <= x <= y < n)
	int32_t value, 			// Елемент початкового масиву
			prev_value,		// Попередній введений елемент масиву 
			index, 			// Порядковий номер зчитаного елементу масиву
			sequential;		// Номер додаваємого елементу в масив
	std::vector<item> array;// Вектор для зберігання елементів масиву
	
	array.reserve(50000);	// Резервуємо місце під 50 000 ймовірних елементів
	
	std::cin >> n >> m;
	
	index = 0;
	sequential = 0;
	std::cin >> value;
	array.push_back(item(index, value));
	
	prev_value = value;
	index++;
	
	for (int32_t i = 1; i < n; i++) {
		std::cin >> value;
		if (value == prev_value){
			array[sequential].count++;
			index++;
		}
		else{
			array.push_back(item(index, value));
			sequential++;
			prev_value = value;
			index++;
		}
		
	}
	
	#ifdef DEBUG
	for (size_t i = 0; i < array.size(); i++){
		std::cout << '{' << array[i].index << ", " << array[i].count << ", " << array[i].value << '}' << std::endl;
	}
	#endif
	
	for (int32_t i = 0; i < m; i++) {
		std::cin >> c >> x >> y;
		
		switch (c) {
			case 'c':
				if()
				break;
				
			case 'q':
				
				std::cout << count << std::endl;
				break;
		}
	}

	return 0;
}
