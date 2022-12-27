//
// Created by aben-ham on 12/22/22.
//

#include "statistic_tracker.h"

statistic_tracker::statistic_tracker(){
    reset();
}

statistic_tracker::statistic_tracker(const statistic_tracker& other){
    this->nb_allocation = other.nb_allocation;
    this->nb_deallocate = other.nb_deallocate;
    this->nb_construct = other.nb_construct;
    this->nb_bad_construct = other.nb_bad_construct;
    this->nb_destruct = other.nb_destruct;
    this->nb_bad_destruct = other.nb_bad_destruct;
    this->nb_bad_deallocate = other.nb_bad_deallocate;
}

statistic_tracker& statistic_tracker::operator=(const statistic_tracker& other){
    this->nb_allocation = other.nb_allocation;
    this->nb_deallocate = other.nb_deallocate;
    this->nb_construct = other.nb_construct;
    this->nb_bad_construct = other.nb_bad_construct;
    this->nb_destruct = other.nb_destruct;
    this->nb_bad_destruct = other.nb_bad_destruct;
    this->nb_bad_deallocate = other.nb_bad_deallocate;
    return (*this);
}

statistic_tracker::~statistic_tracker(){}

void statistic_tracker::reset(){
    nb_allocation = 0;
    nb_deallocate = 0;
    nb_construct = 0;
    nb_bad_construct = 0;
    nb_destruct = 0;
    nb_bad_destruct = 0;
    nb_bad_deallocate = 0;
}

void statistic_tracker::print(){
    std::cout << "nb_allocation: " << nb_allocation << std::endl;
    std::cout << "nb_deallocate: " << nb_deallocate << std::endl;
    std::cout << "nb_construct: " << nb_construct << std::endl;
	std::cout << "nb_destruct: " << nb_destruct << std::endl;
	std::cout << "nb_bad_construct: " << nb_bad_construct << std::endl;
    std::cout << "nb_bad_destruct: " << nb_bad_destruct << std::endl;
    std::cout << "nb_bad_deallocate: " << nb_bad_deallocate << std::endl;
}
