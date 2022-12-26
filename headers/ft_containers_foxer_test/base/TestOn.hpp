/*******************************************/
/*     created by aben-ham 12/23/22         */
/*******************************************/

#ifndef FT_CONTAINERS_TESTON_HPP
#define FT_CONTAINERS_TESTON_HPP

#include "common.h"
#include "statistic_tracker.h"
#include "FoxerGlobal.h"

template <class _T1, class _T2>
bool operator==(const std::pair<_T1, _T2> &x, const ft::pair<_T1, _T2> &y)
{
	return (x.first == y.first && x.second == y.second);
}

template <class _T1, class _T2>
bool operator!=(const std::pair<_T1, _T2> &x, const ft::pair<_T1, _T2> &y)
{
	return (!(x == y));
}

template <class T1, class T2>
std::istream& operator>>(std::istream& is, std::pair<T1, T2>& p)
{
	is >> p.first;
	p.second = T2();
	return is;
}

//TODO: capacity
template <class containerType>
class TestOn{
#pragma region Head
public:
	typedef containerType container;
	typedef typename containerType::value_type value_type;
	typedef void (TestOn::* functionPointer)();
	//typedef std::vector<int> container;
public:
	std::list<value_type> 			c;
	time_t							time;
	statistic_tracker				s_tracker;
	std::string 					name;
	functionPointer 				testFunction;

public:
	TestOn() : c(), time(0) {}
	TestOn(const TestOn& other): c(other.c), time(other.time) {}
	TestOn&	operator=(const TestOn& other){
		this->c = other.c;
		this->leaks = other.leaks;
		this->time = other.time;
		return (*this);
	}
	~TestOn(){}


public:
	void run(){
		usleep(1000);
		time = get_time();
		(this->*testFunction)();
		if (time < 0)
			time *= -1;
		else
			time = get_time() - time;
		s_tracker = memory_tracker::s;
		memory_tracker::reset();
	}

	void reset(){
		c.clear();
		time = 0;
	}

	struct Object{
		int i;
		int *p;

		Object(): i(), p(nullptr){}
		explicit Object(int i): i(i), p(nullptr){}
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

		bool operator<(const Object& other) const{
			return (i < other.i);
		}
	};

	template<typename Tp>
	struct CustomComparator : public std::binary_function<Tp, Tp, bool>
	{
		mutable int state;
		CustomComparator(): state(0){}
		CustomComparator(const CustomComparator &other): state(other.state)  {}
		CustomComparator& operator=(const CustomComparator &other){
			state = other.state;
		}
		~CustomComparator(){};

		bool operator()(const Tp& x, const Tp& y) const
		{
			state++;
			return x < y;
		}
	};




#pragma endregion


/*****************************************************************/
// Vector Tests
/*****************************************************************/
#pragma region VectorTest
public:
//TODO test max_size
	void int_vector_general_test1(){
		//test all type of constructor
		//all iterators
		//destructor
		//copy constructor and Assignment
		//size and max_size
		//capacity is an implementation dependent
		//swap

		// resize capacity reserve shrink_to_fit
		//typedef std::vector<int> type;
		typedef container type;

		type a;
		type b(50, value_type());
		try{
			//should throw
			type d(-1, value_type());
			c.push_back(1);
		}catch (...){
			c.push_back(0);

		}
		std::vector<value_type> arr(50, value_type());
		type e(arr.begin(), arr.end());

		const type f(e);
		e = f;
		type g(f);

		swap(a, b);
		swap(b, a);
		a.swap(b);
		b.swap(a);

		c.insert(c.begin(), a.begin(),   a.end());
		c.insert(c.begin(), a.cbegin(),  a.cend());
		c.insert(c.begin(), a.rbegin(),  a.rend());
		c.insert(c.begin(), a.crbegin(), a.crend());

		c.insert(c.begin(), b.begin(),   b.end());
		c.insert(c.begin(), b.cbegin(),  b.cend());
		c.insert(c.begin(), b.rbegin(),  b.rend());
		c.insert(c.begin(), b.crbegin(), b.crend());

		c.insert(c.begin(), e.begin(),   e.end());
		c.insert(c.begin(), e.cbegin(),  e.cend());
		c.insert(c.begin(), e.rbegin(),  e.rend());
		c.insert(c.begin(), e.crbegin(), e.crend());

		c.insert(c.begin(), f.begin(),   f.end());
		c.insert(c.begin(), f.cbegin(),  f.cend());
		c.insert(c.begin(), f.rbegin(),  f.rend());
		c.insert(c.begin(), f.crbegin(), f.crend());

		c.insert(c.begin(), g.begin(),   g.end());
		c.insert(c.begin(), g.cbegin(),  g.cend());
		c.insert(c.begin(), g.rbegin(),  g.rend());
		c.insert(c.begin(), g.crbegin(), g.crend());
	}

	void int_vector_general_test2(){
		//==, !=, <, >, >=, <=
		//insert
		//push_back
		//assign
		//front, back, at, operator[], data

		//typedef std::vector<int> type;
		typedef container type;
		type a;
		type b;

		//1
		b.insert(b.begin(), FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 50);
		b.insert(b.end(), FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 20);
		b.insert(b.end() - 10, FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 20);
		b.insert(b.begin() + 10, FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 20);
		b.insert(b.cbegin() + 20, FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 20);
		b.insert(b.cend() - 20, FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 20);
		b.insert(b.begin(), 10);
		b.insert(b.end() - 1, 30);
		b.insert(b.begin(), 20,30);
		b.insert(b.end() - 1, 20,30);
		b.insert(b.begin() + 30, 20,30);
		b.insert(b.begin() + 10, 20,30);
		b.push_back(30);
		b.push_back(10);
		c.insert(c.begin(), b.begin(),   b.end());

		//2
		c.insert(c.begin(), b.front());
		c.insert(c.begin(), b.back());
		c.insert(c.begin(), b.at(0));
		c.insert(c.begin(), b.at(5));
		c.insert(c.begin(), b[0]);
		c.insert(c.begin(), b[5]);
		try{
			b.at(-1);
			c.push_back(0);
		}catch (...){
			c.push_back(1);
		}
		int *p = b.data();
		c.push_back(*p);
		*p = 20;
		c.push_back(*p);

		//3
		c.push_back(int(a == b));
		c.push_back(int(a != b));
		c.push_back(int(a < b));
		c.push_back(int(a > b));
		c.push_back(int(a <= b));
		c.push_back(int(a >= b));
		a.assign(b.begin(), b.end());
		c.push_back(int(a == b));
		c.push_back(int(a != b));
		c.push_back(int(a < b));
		c.push_back(int(a > b));
		c.push_back(int(a <= b));
		c.push_back(int(a >= b));
		c.insert(c.begin(), a.begin(),   a.end());

		//4
		b.assign(b.begin(), b.end());
		c.insert(c.begin(), b.begin(),   b.end());

		//5
		b.assign(10, 20);
		c.insert(c.begin(), b.begin(),   b.end());
	}

