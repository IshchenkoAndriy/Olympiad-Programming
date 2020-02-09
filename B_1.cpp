#include <inttypes.h>
#include <iostream>

void quicksort(int32_t A[], int32_t low, int32_t high) {
	int32_t i = low;
	int32_t j = high;
	int32_t x = A[(low + high) / 2];
	
	do {
		while (A[i] < x) {
			i++;
		}
		while (A[j] > x) {
			j--;
		}
		
		if (i <= j) {
			int32_t temp = A[i];
			A[i] = A[j];
			A[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);
	
	if (low < j) {
		quicksort(A, low, j);
	}
	if (i < high) {
		quicksort(A, i, high);
	}
}

int main() {
	char c;
	int32_t count;
	int32_t n, m, x, y;
	int32_t mas[50000];
	int32_t buf[50000];
	
	std::cin >> n >> m;
	
	for (int32_t i = 0; i < n; i++) {
		std::cin >> mas[i];
	}
	
	for (int32_t i = 0; i < m; i++) {
		std::cin >> c >> x >> y;
		
		switch (c) {
			case 'c':
				mas[x] = y;
				break;
				
			case 'q':
				for (int32_t j = x; j <= y; j++) {
					buf[j - x] = mas[j];
				}
				
				quicksort(buf, 0, y - x);
				
				count = 1;
				for (int32_t j = 1; j <= y - x; j++) {
					if (buf[j] != buf[j - 1]) {
						count++;
					}
				}
				
				std::cout << count << std::endl;
				break;
		}
	}
	
	return 0;
}
