#include "headers/ft_containers_foxer_test/foxer.h"


template <class containerType>
class TestOn{
public:
	//TODO: restore
   // typedef containerType container;
    typedef std::vector<int> container;
public:
    container 			c;
	time_t				time;
	bool				leaks;
	statistic_tracker	s_tracker;
public:
	TestOn() : c(container()), time(0), leaks(false) {}
	TestOn(const TestOn& other): c(other.c), time(other.time), leaks(other.leaks) {}
	TestOn&	operator=(const TestOn& other){
		this->c = other.c;
		this->leaks = other.leaks;
		this->time = other.time;
		return (*this);
	}
	~TestOn(){}
public:
	enum TestTypes{
		INSERT,
		ERASE
	};

public:
	void run(int test_type){
		time = get_time();
		_runTest(test_type);
		time = get_time() - time;
		leaks = memory_tracker::allocation_empty();
		s_tracker = memory_tracker::s;
	}

	void reset(){
		c.clear();
		time = 0;
		leaks = false;
		memory_tracker::reset();
	}

private:
	void test(){
		container a;

		{
			for (int i = 0; i != 100000; i++){
				a.push_back(i);
			}
		}

		c = a;
	}


private:
	void _runTest(int test_type){
		switch (test_type) {
			case INSERT: test(); break;
			case ERASE: test(); break;
		}
	}
};
typedef TestOn<std::vector<int> >::TestTypes TestTypes;


template <typename std_container, typename ft_container>
void evaluateResult(TestOn<std_container>& std_test, TestOn<ft_container>& ft_test, int test_type)
{
	std_test.run(test_type);
	ft_test.run(test_type);
	bool res = compareContainers(std_test.c, ft_test.c);

	std::cout << test_type << " " << res << " " << std_test.time << " " << ft_test.time << " slowerBy " << 1.0 * ft_test.time / std_test.time << std::endl;
	std::cout << std_test.leaks << " " << ft_test.leaks;
	std_test.s_tracker.print();
	ft_test.s_tracker.print();

	std_test.reset();
	ft_test.reset();

}

int main(){
	typedef track_allocator<int> allocator;
    TestOn<std::vector<int, allocator> > std_res;
    TestOn<_vector<int, allocator> > ft_res;


	evaluateResult(std_res, ft_res, TestTypes::INSERT);


	return (0);
}