	void int_vector_general_test3(){
		//erase
		//pop_back
		//assign
		//empty
		//get_allocator

		//typedef std::vector<int> type;
		typedef container type;
		type a;
		type b;

		//1
		b.insert(b.begin(), FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 200);
		c.insert(c.begin(), b.begin(),   b.end());

		//2
		while (!b.empty()) {
			b.pop_back();
		}
		c.insert(c.begin(), b.begin(),   b.end());

		//3
		b.insert(b.begin(), FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 200);
		b.erase(b.begin());
		b.erase(b.end() - 1);
		b.erase(b.cbegin() + 2);
		c.insert(c.begin(), b.begin(),   b.end());

		//4
		while (!b.empty())
			b.erase(b.begin());
		c.insert(c.begin(), b.begin(),   b.end());

		//5
		a.assign(b.begin(), b.end());
		c.insert(c.begin(), a.begin(),   a.end());

		//6
		int *p = a.get_allocator().allocate(1);
		a.get_allocator().construct(p, 20);
		a.get_allocator().destroy(p);
		a.get_allocator().deallocate(p, 1);
	}

	void int_vector_general_test4(){
		// resize capacity reserve shrink_to_fit
		//typedef std::vector<int> type;
		typedef container type;

		type v;

		//1
		v.reserve(100);
		if (v.capacity() > 0)
			c.push_back(1);
		else
			c.push_back(0);

		//2
		v.insert(v.begin(), FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 10);
		v.shrink_to_fit();
		if (v.capacity() < 100)
			v.push_back(1);
		else
			v.push_back(0);

		//3
		v.resize(1);
		c.push_back(v.size());
		c.insert(c.begin(), v.begin(), v.end());
		v.resize(1, 20);
		c.push_back(v.size());
		c.insert(c.begin(), v.begin(), v.end());
		try{
			v.resize(-1);
			c.push_back(1);
		}catch (...){
			c.push_back(0);
		}
	}

	//////////
	//Speed///
	/////////

	void run_test_speed(bool is_std, functionPointer function, const std::string &name){
		time = get_time();
		(this->*function)();
		time = get_time() - time;
		FoxerGlobal::save_time.push_back(std::make_pair(time, name));
		std::cout << "*";
		std::flush(std::cout);
	}

	void vector_time_insert(){
		//typedef std::vector<int> type;
		typedef container type;

		size_t size = SIZE_TEST;
		type vector;

		for (int i = 0; i < size; i++){
			vector.insert(vector.begin(), i);
			vector.insert(vector.end(), i);
		}
		for (int i = 0; i < size; i++){
			vector.insert(vector.begin() + 3, i);
		}
		c.insert(c.begin(), vector.begin(), vector.end());
	}

	void vector_time_push_back(){
		//typedef std::vector<int> type;
		typedef container type;

		size_t size = SIZE_TEST;
		type vector;

		for (int i = 0; i < size; i++){
			vector.push_back(i);
		}
	}

	void vector_time_erase(){
		//typedef std::vector<int> type;
		typedef container type;

		size_t size = SIZE_TEST;
		type vector;

		for (int i = 0; i < 10; i++)
			vector.insert(vector.begin(), FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.end());
		time = get_time();
		while (!vector.empty()){
			vector.erase(vector.begin());
		}
	}

	void vector_time_obj_insert(){
		//typedef std::vector<int> type;
		typedef container type;
		typedef typename type::allocator_type::template rebind<Object>::other    		obj_allocator_type;

		bool is_std = std::is_same<type , std::vector<typename type::value_type, typename type::allocator_type> >::value;
		if (is_std){
			typedef std::vector<Object, obj_allocator_type> obj_vector;
			size_t size = SIZE_TEST;
			obj_vector vector;
			for (int i = 0; i < size; i++){
				vector.insert(vector.begin(), Object());
				vector.insert(vector.end(), Object());
			}
			for (int i = 0; i < size; i++){
				vector.insert(vector.begin() + 3, Object());
			}

		}else{
			typedef ft::vector<Object, obj_allocator_type> obj_vector;

			size_t size = SIZE_TEST;
			obj_vector vector;
			for (int i = 0; i < size; i++){
				vector.insert(vector.begin(), Object());
				vector.insert(vector.end(), Object());
			}
			for (int i = 0; i < size; i++){
				vector.insert(vector.begin() + 3, Object());
			}
		}

	}

	void vector_time_obj_erase(){
		//typedef std::vector<int> type;
		typedef container type;
		typedef typename type::allocator_type::template rebind<Object>::other    		obj_allocator_type;

		bool is_std = std::is_same<type , std::vector<typename type::value_type, typename type::allocator_type> >::value;
		if (is_std){
			typedef std::vector<Object, obj_allocator_type> obj_vector;

			size_t size = SIZE_TEST;
			type vector;

			for (int i = 0; i < 10; i++)
				vector.insert(vector.begin(), FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.end());
			time = get_time();
			while (!vector.empty()){
				vector.erase(vector.begin());
			}


		}else{
			typedef ft::vector<Object, obj_allocator_type> obj_vector;

			size_t size = SIZE_TEST;
			type vector;

			for (int i = 0; i < 10; i++)
				vector.insert(vector.begin(), FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.end());
			time = get_time();
			while (!vector.empty()){
				vector.erase(vector.begin());
			}
		}

	}

	void vector_time_iter(){
		typedef std::vector<int> type;
		//typedef container type;

		size_t size = SIZE_TEST;
		type vector;

		for (int i = 0; i < size; i++){
			vector.push_back(i);
		}

		type::iterator it = vector.begin();
		for (int i = 0; i < 1000000; i++){
			(*vector.begin()) = 1;
			(*(vector.end() - 1)) = 8;
			it++;
			--it;
			++it;
			it--;
			vector.cbegin();
			vector.crbegin();
			vector.cend();
			vector.crend();
		}
	}

	void vector_time_from_input_iter(){
		//typedef std::vector<int> type;
		typedef container type;

		size_t size = SIZE_TEST;
		std::stringstream stream;
		for (int i = 0; i < size; i++) {
			if (i < size - 1) {
				stream << i << " ";
			}
			else {
				stream << i;
			}
		}
		std::istringstream str1(stream.str());
		std::istringstream str2(stream.str());
		std::istream_iterator<int> it(str1), end;

		type vector(it, end);

		it = str2;
		vector.insert(vector.end(), it, end);
		c.insert(c.begin(), vector.begin(), vector.end());
	}

