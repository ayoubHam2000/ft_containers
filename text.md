**std::allocator::allocate**
pointer allocate (size_type n, allocator<void>::const_pointer hint=0);

Allocate block of storage
Attempts to allocate a block of storage with a size large enough to contain n elements of member type value_type (an alias of the allocator's template parameter), and returns a pointer to the first element.

The storage is aligned appropriately for objects of type value_type, but they are not constructed.


**std::allocator::construct**

Constructs an element object on the location pointed by p.

Notice that this does not allocate space for the element. It should already be available at p (see member allocate to allocate space).


**std::allocator::deallocate**
Release block of storage

Releases a block of storage previously allocated with member allocate and not yet released.

The elements in the array are not destroyed by a call to this member function.

In the default allocator, the block of storage is at some point deallocated using ::operator delete (either during the function call, or later).


*Info*
https://stackoverflow.com/questions/47783379/calling-allocator-traitsdeallocate-on-a-null-pointer
std::allocator<T>::deallocate() 
does not accept null points. It would be surprising 
if the allocator concept allows passing null pointers 
as std::allocator<T> wouldn't model that concept.



1. null on deallocate
2. read from inputstream
3. speed
4. leaks
5. destroy and construct
6. assignment, copy, construction