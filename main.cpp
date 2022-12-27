#include "headers/ft_containers_foxer_test/foxer.h"

#define VEC_COUNTER 0
#define STA_COUNTER 100
#define SET_COUNTER 200
#define MAP_COUNTER 300



void evaluateResult(int test_nb, const std::string& name)
{
	typedef track_allocator<int> allocator;

	typedef std::vector<int, allocator> std_vector_type;
	typedef ft::vector<int, allocator> ft_vector_type;

	typedef std::stack<int, std_vector_type> std_stack_type;
	typedef ft::stack<int, ft_vector_type> ft_stack_type;

	typedef std::set<int, std::less<int>, allocator> std_set_type;
	typedef ft::set<int, std::less<int>, allocator> ft_set_type;

	if (test_nb < STA_COUNTER){ //vector
		typedef TestOn<std_vector_type> std_test_type;
		typedef TestOn<ft_vector_type> ft_test_type;

		std_test_type std_test;
		ft_test_type ft_test;

		std_test.name = name;
		switch (test_nb) {
			case (VEC_COUNTER):
				std_test.testFunction = &std_test_type::int_vector_general_test1;
				ft_test.testFunction = &ft_test_type::int_vector_general_test1;
				break;
			case (VEC_COUNTER + 1):
				std_test.testFunction = &std_test_type::int_vector_general_test2;
				ft_test.testFunction = &ft_test_type::int_vector_general_test2;
				break;
			case (VEC_COUNTER + 2):
				std_test.testFunction = &std_test_type::int_vector_general_test3;
				ft_test.testFunction = &ft_test_type::int_vector_general_test3;
				break;
			case (VEC_COUNTER + 3):
				std_test.testFunction = &std_test_type::int_vector_general_test4;
				ft_test.testFunction = &ft_test_type::int_vector_general_test4;
				break;
			case (VEC_COUNTER + 4):
				std_test.testFunction = &std_test_type::int_vector_general_test5;
				ft_test.testFunction = &ft_test_type::int_vector_general_test5;
				break;
			case (VEC_COUNTER + 5):
				std_test.testFunction = &std_test_type::int_vector_time_general;
				ft_test.testFunction = &ft_test_type::int_vector_time_general;
				break;
			default:
				std::exit(1);
		}

		std_test.run();
		ft_test.run();
		std_test_type::printResult(std_test, ft_test);
		std_test.reset();
		ft_test.reset();
	}
	else if (test_nb < SET_COUNTER){ //stack
		typedef TestOn<std_stack_type> std_test_type;
		typedef TestOn<ft_stack_type> ft_test_type;

		std_test_type std_test;
		ft_test_type ft_test;

		std_test.name = name;
		switch (test_nb) {
			case (STA_COUNTER):
				std_test.testFunction = &std_test_type::stack_general_test1;
				ft_test.testFunction = &ft_test_type::stack_general_test1;
				break;
			case (STA_COUNTER + 1):
				std_test.testFunction = &std_test_type::stack_general_test2;
				ft_test.testFunction = &ft_test_type::stack_general_test2;
				break;
			default:
				std::exit(1);
		}

		std_test.run();
		ft_test.run();
		std_test_type::printResult(std_test, ft_test);
		std_test.reset();
		ft_test.reset();
	}
	else if (test_nb < MAP_COUNTER){ //set
		typedef TestOn<std_set_type> std_test_type;
		typedef TestOn<ft_set_type> ft_test_type;

		std_test_type std_test;
		ft_test_type ft_test;

		std_test.name = name;
		switch (test_nb) {
			case SET_COUNTER:
				std_test.testFunction = &std_test_type::set_general_test1;
				ft_test.testFunction = &ft_test_type::set_general_test1;
				break;
			case SET_COUNTER + 1:
				std_test.testFunction = &std_test_type::set_general_test2;
				ft_test.testFunction = &ft_test_type::set_general_test2;
				break;
			case SET_COUNTER + 2:
				std_test.testFunction = &std_test_type::set_general_test3;
				ft_test.testFunction = &ft_test_type::set_general_test3;
				break;
			case SET_COUNTER + 3:
				std_test.testFunction = &std_test_type::set_general_test4;
				ft_test.testFunction = &ft_test_type::set_general_test4;
				break;
			case SET_COUNTER + 4:
				std_test.testFunction = &std_test_type::set_time_general;
				ft_test.testFunction = &ft_test_type::set_time_general;
				break;
			default:
				std::exit(1);
		}

		std_test.run();
		ft_test.run();
		std_test_type::printResult(std_test, ft_test);
		std_test.reset();
		ft_test.reset();
	}
	else
		exit(1);
}

