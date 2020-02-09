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
	char c;					// ������� ��������
	int32_t count;			// ˳������� ������� ����� ��������
	int32_t n, 				// n ������� ����� - ���������� ���� ������
			m, 				// m ������� �����, �� ������ ���� ��������
			x, 				// x � ���� �����, ������� � ����� � ��� ������� ������� ������� �������� �� ����� y (0 <= x < n)
			y;				// ���  x, y � ��� �����, �������� ������� � ����� ������, �� ����� ������� ���������� ������� ����� ����� (0 <= x <= y < n)
	int32_t value, 			// ������� ����������� ������
			prev_value,		// ��������� �������� ������� ������ 
			index, 			// ���������� ����� ��������� �������� ������
			sequential;		// ����� ���������� �������� � �����
	std::vector<item> array;// ������ ��� ��������� �������� ������
	
	array.reserve(50000);	// ��������� ���� �� 50 000 �������� ��������
	
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
