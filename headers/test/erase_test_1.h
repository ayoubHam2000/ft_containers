/*******************************************/
/*     created by aben-ham 11/20/22         */
/*******************************************/

#ifndef FT_CONTAINERS_ERASE_TEST_1_H
#define FT_CONTAINERS_ERASE_TEST_1_H

class A{
public:
	static long long nb_assigned;
	static long long nb_delete;
	static long long nb_construct;
	static long long nb_copy_construct;

	int i;
	A(): i(0){
		nb_construct++;
	}

	~A(){
		nb_delete++;
	}

	A(const A &obj): i(obj.i){
		nb_copy_construct++;
	}

	A &operator=(const A &obj){
		i = obj.i;
		nb_delete++;
		return (*this);
	}
};

long long A::nb_assigned = 0;
long long A::nb_delete = 0;
long long A::nb_construct = 0;
long long A::nb_copy_construct = 0;

void test(){

	{
		SETUP;

		ft::vector<A> data;

		for (std::size_t i = 0; i < MAXSIZE; ++i) {
			data.push_back(A());
		}

		timer t;

		ft::vector<A> rty(data.begin(), data.begin() + MAXSIZE);

		t.reset();
		while (!rty.empty()) {
			rty.erase(rty.begin());
		}
		sum += t.get_time();

		PRINT_SUM();

		cout << "nb_construct = " << A::nb_construct << endl;
		cout << "nb_copy_construct = " << A::nb_copy_construct << endl;
		cout << "nb_assigned = " << A::nb_assigned << endl;
		cout << "nb_delete = " << A::nb_delete << endl;
	}
	A::nb_construct = 0;
	A::nb_copy_construct = 0;
	A::nb_assigned = 0;
	A::nb_delete = 0;
	{
		SETUP;

		std::vector<A> data;

		for (std::size_t i = 0; i < MAXSIZE; ++i) {
			data.push_back(A());
		}

		timer t;

		std::vector<A> rty(data.begin(), data.begin() + MAXSIZE);

		t.reset();
		while (!rty.empty()) {
			rty.erase(rty.begin());
		}
		sum += t.get_time();

		PRINT_SUM();

		cout << "nb_construct = " << A::nb_construct << endl;
		cout << "nb_copy_construct = " << A::nb_copy_construct << endl;
		cout << "nb_assigned = " << A::nb_assigned << endl;
		cout << "nb_delete = " << A::nb_delete << endl;
	}

}

#endif //FT_CONTAINERS_ERASE_TEST_1_H
