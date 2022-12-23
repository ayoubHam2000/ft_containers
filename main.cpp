#include "headers/ft_containers_foxer_test/foxer.h"



template <typename std_container, typename ft_container>
void evaluateResult(TestOn<std_container>& std_test, TestOn<ft_container>& ft_test)
{
	std_test.run();
	ft_test.run();
	TestOnType::printResult(std_test, ft_test);
	std_test.reset();
	ft_test.reset();
}


int main(){
	typedef track_allocator<int> allocator;
    TestOn<std::vector<int, allocator> > std_test;
    TestOn<_vector<int, allocator> > ft_test;

	TestOnType::printInfo();
	TestOnType::printVectorHeader();

	std_test.name = "Insert";
	std_test.testFunction = &TestOn<std::vector<int, allocator> >::test;
	ft_test.testFunction = &TestOn<_vector<int, allocator> >::test;
	evaluateResult(std_test, ft_test);


	std_test.name = "Insert";
	std_test.testFunction = &TestOn<std::vector<int, allocator> >::test;
	ft_test.testFunction = &TestOn<_vector<int, allocator> >::test;
	evaluateResult(std_test, ft_test);

	return (0);
}