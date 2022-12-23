/*******************************************/
/*     created by aben-ham 12/23/22         */
/*******************************************/

#ifndef FT_CONTAINERS_TESTON_HPP
#define FT_CONTAINERS_TESTON_HPP

#include "common.h"
#include "statistic_tracker.h"



template <class containerType>
class TestOn{
public:
	typedef containerType container;
	typedef void (TestOn::* functionPointer)();
	//typedef std::vector<int> container;
public:
	std::set<typename containerType::value_type> 	c;
	time_t											time;
	bool											leaks;
	statistic_tracker								s_tracker;
	std::string 									name;
	functionPointer 								testFunction;
public:
	TestOn() : c(), time(0), leaks(false) {}
	TestOn(const TestOn& other): c(other.c), time(other.time), leaks(other.leaks) {}
	TestOn&	operator=(const TestOn& other){
		this->c = other.c;
		this->leaks = other.leaks;
		this->time = other.time;
		return (*this);
	}
	~TestOn(){}


public:
	void run(){
		time = get_time();
		(this->*testFunction)();
		time = get_time() - time;
		leaks = memory_tracker::allocation_empty();
		s_tracker = memory_tracker::s;
		memory_tracker::reset();
	}

	void reset(){
		c.clear();
		time = 0;
		leaks = false;
	}

	void test(){
		container a;

		{
			for (int i = 0; i != 10000; i++){
				a.push_back(i);
			}
		}

		c.insert(a.begin(), a.end());
	}

public:
	static time_t get_time(void)
	{
		struct timeval time_now;

		gettimeofday(&time_now, NULL);
		time_t msecs_time = (time_now.tv_sec * 1e6) + (time_now.tv_usec);
		return (msecs_time);
	}

	template <typename container1, typename container2>
	static bool compareContainers(container1& c1, container2& c2)
	{
		if (c1.size() != c2.size())
			return (false);
		typename container1::iterator first1 = c1.begin();
		typename container2::iterator first2 = c2.begin();
		typename container1::iterator last1 = c1.end();
		typename container2::iterator last2 = c2.end();
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
			if (*first1 != *first2)
				return false;
		return true;
	}

	static void printInfo(){
		std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "|                                           INFO                                           |" << std::endl;
		std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
		std::cout << BLUE << "STATISTICS Filed " << YELLOW;
		std::cout << "Contains [nb_allocation, nb_deallocate, nb_construct, nb_destruct, nb_bad_construct, nb_bad_destruct, nb_bad_deallocate]" << std::endl;
		std::cout << "The blue number is produced by the std, while the other is produced using the ft method" << std::endl;;
		std::cout << BLUE << "nb_bad_construct, nb_bad_destruct, nb_bad_deallocate"<< YELLOW << " should be zero" << std::endl;;
		std::cout << BLUE << "nb_bad_construct :: " << YELLOW << "Called construct on null || Called construct on initialized memory" << std::endl;
		std::cout << BLUE << "nb_bad_destruct :: " << YELLOW << "Called destroy on null || Called destroy on uninitialized memory" << std::endl;
		std::cout << BLUE << "nb_bad_deallocate :: " << YELLOW << "Called deallocate on non-allocated address || Called deallocate with wrong block size" << std::endl;
		std::cout << BLUE << "SAME Filed :: " << YELLOW << "Ok if the content of the containers are equals !! (other errors has no effect)" << std::endl;
		std::cout << RESET;
	}

	static void printElement(std::string t, std::string color) {
		t = color + t + RESET;
		std::cout << std::left << std::setw(30) << std::setfill(' ') << t;
	}

	static void printElement(bool flag) {
		std::string t;
		if (flag)
			t = GREEN  "OK"  RESET;
		else
			t = RED "KO"  RESET;
		std::cout << std::left << std::setw(30) << std::setfill(' ') << t;
		std::flush(std::cout);
	}