	/////////////////////////

	void print_time_test(){
		std::cout << std::endl;
		std::vector<std::pair<time_t, std::string> >::size_type time_size = FoxerGlobal::save_time.size();
		time_size /= 2;
		for (int i = 0; i < time_size; i++){
			printElement(FoxerGlobal::save_time[i].second + "_std-ft", WHITE, 55);
			time_t std_time = FoxerGlobal::save_time[i].first;
			time_t ft_time = FoxerGlobal::save_time[i + time_size].first;
			printElement(getTimeInUnitTime(std_time), GREEN, 20);
			printElement(getTimeInUnitTime(ft_time), GREEN, 25);
			printElement(std::to_string(std::round((1000.0 * ft_time / std_time)) / 1000.0) + "x", GREEN, 25);
			std::cout << std::endl;
		}
		FoxerGlobal::save_time.clear();
	}

	void int_vector_time_general(){
		typedef container type;

		//typedef std::vector<int> type;

		bool is_std = std::is_same<type , std::vector<typename type::value_type, typename type::allocator_type> >::value;
		run_test_speed(is_std, &TestOn<container>::vector_time_insert, "vector_time_insert");
		run_test_speed(is_std, &TestOn<container>::vector_time_push_back, "vector_time_push_back");
		run_test_speed(is_std, &TestOn<container>::vector_time_erase, "vector_time_erase");
		run_test_speed(is_std, &TestOn<container>::vector_time_obj_insert, "vector_time_obj_insert");
		run_test_speed(is_std, &TestOn<container>::vector_time_obj_erase, "vector_time_obj_erase");
		run_test_speed(is_std, &TestOn<container>::vector_time_iter, "vector_time_iter");
		run_test_speed(is_std, &TestOn<container>::vector_time_from_input_iter, "vector_time_from_input_iter");

		std::vector<std::pair<time_t, std::string> >::size_type time_size = FoxerGlobal::save_time.size();
		int i = 0;
		if (!is_std){
			i = time_size / 2;
			print_time_test();
			std::cout << "Total: " << std::endl;
		}
		time = 0;
		for (;i < time_size; i++)
			time += FoxerGlobal::save_time[i].first;
		time *= -1;

	}

#pragma endregion

#pragma region StackTest
public:

	void stack_general_test1(){
		//constructors, destructor
		//copy constructor and Assignment
		//size, empty, top, push, pop, swap

		//typedef std::stack<int, std::vector<int> > type;
		typedef container type;
		typedef typename type::container_type container_type;

		container_type vector(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 100);
		const container_type const_vector(vector);

		type empty;
		type a(vector);
		type b(const_vector);
		const type d(b);
		const type e(d);

		b = a;
		a = b;
		for (int i = 0; i < 100; i++){
			a.push(i);
		}

		while (!a.empty()){
			c.push_back(a.top());
			c.push_back(d.top());
			c.push_back(e.top());
			a.pop();
		}

		while (b.size() != 0){
			c.push_back(b.top());
			b.pop();
		}

		while (!empty.empty()){
			empty.pop();
			c.push_back(empty.top());
		}

		swap(a, b);
		swap(b, a);
		a.swap(b);
		b.swap(a);
	}

	void stack_general_test2(){
		//==, !=, <, >, >=, <=

		//typedef std::stack<int, std::vector<int> > type;
		typedef container type;
		typedef typename type::container_type container_type;

		container_type vector(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 100);
		const container_type const_vector(vector);

		type empty;
		type empty2;
		type a(vector);
		type b(const_vector);


		//1
		c.push_back(int(empty == empty2));
		c.push_back(int(empty != empty2));
		c.push_back(int(empty <  empty2));
		c.push_back(int(empty >  empty2));
		c.push_back(int(empty <= empty2));
		c.push_back(int(empty >= empty2));

		//2
		c.push_back(int(empty == a));
		c.push_back(int(empty != a));
		c.push_back(int(empty <  a));
		c.push_back(int(empty >  a));
		c.push_back(int(empty <= a));
		c.push_back(int(empty >= a));

		//3
		c.push_back(int(a == b));
		c.push_back(int(a != b));
		c.push_back(int(a < b));
		c.push_back(int(a > b));
		c.push_back(int(a <= b));
		c.push_back(int(a >= b));

		//4
		a.push(50);
		c.push_back(int(a == b));
		c.push_back(int(a != b));
		c.push_back(int(a < b));
		c.push_back(int(a > b));
		c.push_back(int(a <= b));
		c.push_back(int(a >= b));
	}


#pragma endregion

#pragma region SetTest

//TODO custom key_compare
public:
	void set_general_test1(){
		//constructors, all iterators, destructor, copy constructor and Assignment
		//size and max_size
		//swap


		//typedef ft::set<int, std::less<int> > type;
		typedef container type;

		std::vector<value_type> arr(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 1000);

		type a;
		type e(arr.begin(), arr.end());
		const type f(e);
		const type h(f);
		e = f;
		type g(f);

		swap(a, e);
		swap(e, a);
		a.swap(e);
		e.swap(a);

		c.insert(c.begin(), a.begin(),   a.end());
		c.insert(c.begin(), a.cbegin(),  a.cend());
		c.insert(c.begin(), a.rbegin(),  a.rend());
		c.insert(c.begin(), a.crbegin(), a.crend());

		c.insert(c.begin(), h.begin(),   h.end());
		c.insert(c.begin(), h.cbegin(),  h.cend());
		c.insert(c.begin(), h.rbegin(),  h.rend());
		c.insert(c.begin(), h.crbegin(), h.crend());

		c.insert(c.begin(), e.begin(),   e.end());
		c.insert(c.begin(), e.cbegin(),  e.cend());
		c.insert(c.begin(), e.rbegin(),  e.rend());
		c.insert(c.begin(), e.crbegin(), e.crend());

		c.insert(c.begin(), f.begin(),   f.end());
		c.insert(c.begin(), f.cbegin(),  f.cend());
		c.insert(c.begin(), f.rbegin(),  f.rend());
		c.insert(c.begin(), f.crbegin(), f.crend());

		c.insert(c.begin(), g.begin(),   g.end());
		c.insert(c.begin(), g.cbegin(),  g.cend());
		c.insert(c.begin(), g.rbegin(),  g.rend());
		c.insert(c.begin(), g.crbegin(), g.crend());
	}

