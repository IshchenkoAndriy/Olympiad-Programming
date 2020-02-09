#include <iostream>
#include <inttypes.h>
#include <math.h>

#define RANGE_MIN 10
#define RANGE_MAX 99

int32_t GetDivisorCount(int32_t divisor, int64_t min, int64_t max){
	int32_t divisor_count = max / divisor - min / divisor;
	divisor_count += ((min % divisor) == 0) ? 1 : 0;
	return divisor_count;
}

int main(){
	int32_t K, X;
	int32_t T;
	int64_t result;

	//std::cin >> T;
	
	//for(int i = 0; i < T; i++){
		std::cin >> K;
		std::cin >> X;
		
		result = 0;
		switch(K){
			case 1: //std::cout << GetDivisorCount(X, RANGE_MIN, RANGE_MAX - 1) << std::endl;
				for(int j = RANGE_MIN; j <= RANGE_MAX; j++)
							if(j % X == 0) std::cout << "Num: " << j << " " << X << " * " << j / X << std::endl;
			break;
			
			case 2:{/*
				for(int j = RANGE_MIN; j <= RANGE_MAX; j++)
					result += GetDivisorCount(X, j * 100 + RANGE_MIN, j * 100 + RANGE_MAX - 1);
				std::cout << result << std::endl;*/
				
				int prev = 0;
				
				for(int j = RANGE_MIN; j <= RANGE_MAX; j++)
					for(int m = j * 100 + RANGE_MIN; m <= j * 100 + RANGE_MAX; m++)
							if(m % X == 0) {
								if(prev){ 
									if ((m / X) - prev > 1) {
										std::cout << "--------------------------" << prev + 1 << std::endl; 
									}
									prev = m / X;
								}
								else prev = m / X;
								std::cout << "Num: " << m << " " << X << " * " << m / X << std::endl;
							}
			
					std::cout << GetDivisorCount(X, 1000, 9999) << std::endl;
			}
			break;
			
			case 3:{/*
				result = 0;
				for(int j = RANGE_MIN; j <= RANGE_MAX; j++)
					for(int k = RANGE_MIN; k <= RANGE_MAX; k++)
						result += GetDivisorCount(X, j * 10000 + k * 100 + RANGE_MIN, j * 10000 + k * 100 + RANGE_MAX);
				std::cout << result << std::endl;*/
				int prev = 0;
				
				for(int j = RANGE_MIN; j <= RANGE_MAX; j++)
					for(int k = RANGE_MIN; k <= RANGE_MAX; k++)
						for(int m = j * 10000 + k * 100 + RANGE_MIN; m <= j * 10000 + k * 100 + RANGE_MAX; m++)
							if(m % X == 0) {
								if(prev){ 
									if ((m / X) - prev > 1) {
										std::cout << "--------------------------" << prev + 1 << std::endl; 
									}
									prev = m / X;
								}
								else prev = m / X;
								std::cout << "Num: " << m << " " << X << " * " << m / X << std::endl;
							}
			}
			break;
			
			case 4:{
				for(int j = RANGE_MIN; j <= RANGE_MAX; j++)
					for(int k = RANGE_MIN; k <= RANGE_MAX; k++)
						for(int l = RANGE_MIN; l <= RANGE_MAX; l++)
							result += GetDivisorCount(X, l * 1000000 + k * 10000 + j * 100 + RANGE_MIN, l * 1000000 + k * 10000 + j * 100 + RANGE_MAX);
				std::cout << result << std::endl;
			}
			break;
			
			case 5:{
				for(int j = RANGE_MIN; j <= RANGE_MAX; j++)
					for(int k = RANGE_MIN; k <= RANGE_MAX; k++)
						for(int l = RANGE_MIN; l <= RANGE_MAX; l++)
							for(int m = RANGE_MIN; m <= RANGE_MAX; m++)
								result += GetDivisorCount(X, m * 100000000 + l * 1000000 + k * 10000 + j * 100 + RANGE_MIN, m * 100000000 + l * 1000000 + k * 10000 + j * 100 + RANGE_MAX);
				std::cout << result << std::endl;
			}
			break;
		}
	
	//}
}