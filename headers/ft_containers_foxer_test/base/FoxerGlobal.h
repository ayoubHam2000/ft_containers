/*******************************************/
/*     created by aben-ham 12/25/22         */
/*******************************************/

#ifndef FT_CONTAINERS_FOXERGLOBAL_H
#define FT_CONTAINERS_FOXERGLOBAL_H

#include "common.h"

class FoxerGlobal {
public:
	static std::vector<int>									random_values_int;
	static std::vector<std::string>							random_values_string;
	static std::vector<std::pair<time_t, std::string> >		save_time;
	static void init_random_int(int size, int seed);
	static void init_random_string(int size, int seed);
};


#endif //FT_CONTAINERS_FOXERGLOBAL_H