	void set_general_test2(){
		//==, !=, <, >, >=, <=
		//insert
		//find, count, clear

		//typedef std::set<int> type;
		typedef container type;
		typedef typename type::iterator iterator;
		typedef typename type::const_iterator const_iterator;

		std::vector<value_type> arr(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 1000);

		type a;
		type b(arr.begin(), arr.end());
		const type f(b);
		const type h(f);
		b = f;
		type g(f);

		//1
		b.insert(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 50);
		b.insert(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 20);
		b.insert(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 20);
		b.insert(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 20);
		b.insert(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 20);
		b.insert(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 20);
		b.insert(10);

		iterator it = b.begin();
		std::advance(it, 10);
		b.insert(it, 30);
		std::advance(it, -1);
		b.insert(it, 99999999);

		const_iterator c_it = b.begin();
		std::advance(c_it, 9);
		b.insert(c_it, 45);
		std::advance(c_it, 3);
		b.insert(c_it, 99989999);

		b.insert(--b.end(), 79);
		b.insert(++b.begin(), 80);
		b.insert(++b.begin() , 81);
		b.insert(75);
		b.insert(76);
		g.insert(77);
		c.insert(c.begin(), b.begin(), b.end());
		c.insert(c.begin(), g.crbegin(), g.crend());
		c.insert(c.begin(), a.begin(), a.end());



		a.insert(arr.begin(), arr.end());
		iterator start = b.begin();
		const_iterator s_start = start;
		iterator end = b.end();
		start = s_start;
		while (s_start != end){
			iterator isFound = a.find(*s_start);
			if (isFound == a.end()) {
				c.push_back(-1);
			}
			else {
				c.push_back(*isFound);
			}
			c.push_back(a.count(*s_start));
			s_start++;
		}

		//3
		c.push_back(int(a == b));
		c.push_back(int(a != b));
		c.push_back(int(a < b));
		c.push_back(int(a > b));
		c.push_back(int(a <= b));
		c.push_back(int(a >= b));
		a.clear();
		a.insert(b.begin(), b.end());
		c.push_back(int(a == b));
		c.push_back(int(a != b));
		c.push_back(int(a < b));
		c.push_back(int(a > b));
		c.push_back(int(a <= b));
		c.push_back(int(a >= b));
		c.insert(c.begin(), a.begin(),   a.end());

	}

	void set_general_test3(){
		//erase
		//empty
		//get_allocator, key_comp, value_comp

		//typedef std::set<int> type;
		typedef container type;
		typedef typename type::iterator iterator;

		std::vector<value_type> arr(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 1000);

		type a;
		type b(arr.begin(), arr.end());
		const type f(b);
		const type h(f);
		b = f;
		type g(f);

		//1
		b.insert(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 200);
		c.insert(c.begin(), b.begin(),   b.end());

		//2
		while (!b.empty()) {
			b.erase(b.begin());
		}
		c.insert(c.begin(), b.begin(),   b.end());

		//3
		b.insert(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 200);
		b.erase(b.begin(), b.end());

		//4
		//4
		b.insert(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 200);
		iterator it = b.begin();
		std::advance(it, 10);
		b.erase(it);
		it = b.begin();
		std::advance(it, 10);
		std::advance(it, -5);
		b.erase(it);
		it = b.end();
		it--;
		b.erase(it);
		c.insert(c.begin(), b.begin(),   b.end());

		//5
		//4
		b.insert(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 200);
		iterator s = b.begin();
		iterator end = b.end();
		while (s != end){
			typename type::size_type res = b.erase(*(s++));
			c.push_back(res);
			res = b.erase(std::rand() % RANDOM_SIZE);
			c.push_back(res);
		}


		//4
		while (!b.empty())
			b.erase(b.begin());
		c.insert(c.begin(), b.begin(),   b.end());

		//5
		int *p = a.get_allocator().allocate(1);
		a.get_allocator().construct(p, 20);
		a.get_allocator().destroy(p);
		a.get_allocator().deallocate(p, 1);

		//6
		typename type::key_compare cmp = a.key_comp();
		c.push_back(int(cmp(10, 20)));
		c.push_back(int(cmp(20, 10)));

		//7
		typename type::key_compare cmp2 = a.value_comp();
		c.push_back(int(cmp(10, 20)));
		c.push_back(int(cmp(20, 10)));

	}

	void set_general_test4(){
		// key_comp, value_comp, max_size, lower_bound, upper_bound, equal_range

		//typedef std::set<int> type;
		typedef container type;
		typedef typename type::iterator iterator;

		std::vector<value_type> arr(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + 1000);

		type b(arr.begin(), arr.end());
		const type a(b);

		iterator s = b.lower_bound(99999999);
		iterator c_s = b.lower_bound(99999999);
		c.push_back(int(b.end() == s));
		c.push_back(int(b.end() == c_s));

		s = b.upper_bound(99999999);
		c_s = b.upper_bound(99999999);
		c.push_back(int(b.end() == s));
		c.push_back(int(b.end() == c_s));

		std::pair<iterator, iterator> range;
		range.first = b.equal_range(*b.begin()).first;
		range.second = b.equal_range(*b.begin()).second;
		for (iterator it = range.first; it != range.second; ++it){
			c.push_back(*it);
		}

		range.first = b.lower_bound(*b.begin());
		s = b.begin();
		std::advance(s, 10);
		range.second = b.upper_bound(*s);
		for (iterator it = range.first; it != range.second; ++it){
			c.push_back(*it);
		}

		bool is_std = std::is_same<type , std::set<typename type::value_type, typename  type::key_compare, typename type::allocator_type> >::value;
		if (is_std){
			typedef CustomComparator<int> the_cmp;
			typedef std::set<int, the_cmp, track_allocator<int> > new_type;

			the_cmp compare;
			compare.state++;
			new_type a_set(compare);
			for (int i = 0; i < 55; i++)
				a_set.insert(i);
			new_type b_set(compare);
			new_type c_set(a_set.key_comp());
			c.push_back(int(b_set.key_comp().state == a_set.key_comp().state));
			c.push_back(int(c_set.key_comp().state == a_set.key_comp().state));
		}else{
			typedef CustomComparator<int> the_cmp;
			typedef ft::set<int, the_cmp, track_allocator<int> > new_type;

			the_cmp compare;
			compare.state++;
			new_type a_set(compare);
			for (int i = 0; i < 55; i++)
				a_set.insert(i);
			new_type b_set(compare);
			new_type c_set(a_set.key_comp());
			c.push_back(int(b_set.key_comp().state == a_set.key_comp().state));
			c.push_back(int(c_set.key_comp().state == a_set.key_comp().state));
		}

	}


	//////////
	//Speed///
	/////////