	static double round(double value, int places) {
		long factor = (long) std::pow(10, places);
		value = value * factor;
		long tmp = std::round(value);
		return (double) tmp / factor;
	}

	static std::string getTimeInUnitTime(time_t t){
		std::stringstream  a;
		if (t < 1000)
			a << t << "us";
		else if (t < 1000000)
			a << std::fixed << std::setprecision(2) << t / 1000.0 << "ms";
		else
			a << std::fixed << std::setprecision(2) << t / 1000000.0 << "s";
		return a.str();
	}

	static void printVectorHeader(){
		std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "|                                          VECTOR                                          |" << std::endl;
		std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
		printElement("FUNCTION", BLUE);
		printElement("RESULT", BLUE);
		printElement("SAME", BLUE);
		printElement("LEAKS", BLUE);
		printElement("FT TIME", BLUE);
		printElement("STD TIME", BLUE);
		printElement("SLOWER BY", BLUE);
		printElement("SIZE", BLUE);
		printElement("STATISTICS", BLUE);
		std::cout << std::endl;
	}

	template <typename std_container, typename ft_container>
	static void printResult(TestOn<std_container>& std_test, TestOn<ft_container>& ft_test){
		printElement(std_test.name, YELLOW);

		bool isSame = compareContainers(std_test.c, ft_test.c);
		bool leaks = memory_tracker::allocation_empty();
		bool errors = !isSame || !leaks || ft_test.s_tracker.nb_bad_construct || ft_test.s_tracker.nb_bad_deallocate || ft_test.s_tracker.nb_bad_destruct || ft_test.s_tracker.nb_allocation != ft_test.s_tracker.nb_deallocate;
		printElement(!errors);
		printElement(isSame);
		printElement(leaks);

		printElement(getTimeInUnitTime(ft_test.time), GREEN);
		printElement(getTimeInUnitTime(std_test.time), GREEN);
		printElement(std::to_string(std::round((1000.0 * ft_test.time / std_test.time)) / 1000.0) + "x", GREEN);
		printElement(std::to_string(std_test.c.size()) + "-" + std::to_string(ft_test.c.size()), GREEN);

		std::cout
			<< "[a " << BLUE << std_test.s_tracker.nb_allocation << WHITE << "-" << (ft_test.s_tracker.nb_allocation != ft_test.s_tracker.nb_deallocate ? RED : GREEN) << ft_test.s_tracker.nb_allocation << WHITE
			<< ", de " << BLUE << std_test.s_tracker.nb_deallocate << WHITE << "-" << (ft_test.s_tracker.nb_deallocate != ft_test.s_tracker.nb_allocation ? RED : GREEN) << ft_test.s_tracker.nb_deallocate << WHITE
			<< ", c " << BLUE << std_test.s_tracker.nb_construct << WHITE << "-" << ft_test.s_tracker.nb_construct
			<< ", ds " << BLUE << std_test.s_tracker.nb_destruct << WHITE << "-" << ft_test.s_tracker.nb_destruct
			<< ", b_c " << BLUE << std_test.s_tracker.nb_bad_construct << WHITE << "-" << (ft_test.s_tracker.nb_bad_construct ? RED : GREEN) << ft_test.s_tracker.nb_bad_construct << WHITE
			<< ", b_ds " << BLUE << std_test.s_tracker.nb_bad_destruct << WHITE << "-" << (ft_test.s_tracker.nb_bad_destruct ? RED : GREEN) << ft_test.s_tracker.nb_bad_destruct << WHITE
			<< ", b_de " << BLUE << std_test.s_tracker.nb_bad_deallocate << WHITE << "-" << (ft_test.s_tracker.nb_bad_deallocate ? RED : GREEN) << ft_test.s_tracker.nb_bad_deallocate << WHITE
			<< "]" << RESET;
		std::cout << std::endl;
	}

};
typedef TestOn<std::vector<int> > TestOnType;

#endif //FT_CONTAINERS_TESTON_HPP
