#include <iostream>
#include <inttypes.h>

int main() {
	int32_t result = 0;
	int32_t n, num[4000], bigger_left = 0, lower_left = 0, bigger_right = 0, lower_right = 0;
	
	std::cin >> n;
	
	for (int32_t i = 0; i < n; i++) {
		std::cin >> num[i];
	}
	
	for (int32_t i = 0; i < n; i++) {

		for (int32_t j = 0; j < i; j++) {
			if(num[i] < num[j]) bigger_left++;
			else lower_left++;
		}
		
		for (int32_t j = i + 1; j < n; j++) {
			if(num[i] < num[j]) bigger_right++;
			else lower_right++;
		}

	}
	std::cout << bigger_left + lower_right << " " << bigger_right + lower_left << std::endl;
	if (bigger_left + lower_right > bigger_right + lower_left) {
		std::cout << "Meg" << std::endl;
	}
	else  {
		std::cout << "Stewie" << std::endl;
	} 
	
	return 0;
}