	void set_time_insert(){
		//typedef std::set<int> type;
		typedef container type;

		size_t size = TREE_SIZE_TEST;
		type set;

		for (int i = 0; i < size; i++){
			set.insert(i);
			set.insert(set.begin(), i);
			set.insert(set.end(), i);
		}
		c.insert(c.begin(), set.begin(), set.end());
	}

	void set_time_erase(){
		//typedef std::set<int> type;
		typedef container type;

		size_t size = TREE_SIZE_TEST;
		type set;

		for (int i = 0; i < 100; i++)
			set.insert(FoxerGlobal::random_values_int.begin(), FoxerGlobal::random_values_int.begin() + i * 10);
		time = get_time();
		typename type::iterator it = set.begin();
		typename type::iterator e = set.cend();
		while (it != e){
			set.erase(*(it++));
		}
	}

	void set_time_obj_insert(){
		//typedef std::set<int> type;
		typedef container type;
		typedef typename type::allocator_type::template rebind<Object>::other    		obj_allocator_type;

		bool is_std = std::is_same<type , std::set<typename type::value_type, typename  type::key_compare, typename type::allocator_type> >::value;
		if (is_std){
			typedef std::set<Object, std::less<Object>, obj_allocator_type> obj_set;
			size_t size = TREE_SIZE_TEST * 2;
			obj_set set;
			for (int i = 0; i < size; i++){
				set.insert(Object(i));
			}
		}else{
			typedef ft::set<Object, std::less<Object>, obj_allocator_type> obj_set;
			size_t size = TREE_SIZE_TEST * 2;
			obj_set set;
			for (int i = 0; i < size; i++){
				set.insert(Object(i));
			}
		}

	}

	void set_time_obj_erase(){
		//typedef std::set<int> type;

		typedef container type;
		typedef typename type::allocator_type::template rebind<Object>::other    		obj_allocator_type;

		bool is_std = std::is_same<type , std::set<typename type::value_type, typename  type::key_compare, typename type::allocator_type> >::value;
		if (is_std){
			typedef std::set<Object, std::less<Object>, obj_allocator_type> obj_set;

			size_t size = TREE_SIZE_TEST;
			obj_set set;

			for (int i = 0; i < size; i++)
				set.insert(Object(i));
			time = get_time();
			while (!set.empty()){
				set.erase(set.begin());
			}


		}else{
			typedef std::set<Object, std::less<Object>, obj_allocator_type> obj_set;

			size_t size = TREE_SIZE_TEST;
			obj_set set;

			for (int i = 0; i < size; i++)
				set.insert(Object(i));
			time = get_time();
			while (!set.empty()){
				set.erase(set.begin());
			}
		}

	}

	void set_time_iter(){
		//typedef std::set<int> type;
		typedef container type;

		size_t size = TREE_SIZE_TEST;
		type set;

		for (int i = 0; i < size; i++){
			set.insert(i);
		}

		typename type::iterator it = set.begin();
		for (int i = 0; i < 1000000; i++){
			it++;
			--it;
			++it;
			it--;
			set.cbegin();
			set.crbegin();
			set.cend();
			set.crend();
		}
	}

	void set_time_from_input_iter(){
		//typedef std::set<int> type;
		typedef container type;

		size_t size = TREE_SIZE_TEST;
		std::stringstream stream;
		for (int i = 0; i < size; i++) {
			if (i < size - 1) {
				stream << i << " ";
			}
			else {
				stream << i;
			}
		}
		std::istringstream str1(stream.str());
		std::istringstream str2(stream.str());
		std::istream_iterator<int> it(str1), end;

		type set(it, end);
		c.insert(c.begin(), set.begin(), set.end());
		set.clear();

		it = str2;
		set.insert(it, end);
		c.insert(c.begin(), set.begin(), set.end());
	}

	/////////////////////////

	void set_time_general(){
		typedef container type;

		//typedef std::set<int> type;

		bool is_std = std::is_same<type , std::set<typename type::value_type, typename  type::key_compare, typename type::allocator_type> >::value;
		run_test_speed(is_std, &TestOn<container>::set_time_insert, "set_time_insert");
		run_test_speed(is_std, &TestOn<container>::set_time_erase, "set_time_erase");
		run_test_speed(is_std, &TestOn<container>::set_time_obj_insert, "set_time_obj_insert");
		run_test_speed(is_std, &TestOn<container>::set_time_obj_erase, "set_time_obj_erase");
		run_test_speed(is_std, &TestOn<container>::set_time_iter, "set_time_iter");
		run_test_speed(is_std, &TestOn<container>::set_time_from_input_iter, "set_time_from_input_iter");

		std::vector<std::pair<time_t, std::string> >::size_type time_size = FoxerGlobal::save_time.size();
		int i = 0;
		if (!is_std){
			i = time_size / 2;
			print_time_test();
			std::cout << "Total: " << std::endl;
		}
		time = 0;
		for (;i < time_size; i++)
			time += FoxerGlobal::save_time[i].first;
		time *= -1;

	}


#pragma endregion

#pragma region MapTest

//TODO custom key_compare
public:
	void map_general_test1(){
		//constructors, all iterators, destructor, copy constructor and Assignment
		//size and max_size
		//swap


		//typedef std::map<int, int, std::less<int> > type;
		typedef container type;
		typedef typename type::value_type map_value_type;

		std::vector<map_value_type> arr;
		for (int i = 0; i < TREE_SIZE_TEST; i++){
			arr.push_back(map_value_type(FoxerGlobal::random_values_int[i], FoxerGlobal::random_values_int[i]));
		}

		type a;
		type e(arr.begin(), arr.end());
		const type f(e);
		const type h(f);
		e = f;
		type g(f);

		swap(a, e);
		swap(e, a);
		a.swap(e);
		e.swap(a);

		c.insert(c.begin(), a.begin(),   a.end());
		c.insert(c.begin(), a.cbegin(),  a.cend());
		c.insert(c.begin(), a.rbegin(),  a.rend());
		c.insert(c.begin(), a.crbegin(), a.crend());

		c.insert(c.begin(), h.begin(),   h.end());
		c.insert(c.begin(), h.cbegin(),  h.cend());
		c.insert(c.begin(), h.rbegin(),  h.rend());
		c.insert(c.begin(), h.crbegin(), h.crend());

		c.insert(c.begin(), e.begin(),   e.end());
		c.insert(c.begin(), e.cbegin(),  e.cend());
		c.insert(c.begin(), e.rbegin(),  e.rend());
		c.insert(c.begin(), e.crbegin(), e.crend());

		c.insert(c.begin(), f.begin(),   f.end());
		c.insert(c.begin(), f.cbegin(),  f.cend());
		c.insert(c.begin(), f.rbegin(),  f.rend());
		c.insert(c.begin(), f.crbegin(), f.crend());

		c.insert(c.begin(), g.begin(),   g.end());
		c.insert(c.begin(), g.cbegin(),  g.cend());
		c.insert(c.begin(), g.rbegin(),  g.rend());
		c.insert(c.begin(), g.crbegin(), g.crend());
	}

