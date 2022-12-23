//
// Created by aben-ham on 12/22/22.
//

#ifndef FT_CONTAINERS_STATISTIC_TRACKER_H
#define FT_CONTAINERS_STATISTIC_TRACKER_H

#include <iostream>

struct statistic_tracker{
    size_t	nb_allocation;
    size_t 	nb_deallocate;
    size_t	nb_construct;
    size_t 	nb_bad_construct;//Called construct on null Or Called construct on initialized memory
    size_t 	nb_destruct;
    size_t 	nb_bad_destruct;//Called destroy on null Or Called destroy on uninitialized memory
    size_t 	nb_bad_size;
    size_t 	nb_bad_deallocate;//deallocate on unconstructed memory region or deallocate a null pointer


    statistic_tracker();

    statistic_tracker(const statistic_tracker& other);

    statistic_tracker& operator=(const statistic_tracker& other);

    ~statistic_tracker();

    void reset();

    void print();
};


#endif //FT_CONTAINERS_STATISTIC_TRACKER_H
