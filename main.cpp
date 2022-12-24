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

struct Object{
	int i;
	int *p;

	Object(): i(), p(nullptr){}
	Object(const Object& other): i(other.i), p(nullptr){
		if (other.p){
			p = new int();
			*p = *other.p;
		}
	}
	~Object(){
		delete p;
	}
	Object& operator=(const Object& other){
		Object tmp(other);
		delete p;
		i = other.i;
		p = other.p;
		tmp.p = nullptr;
		return (*this);
	}

	bool operator==(const Object& other) const{
		return (i == other.i);
	}

	bool operator!=(const Object& other) const{
		return !(operator==(other));
	}
};

void vectorTests(){

	{
		typedef track_allocator<int> allocator;
		TestOn<std::vector<int, allocator> > std_test;
		TestOn<_vector<int, allocator> > ft_test;

		std_test.name = "Construct_Int";
		std_test.testFunction = &TestOn<std::vector<int, allocator> >::construct;
		ft_test.testFunction = &TestOn<_vector<int, allocator> >::construct;
		evaluateResult(std_test, ft_test);
	}

	{
		typedef Object type;
		typedef track_allocator<type> allocator;
		TestOn<std::vector<type, allocator> > std_test;
		TestOn<_vector<type, allocator> > ft_test;

		std_test.name = "Construct_Object";
		std_test.testFunction = &TestOn<std::vector<type, allocator> >::construct;
		ft_test.testFunction = &TestOn<_vector<type, allocator> >::construct;
		evaluateResult(std_test, ft_test);
	}
}

int main(){

	TestOnType::printInfo();
	TestOnType::printVectorHeader();
	vectorTests();



	return (0);
}