	void map_general_test2(){
		//==, !=, <, >, >=, <=
		//insert
		//find, count, clear

		//typedef ft::map<int, int, std::less<int> > type;
		typedef container type;
		typedef typename type::iterator iterator;
		typedef typename type::const_iterator const_iterator;
		typedef typename type::value_type map_value_type;

		std::vector<map_value_type> arr;
		for (int i = 0; i < TREE_SIZE_TEST; i++){
			arr.push_back(map_value_type(FoxerGlobal::random_values_int[i], FoxerGlobal::random_values_int[i]));
		}


		type a;
		type b(arr.begin(), arr.end());
		const type f(b);
		const type h(f);
		b = f;
		type g(f);

		//1
		b.insert(arr.begin(), arr.begin() + 50);
		b.insert(arr.begin(), arr.begin() + 20);
		b.insert(arr.begin(), arr.begin() + 20);
		b.insert(arr.begin(), arr.begin() + 20);
		b.insert(arr.begin(), arr.begin() + 20);
		b.insert(arr.begin(), arr.begin() + 20);
		b.insert(map_value_type(10, 88));

		iterator it = b.begin();
		std::advance(it, 10);
		b.insert(it, map_value_type(30, 88));
		std::advance(it, -1);
		b.insert(it, map_value_type(99999999, 88));

		const_iterator c_it = b.begin();
		std::advance(c_it, 9);
		b.insert(c_it, map_value_type(45, 88));
		std::advance(c_it, 3);
		b.insert(c_it, map_value_type(99989999, 88));

		b.insert(--b.end(), map_value_type(79, 88));
		b.insert(++b.begin(), map_value_type(80, 88));
		b.insert(++b.begin() , map_value_type(94, 88));
		b.insert(map_value_type(99989999, 75));
		b.insert(map_value_type(99989999, 76));
		g.insert(map_value_type(99989999, 77));
		c.insert(c.begin(), b.begin(), b.end());
		c.insert(c.begin(), g.crbegin(), g.crend());
		c.insert(c.begin(), a.begin(), a.end());



		a.insert(arr.begin(), arr.end());
		iterator start = b.begin();
		const_iterator s_start = start;
		iterator end = b.end();
		while (s_start != end){
			iterator isFound = a.find(s_start->first);
			if (isFound == a.end()) {
				c.push_back(map_value_type(-1, 77));
			}
			else {
				c.push_back(*isFound);
			}
			c.push_back(map_value_type(a.count(s_start->first), 77));
			s_start++;
		}

		//3
		c.push_back(map_value_type(int(a == b), 77));
		c.push_back(map_value_type(int(a != b), 77));
		c.push_back(map_value_type(int(a < b), 77));
		c.push_back(map_value_type(int(a > b), 77));
		c.push_back(map_value_type(int(a <= b), 77));
		c.push_back(map_value_type(int(a >= b), 77));
		a.clear();
		a.insert(b.begin(), b.end());
		c.push_back(map_value_type(int(a == b), 77));
		c.push_back(map_value_type(int(a != b), 77));
		c.push_back(map_value_type(int(a < b), 77));
		c.push_back(map_value_type(int(a > b), 77));
		c.push_back(map_value_type(int(a <= b), 77));
		c.push_back(map_value_type(int(a >= b), 77));
		c.insert(c.begin(), a.begin(),   a.end());

	}

	void map_general_test3(){
		//erase
		//empty
		//get_allocator, key_comp, value_comp

		//typedef std::map<int, int, std::less<int> > type;
		typedef container type;
		typedef typename type::iterator iterator;
		typedef typename type::const_iterator const_iterator;
		typedef typename type::value_type map_value_type;

		std::vector<map_value_type> arr;
		for (int i = 0; i < TREE_SIZE_TEST; i++){
			arr.push_back(map_value_type(FoxerGlobal::random_values_int[i], FoxerGlobal::random_values_int[i]));
		}

		type a;
		type b(arr.begin(), arr.end());
		const type f(b);
		const type h(f);
		b = f;
		type g(f);

		//1
		b.insert(arr.begin(), arr.begin() + 200);
		c.insert(c.begin(), b.begin(),   b.end());

		//2
		while (!b.empty()) {
			b.erase(b.begin());
		}
		c.insert(c.begin(), b.begin(),   b.end());

		//3
		b.insert(arr.begin(), arr.begin() + 200);
		b.erase(b.begin(), b.end());

		//4
		//4
		b.insert(arr.begin(), arr.begin() + 200);
		iterator it = b.begin();
		std::advance(it, 10);
		b.erase(it);
		it = b.begin();
		std::advance(it, 10);
		std::advance(it, -5);
		b.erase(it);
		it = b.end();
		it--;
		b.erase(it);
		c.insert(c.begin(), b.begin(),   b.end());

		//5
		//4
		b.insert(arr.begin(), arr.begin() + 200);
		iterator s = b.begin();
		iterator end = b.end();
		while (s != end){
			typename type::size_type res = b.erase((s++)->first);
			c.push_back(map_value_type(res, 77));
			res = b.erase(std::rand() % RANDOM_SIZE);
			c.push_back(map_value_type(res, 77));
		}


		//4
		while (!b.empty())
			b.erase(b.begin());
		c.insert(c.begin(), b.begin(),   b.end());

		//5
		map_value_type *p = a.get_allocator().allocate(1);
		a.get_allocator().construct(p, map_value_type(20, 77));
		a.get_allocator().destroy(p);
		a.get_allocator().deallocate(p, 1);

		//6
		typename type::key_compare cmp = a.key_comp();
		c.push_back(map_value_type(int(cmp(10, 20)), 77));
		c.push_back(map_value_type(int(cmp(20, 10)), 77));

		//7
		typename type::value_compare cmp2 = a.value_comp();
		c.push_back(map_value_type(int(cmp(10, 20)), 77));
		c.push_back(map_value_type(int(cmp(20, 10)), 77));

	}

