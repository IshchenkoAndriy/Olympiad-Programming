#include <iostream>
#include <inttypes.h>
#include <math.h>

int main(){
	int32_t prime[100000] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
	int32_t count_prime = 16;
	
	int64_t num;
	int32_t T;

	std::cin >> T;
	
	for(int i = 0; i < T; i++){
		std::cin >> num;
		
		for(int testing_num = prime[count_prime - 1] + 2; testing_num <= sqrt(num); testing_num += 2) {
			
			bool is_prime = true;
			
			for(int j = 0; j < count_prime && sqrt(testing_num) >= prime[j];j++) {
				if (testing_num % prime[j] == 0) {
					is_prime = false;
					break;
				}
			}
			
			if(is_prime){
				prime[count_prime] = testing_num;
				count_prime++;
			}
		}
		bool not_finded = true;
		for(int j = 0; j < count_prime && not_finded; j++){
			if(num % prime[j] == 0){
				std::cout << prime[j];
				num = num / prime[j];
				not_finded = false;
				break;
			}
		}
		if (not_finded) std::cout << num;
		else{
			for(int j = 0; j < count_prime;){
				if(num % prime[j] == 0){
					std::cout << " * " << prime[j];
					num = num / prime[j];
				}
				else{
					j++;
				}
			}
			if(num != 1) std::cout << " * " << num;
		}
		
		std::cout << std::endl;
	}

	return 0;
}