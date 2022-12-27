/*******************************************/
/*     created by aben-ham 12/25/22         */
/*******************************************/

#include "FoxerGlobal.h"

std::vector<int> FoxerGlobal::random_values_int = std::vector<int>();

std::vector<std::string> FoxerGlobal::random_values_string = std::vector<std::string>();

std::vector<std::pair<time_t, std::string> >	 FoxerGlobal::save_time = std::vector<std::pair<time_t, std::string> >();

void FoxerGlobal::init_random_int(int size, int seed){
	random_values_int = std::vector<int>(size, 0);
	std::srand(seed);
	for (int i = 0; i < size; i++){
		random_values_int[i] = (std::rand() % (size * 10));
	}
}

void FoxerGlobal::init_random_string(int size, int seed){
	random_values_string = std::vector<std::string>(size, "");
	std::stringstream res;
	char c;
	std::srand(seed);
	for (int i = 0; i < size; i++){
		for (int j = 0; j < 10; j++){
			c = ((std::rand() % 92) + 34);
			res << i * j;
			res << c;
		}
		random_values_string[i] = res.str();
		res.str("");
	}
}