	void map_general_test4(){
		// key_comp, value_comp, max_size, lower_bound, upper_bound, equal_range

		//typedef std::map<int, int, std::less<int> > type;
		typedef container type;
		typedef typename type::iterator iterator;
		typedef typename type::const_iterator const_iterator;
		typedef typename type::value_type map_value_type;

		std::vector<map_value_type> arr;
		for (int i = 0; i < TREE_SIZE_TEST; i++){
			arr.push_back(map_value_type(FoxerGlobal::random_values_int[i], FoxerGlobal::random_values_int[i]));
		}

		type b(arr.begin(), arr.end());
		const type a(b);

		iterator s = b.lower_bound(99999999);
		iterator c_s = b.lower_bound(99999999);
		c.push_back(value_type(int(b.end() == s), 77));
		c.push_back(value_type(int(b.end() == c_s), 77));

		s = b.upper_bound(99999999);
		c_s = b.upper_bound(99999999);
		c.push_back(value_type(int(b.end() == s), 77));
		c.push_back(value_type(int(b.end() == c_s), 77));

		std::pair<iterator, iterator> range;
		range.first = b.equal_range(b.begin()->first).first;
		range.second = b.equal_range(b.begin()->first).second;
		for (iterator it = range.first; it != range.second; ++it){
			c.push_back(*it);
		}

		range.first = b.lower_bound(b.begin()->first);
		s = b.begin();
		std::advance(s, 10);
		range.second = b.upper_bound(s->first);
		for (iterator it = range.first; it != range.second; ++it){
			c.push_back(*it);
		}

		bool is_std = std::is_same<type , std::map<int, int, typename type::key_compare , typename type::allocator_type> >::value;
		if (is_std){
			typedef CustomComparator<int> the_cmp;
			typedef std::map<int, int, the_cmp > new_type;

			the_cmp compare;
			compare.state++;
			new_type a_map(compare);
			for (int i = 0; i < 55; i++)
				a_map.insert(std::make_pair(i, 77));
			new_type b_set(compare);
			new_type c_set(a_map.key_comp());
			c.push_back(value_type(int(b_set.key_comp().state == a_map.key_comp().state), 77));
			c.push_back(value_type(int(c_set.key_comp().state == a_map.key_comp().state), 77));
		}else{
			typedef CustomComparator<int> the_cmp;
			typedef ft::map<int, int, the_cmp > new_type;

			the_cmp compare;
			compare.state++;
			new_type a_map(compare);
			for (int i = 0; i < 55; i++)
				a_map.insert(ft::make_pair(i, 77));
			new_type b_set(compare);
			new_type c_set(a_map.key_comp());
			c.push_back(value_type(int(b_set.key_comp().state == a_map.key_comp().state), 77));
			c.push_back(value_type(int(c_set.key_comp().state == a_map.key_comp().state), 77));
		}

	}


	//////////
	//Speed///
	/////////

	void map_time_insert(){
		//typedef std::map<int, int> type;
		typedef container type;
		typedef typename type::value_type map_value_type;

		size_t size = TREE_SIZE_TEST;
		type map;

		for (int i = 0; i < size; i++){
			map.insert(map_value_type(i, 77));
			map.insert(map.begin(), map_value_type(i, 77));
			map.insert(map.end(), map_value_type(i, 77));
		}
		c.insert(c.begin(), map.begin(), map.end());
	}

	void map_time_erase(){
		//typedef std::map<int, int> type;
		typedef container type;
		typedef typename type::value_type map_value_type;

		std::vector<map_value_type> arr;
		for (int i = 0; i < TREE_SIZE_TEST; i++){
			arr.push_back(map_value_type(FoxerGlobal::random_values_int[i], FoxerGlobal::random_values_int[i]));
		}

		size_t size = TREE_SIZE_TEST;
		type map;

		for (int i = 0; i < 100; i++)
			map.insert(arr.begin(), arr.begin() + i * 10);
		time = get_time();
		typename type::iterator it = map.begin();
		typename type::iterator e = map.end();
		while (it != e){
			map.erase((it++)->first);
		}
	}

	void map_time_obj_insert(){
		typedef container type;
		//typedef std::map<int, int> type;
		typedef typename type::value_type map_value_type;

		bool is_std = std::is_same<type , std::set<typename type::value_type, typename  type::key_compare, typename type::allocator_type> >::value;

		if (is_std){
			typedef std::map<Object, int, std::less<Object> > obj_map;
			size_t size = TREE_SIZE_TEST * 2;
			obj_map map;
			for (int i = 0; i < size; i++){
				map.insert(std::make_pair(Object(), 77));
			}
		}else{
			typedef ft::map<Object, int, std::less<Object> > obj_map;
			size_t size = TREE_SIZE_TEST * 2;
			obj_map map;
			for (int i = 0; i < size; i++){
				map.insert(ft::make_pair(Object(), 77));
			}
		}

	}

	void map_time_obj_erase(){
		typedef std::map<int, int> type;
		//typedef container type;
		typedef typename type::value_type map_value_type;

		bool is_std = std::is_same<type , std::set<typename type::value_type, typename  type::key_compare, typename type::allocator_type> >::value;

		if (is_std){
			typedef std::map<Object, int, std::less<Object> > obj_map;

			size_t size = TREE_SIZE_TEST;
			obj_map map;

			for (int i = 0; i < size; i++)
				map.insert(std::make_pair(Object(i), 10));
			time = get_time();
			while (!map.empty()){
				map.erase(map.begin());
			}


		}else{
			typedef ft::map<Object,int, std::less<Object> > obj_map;

			size_t size = TREE_SIZE_TEST;
			obj_map map;

			for (int i = 0; i < size; i++)
				map.insert(ft::make_pair(Object(i), 10));
			time = get_time();
			while (!map.empty()){
				map.erase(map.begin());
			}
		}

	}

	void map_time_iter(){
		typedef container type;
		//typedef std::map<int, int> type;
		typedef typename type::value_type map_value_type;



		size_t size = TREE_SIZE_TEST;
		type map;

		for (int i = 0; i < size; i++){
			map.insert(map_value_type(i, 77));
		}

		typename type::iterator it = map.begin();
		for (int i = 0; i < 1000000; i++){
			it++;
			--it;
			++it;
			it--;
			map.cbegin();
			map.crbegin();
			map.cend();
			map.crend();
		}
	}

	void map_time_from_input_iter(){
		//typedef container type;
		//typedef typename type::value_type map_value_type;
		typedef std::map<int, int> type;

		std::stringstream stream;

		// Write some pairs to the stream
		stream << "1 2";

		// Read the pairs from the stream
		std::istringstream str(stream.str());
		std::istream_iterator<std::pair<int, int> > it(str), end;

		/*type map(it, end);
		c.insert(c.begin(), map.begin(), map.end());
		map.clear();

		it = str2;
		map.insert(it, end);
		c.insert(c.begin(), map.begin(), map.end());*/
	}

	/////////////////////////

