#include <iostream>

struct block{
   char sex;
   int start, end;
};

int main(){

   int blocks;
   block b[1000];
   int count_c = 0, count_m = 0, count_f = 0;
   int diapasones[5];
   char diap_sex[3] = {'c', 'f', 'm'};
   int dead_count[3] = {0, 0, 0};
   
   std::cin >> blocks;

   for(int i = 0; i < blocks; i++){
       b[i].start = (i > 0) ? b[i - 1].end : 0;
       std::cin >> b[i].sex;
       std::cin >> b[i].end;
       
       
       if(b[i].sex == 'c') count_c += b[i].end;
       if(b[i].sex == 'f') count_f += b[i].end;
	    if(b[i].sex == 'm') count_m += b[i].end;
       b[i].end += b[i].start;
   }
   
   diapasones[0] = 0;
   diapasones[1] = count_c;
   diapasones[2] = diapasones[1] + count_f;
   diapasones[3] = diapasones[2] + count_m;
   
   for(int i = 0; i < blocks; i++){
       for(int j = 0; j < 3; j++){
			if(b[i].start >= diapasones[j] && b[i].start < diapasones[j + 1]){
				if(diap_sex[j] != b[i].sex){
					if(b[i].end >= diapasones[j + 1]){
					   dead_count[j] += diapasones[j + 1] - b[i].start;
				   }
				   else dead_count[j] += b[i].end - b[i].start;
				}
			}
			if(b[i].end >= diapasones[j] && b[i].end <= diapasones[j + 1]){
				if(!(b[i].start >= diapasones[j] && b[i].start < diapasones[j + 1])){
					if(diap_sex[j] != b[i].sex){
						dead_count[j] += b[i].end - diapasones[j];
					}
				}
			}
			if(b[i].start < diapasones[j] && b[i].end > diapasones[j + 1]){
				dead_count[j] += diapasones[j + 1] - diapasones[j];
			}
	   }
   }
   
	int max = 0;
	for(int i = 1; i < 3; i++){
		if(dead_count[max] < dead_count[i]) max = i;
	}
	
	switch(max){
		case 0:	std::cout << dead_count[1] + dead_count[2] << std::endl; break;
		case 1: std::cout << dead_count[0] + dead_count[2] << std::endl; break;
		case 2: std::cout << dead_count[0] + dead_count[1] << std::endl; break;
	}
	//std::cout << dead_count[0] << " " << dead_count[1] << " " << dead_count[2] << std::endl;
	return 0;
}
