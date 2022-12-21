//#include "main.h"
//
//#define Vector vector
//#define Map map
//#define Set set
//#define Stack stack
//#include <sys/time.h>
//#include "headers/set.hpp"
//#include <unistd.h>
//
//#include <vector>
//#include <iostream>
//#include <iterator>
//#include <utility>
//#include <ctime>
//#include <iomanip>
//#include <unistd.h>
//#include <signal.h>
//#include <sys/time.h>
//#include <random>
//
//#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
//#define TIME_FAC 3 // the ft::vector methods can be slower up to std::vector methods * TIME_FAC (MAX 20)
//
//time_t get_time(void)
//{
//	struct timeval time_now;
//
//	gettimeofday(&time_now, NULL);
//	time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
//
//	std::allocator<int> a;
//
//	return (msecs_time);
//}
//
//template <typename Iter1, typename Iter2>
//bool compareMaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
//{
//	for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
//		if (*first1 != *first2)
//			return false;
//	return true;
//}


#include "./headers/unit_test/sources/system/system_methods.ipp"
#include "./headers/unit_test/sources/map_tests/__service.ipp"

template <class T, class V>
std::vector<int> comparator_test(std::map<T, V> mp) {

	std::vector<int> v;
	fillMap(mp);
	for (typename std::map<T, V>::iterator it = mp.begin(); it != mp.end(); it++) { v.push_back(it->first); }
	for (typename std::map<T, V>::iterator it = --mp.end(); it != mp.begin(); it--) { v.push_back(it->first); }
	std::map<int, int, std::greater<int> > mp1;
	fillMap(mp1);
	v.push_back(mp1.begin()->first);
	mp1.erase(41);
	v.push_back(mp1.begin()->first);
	mp1.erase(29);
	v.push_back(mp1.begin()->first);
	std::map<int, int, std::greater<int> > mp2;
	mp2.insert(std::make_pair(3, 3));
	v.push_back(mp2.begin()->first);
	mp2.erase(3);
	if (mp2.begin() == mp2.end())
		v.push_back(1);
	std::map<int, int, std::plus<int> > mp3;
	fillMap(mp3);
	for (typename std::map<T, V>::iterator it = mp3.begin(); it != mp3.end(); it++) { v.push_back(it->first); }
	for (typename std::map<T, V>::iterator it = --mp3.end(); it != mp3.begin(); it--) { v.push_back(it->first); }
	std::map<int, int, std::minus<int> > mp4;
	fillMap(mp4);
	for (typename std::map<T, V>::iterator it = mp4.begin(); it != mp4.end(); it++) { v.push_back(it->first); }
	for (typename std::map<T, V>::iterator it = --mp4.end(); it != mp4.begin(); it--) { v.push_back(it->first); }
	std::map<int, int, std::greater_equal<int> > mp5;
	fillMap(mp5);
	for (typename std::map<T, V>::iterator it = mp5.begin(); it != mp5.end(); it++) { v.push_back(it->first); }
	for (typename std::map<T, V>::iterator it = --mp5.end(); it != mp5.begin(); it--) { v.push_back(it->first); }
	std::map<int, int, std::multiplies<int> > mp6;
	fillMap(mp6);
	for (typename std::map<T, V>::iterator it = mp6.begin(); it != mp6.end(); it++) { v.push_back(it->first); }
	for (typename std::map<T, V>::iterator it = --mp6.end(); it != mp6.begin(); it--) { v.push_back(it->first); }
	std::map<int, int, std::bit_xor<int> > mp7;
	fillMap(mp7);
	for (typename std::map<T, V>::iterator it = mp7.begin(); it != mp7.end(); it++) { v.push_back(it->first); }
	for (typename std::map<T, V>::iterator it = --mp7.end(); it != mp7.begin(); it--) { v.push_back(it->first); }
	std::map<int, int, std::logical_and<int> > mp8;
	fillMap(mp8);
	for (typename std::map<T, V>::iterator it = mp8.begin(); it != mp8.end(); it++) { v.push_back(it->first); }
	for (typename std::map<T, V>::iterator it = --mp8.end(); it != mp8.begin(); it--) { v.push_back(it->first); }
	g_start1 = timer();
	g_end1 = timer();
	v.push_back(mp1.size());
	return v;
}
*/

template <class T, class V>
std::vector<int> comparator_test(_map<T, V> mp) {
	std::vector<int> v;
	fillMap(mp);
	for (typename _map<T, V>::iterator it = mp.begin(); it != mp.end(); it++) { v.push_back(it->first); }
	for (typename _map<T, V>::iterator it = --mp.end(); it != mp.begin(); it--) { v.push_back(it->first); }
	_map<int, int, std::greater<int> > mp1;
	fillMap(mp1);
	v.push_back(mp1.begin()->first);
	mp1.erase(41);
	v.push_back(mp1.begin()->first);
	mp1.erase(29);
	v.push_back(mp1.begin()->first);
	_map<int, int, std::greater<int> > mp2;
	mp2.insert(_make_pair(3, 3));
	v.push_back(mp2.begin()->first);
	mp2.erase(3);
	if (mp2.begin() == mp2.end())
		v.push_back(1);
	_map<int, int, std::plus<int> > mp3;
	fillMap(mp3);
	for (typename _map<T, V>::iterator it = mp3.begin(); it != mp3.end(); it++) { v.push_back(it->first); }
	for (typename _map<T, V>::iterator it = --mp3.end(); it != mp3.begin(); it--) { v.push_back(it->first); }
	_map<int, int, std::minus<int> > mp4;
	fillMap(mp4);
	for (typename _map<T, V>::iterator it = mp4.begin(); it != mp4.end(); it++) { v.push_back(it->first); }
	for (typename _map<T, V>::iterator it = --mp4.end(); it != mp4.begin(); it--) { v.push_back(it->first); }
	_map<int, int, std::greater_equal<int> > mp5;
	fillMap(mp5);
	for (typename _map<T, V>::iterator it = mp5.begin(); it != mp5.end(); it++) { v.push_back(it->first); }
	for (typename _map<T, V>::iterator it = --mp5.end(); it != mp5.begin(); it--) { v.push_back(it->first); }
	_map<int, int, std::multiplies<int> > mp6;
	fillMap(mp6);
	for (typename _map<T, V>::iterator it = mp6.begin(); it != mp6.end(); it++) { v.push_back(it->first); }
	for (typename _map<T, V>::iterator it = --mp6.end(); it != mp6.begin(); it--) { v.push_back(it->first); }
	_map<int, int, std::bit_xor<int> > mp7;
	fillMap(mp7);
	for (typename _map<T, V>::iterator it = mp7.begin(); it != mp7.end(); it++) { v.push_back(it->first); }
	for (typename _map<T, V>::iterator it = --mp7.end(); it != mp7.begin(); it--) { v.push_back(it->first); }
	std::map<int, int, std::logical_and<int> > mp8;
	fillMap(mp8);
	for (typename std::map<T, V>::iterator it = mp8.begin(); it != mp8.end(); it++) { v.push_back(it->first); }
	for (typename std::map<T, V>::iterator it = --mp8.end(); it != mp8.begin(); it--) { v.push_back(it->first); }
	g_start1 = timer();
	g_end1 = timer();
	v.push_back(mp1.size());

	return v;
}

int main() {

	run_map_unit_test<int, int>("compare class", comparator_test, comparator_test);
	system("leaks ft_containers");
}
