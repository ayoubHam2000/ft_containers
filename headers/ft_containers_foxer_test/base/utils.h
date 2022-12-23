//
// Created by aben-ham on 12/22/22.
//

#ifndef FT_CONTAINERS_UTILS_H
#define FT_CONTAINERS_UTILS_H


template <typename container1, typename container2>
bool compareContainers(container1& c1, container2& c2)
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

time_t get_time(void);

#endif //FT_CONTAINERS_UTILS_H
