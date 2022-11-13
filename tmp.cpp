/*******************************************/
/*     created by aben-ham 11/11/22         */
/*******************************************/

//from vector
void _add_space(size_type pos, size_type nb_shift){
	size_type capacity = capacity();
	size_type size = size();
	size_type new_capacity = __get_new_capacity(capacity + nb_shift);
	pointer new_arr = _alloc.allocate(new_capacity, _first);

	//copy and shift
	pointer new_tmp = new_arr;
	pointer old_tmp = _first;
	while (--pos){
		_alloc.construct(new_tmp, *old_tmp);
		_alloc.destroy(old_tmp);
		new_tmp++;
		old_tmp++;
	}
	new_tmp += nb_shift;
	while (old_tmp != _last){
		_alloc.construct(new_tmp, *old_tmp);
		_alloc.destroy(old_tmp);
		new_tmp++;
		old_tmp++;
	}

	//deallocate and set new member's values
	_alloc.deallocate(_first, capacity);
	_first = new_arr;
	_last = new_arr + size + nb_shift;
	_last_max = new_arr + new_capacity;
}
