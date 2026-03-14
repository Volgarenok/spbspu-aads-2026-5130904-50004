#ifndef DELETE_LIST
#define DELETE_LIST

#include "CLIter.hpp"
#include "LIter.hpp"
#include "List.hpp"

template<class T>
void delete_LL(CLIter<T> iter);

template<class T>
void delete_List(CLIter<T> iter, List<T> * fake);

template<class T>
void delete_List(LIter<T> iter, List<T> * fake);

#endif