	void map_time_general(){
		typedef container type;

		//typedef std::set<int> type;

		bool is_std = std::is_same<type , std::set<typename type::value_type, typename  type::key_compare, typename type::allocator_type> >::value;
		run_test_speed(is_std, &TestOn<container>::map_time_insert, "map_time_insert");
		run_test_speed(is_std, &TestOn<container>::map_time_erase, "map_time_erase");
		run_test_speed(is_std, &TestOn<container>::map_time_obj_insert, "map_time_obj_insert");
		run_test_speed(is_std, &TestOn<container>::map_time_obj_erase, "map_time_obj_erase");
		run_test_speed(is_std, &TestOn<container>::map_time_iter, "map_time_iter");
		run_test_speed(is_std, &TestOn<container>::map_time_from_input_iter, "map_time_from_input_iter");

		std::vector<std::pair<time_t, std::string> >::size_type time_size = FoxerGlobal::save_time.size();
		int i = 0;
		if (!is_std){
			i = time_size / 2;
			print_time_test();
			std::cout << "Total: " << std::endl;
		}
		time = 0;
		for (;i < time_size; i++)
			time += FoxerGlobal::save_time[i].first;
		time *= -1;

	}
#pragma endregion

#pragma region Display
	/*****************************************************************/
	// Display Result And Info
	/*****************************************************************/
public:
	static time_t get_time(void)
	{
		struct timeval time_now;

		gettimeofday(&time_now, NULL);
		time_t msecs_time = (time_now.tv_sec * 1e6) + (time_now.tv_usec);
		return (msecs_time);
	}

	//TODO stack max_size
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
		std::cout << BLUE << "SAME Filed :: " << YELLOW << "Ok if the content of the containers are equals and have the same max_size !! (other errors has no effect)" << std::endl;
		std::cout << RESET;
	}

	static void printElement(std::string t, std::string color, int fieldSize) {
		t = color + t + RESET;
		std::cout << std::left << std::setw(fieldSize) << std::setfill(' ') << t;
	}

	static void printElement(bool flag, int fieldSize) {
		std::string t;
		if (flag)
			t = GREEN  "OK"  RESET;
		else
			t = RED "KO"  RESET;
		std::cout << std::left << std::setw(fieldSize) << std::setfill(' ') << t;
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

	static void tableHeader(){
		printElement("FUNCTION", BLUE, 40);
		printElement("RESULT", BLUE, 20);
		printElement("SAME", BLUE, 20);
		printElement("LEAKS", BLUE, 20);
		printElement("FT TIME", BLUE, 20);
		printElement("STD TIME", BLUE, 25);
		printElement("SLOWER BY", BLUE, 25);
		printElement("SIZE", BLUE, 30);
		printElement("STATISTICS", BLUE, 20);
		std::cout << std::endl;
	}

	static void printVectorHeader(){
		std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "|                                          VECTOR                                          |" << std::endl;
		std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
		tableHeader();
	}

	static void printStackHeader(){
		std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "|                                          Stack                                           |" << std::endl;
		std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
		tableHeader();
	}

	static void printSetHeader(){
		std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "|                                           Set                                            |" << std::endl;
		std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
		tableHeader();
	}

	static void printMapHeader(){
		std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "|                                           Map                                            |" << std::endl;
		std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
		tableHeader();
	}

	template <typename std_container, typename ft_container>
	static void printResult(TestOn<std_container>& std_test, TestOn<ft_container>& ft_test){
		printElement(std_test.name, YELLOW, 40);

		bool isSame = compareContainers(std_test.c, ft_test.c);
		bool leaks = memory_tracker::allocation_empty();
		bool errors = !isSame || !leaks || ft_test.s_tracker.nb_bad_construct || ft_test.s_tracker.nb_bad_deallocate
				|| ft_test.s_tracker.nb_bad_destruct || ft_test.s_tracker.nb_allocation != ft_test.s_tracker.nb_deallocate
				|| ft_test.s_tracker.nb_construct != ft_test.s_tracker.nb_destruct;
		printElement(!errors, 20);
		printElement(isSame, 20);
		printElement(leaks, 20);

		printElement(getTimeInUnitTime(ft_test.time), GREEN, 20);
		printElement(getTimeInUnitTime(std_test.time), GREEN, 25);
		printElement(std::to_string(std::round((1000.0 * ft_test.time / std_test.time)) / 1000.0) + "x", GREEN, 25);
		printElement(std::to_string(std_test.c.size()) + "-" + std::to_string(ft_test.c.size()), GREEN, 30);

		std::cout
			<< "[a " << BLUE << std_test.s_tracker.nb_allocation << WHITE << "-" << (ft_test.s_tracker.nb_allocation != ft_test.s_tracker.nb_deallocate ? RED : GREEN) << ft_test.s_tracker.nb_allocation << WHITE
			<< ", de " << BLUE << std_test.s_tracker.nb_deallocate << WHITE << "-" << (ft_test.s_tracker.nb_deallocate != ft_test.s_tracker.nb_allocation ? RED : GREEN) << ft_test.s_tracker.nb_deallocate << WHITE
			<< ", c " << BLUE << std_test.s_tracker.nb_construct << WHITE << "-" << (ft_test.s_tracker.nb_construct != ft_test.s_tracker.nb_destruct ? RED : GREEN) << ft_test.s_tracker.nb_construct << WHITE
			<< ", ds " << BLUE << std_test.s_tracker.nb_destruct << WHITE << "-" << (ft_test.s_tracker.nb_construct != ft_test.s_tracker.nb_destruct ? RED : GREEN) << ft_test.s_tracker.nb_destruct << WHITE
			<< ", b_c " << BLUE << std_test.s_tracker.nb_bad_construct << WHITE << "-" << (ft_test.s_tracker.nb_bad_construct ? RED : GREEN) << ft_test.s_tracker.nb_bad_construct << WHITE
			<< ", b_ds " << BLUE << std_test.s_tracker.nb_bad_destruct << WHITE << "-" << (ft_test.s_tracker.nb_bad_destruct ? RED : GREEN) << ft_test.s_tracker.nb_bad_destruct << WHITE
			<< ", b_de " << BLUE << std_test.s_tracker.nb_bad_deallocate << WHITE << "-" << (ft_test.s_tracker.nb_bad_deallocate ? RED : GREEN) << ft_test.s_tracker.nb_bad_deallocate << WHITE
			<< "]" << RESET;
		std::cout << std::endl;
	}

	static int get_random_int(int i){
		return (FoxerGlobal::random_values_int[i % RANDOM_SIZE]);
	}

	static std::string get_random_string(int i){
		return (FoxerGlobal::random_values_string[i % RANDOM_SIZE]);
	}


#pragma endregion
};



typedef TestOn<std::vector<int> > TestOnType;

#endif //FT_CONTAINERS_TESTON_HPP