template <class key, class value>
void evaluateMapResult(int test_nb, const std::string& name){
	typedef track_allocator<std::pair<const key, value> > std_allocator;
	typedef track_allocator<ft::pair<const key, value> > ft_allocator;

	typedef std::map<key, value, std::less<key>, std_allocator> std_map_type;
	typedef ft::map<key, value, std::less<key>, ft_allocator> ft_map_type;

	typedef TestOn<std_map_type> std_test_type;
	typedef TestOn<ft_map_type> ft_test_type;

	std_test_type std_test;
	ft_test_type ft_test;

	std_test.name = name;
	if (test_nb >= MAP_COUNTER){
		switch (test_nb) {
			case MAP_COUNTER:
				std_test.testFunction = &std_test_type::map_general_test1;
				ft_test.testFunction = &ft_test_type::map_general_test1;
				break;
			case MAP_COUNTER + 1:
				std_test.testFunction = &std_test_type::map_general_test2;
				ft_test.testFunction = &ft_test_type::map_general_test2;
				break;
			case MAP_COUNTER + 2:
				std_test.testFunction = &std_test_type::map_general_test3;
				ft_test.testFunction = &ft_test_type::map_general_test3;
				break;
			case MAP_COUNTER + 3:
				std_test.testFunction = &std_test_type::map_general_test4;
				ft_test.testFunction = &ft_test_type::map_general_test4;
				break;
			case MAP_COUNTER + 4:
				std_test.testFunction = &std_test_type::map_time_general;
				ft_test.testFunction = &ft_test_type::map_time_general;
				break;
			default:
				std::exit(1);
		}

		std_test.run();
		ft_test.run();
		std_test_type::printResult(std_test, ft_test);
		std_test.reset();
		ft_test.reset();
	}
	else
		exit(1);
}



void vectorTests(){
	TestOnType::printVectorHeader();
	evaluateResult(VEC_COUNTER, "vector_general_test1");
	evaluateResult(VEC_COUNTER + 1, "vector_general_test2");
	evaluateResult(VEC_COUNTER + 2, "vector_general_test3");
	evaluateResult(VEC_COUNTER + 3, "vector_general_test4");
	evaluateResult(VEC_COUNTER + 4, "vector_general_test5");

	evaluateResult(VEC_COUNTER + 5, "int_vector_time_general");
}

void stackTests(){
	TestOnType::printStackHeader();
	evaluateResult(STA_COUNTER, "stack_general_test1");
	evaluateResult(STA_COUNTER + 1, "stack_general_test2");
}

void setTests(){
	TestOnType::printSetHeader();
	evaluateResult(SET_COUNTER, "set_general_test1");
	evaluateResult(SET_COUNTER + 1, "set_general_test2");
	evaluateResult(SET_COUNTER + 2, "set_general_test3");
	evaluateResult(SET_COUNTER + 3, "set_general_test4");
	evaluateResult(SET_COUNTER + 4, "set_time_general");
}

void mapTests(){
	TestOnType::printMapHeader();
	evaluateMapResult<int, int>(MAP_COUNTER, "map_general_test1");
	evaluateMapResult<int, int>(MAP_COUNTER + 1, "map_general_test2");
	evaluateMapResult<int, int>(MAP_COUNTER + 2, "map_general_test3");
	evaluateMapResult<int, int>(MAP_COUNTER + 3, "map_general_test4");
	evaluateMapResult<int, int>(MAP_COUNTER + 4, "map_time_general");
}

void mainTests(){
	TestOnType::printInfo();
	FoxerGlobal::init_random_int(RANDOM_SIZE, RANDOM_SEED);
	FoxerGlobal::init_random_string(RANDOM_SIZE, RANDOM_SEED);
	vectorTests();
	stackTests();
	setTests();
	mapTests();
}

int main(){
	mainTests();
	return (0);
}