#include "headers/ft_containers_foxer_test/foxer.h"
#include <list>

template <class T>
struct IsNotInt{
	static const int value = true;
};

template <>
struct IsNotInt<int>{
	static const int value = false;
};

template <class t>
void function(typename std::enable_if<IsNotInt<t>::value, t>::type a){
	return ;
}


int main(){


	function<double>(5);

	return (0);
}