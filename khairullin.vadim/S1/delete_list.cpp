#include "delete_list.hpp"

template<class T>
void delete_LL(CLIter<T> iter)
{
  iter = iter.list->cut_fake(iter.list);
  while(iter.not_empty())
  {
    iter.value() = iter.value()->cut_fake(iter.value());
    if (iter.value())
    {
      iter.value()->clear(iter.value());
    }
    iter = iter.list->cut(iter.list);
  }
}

template<class T>
void delete_List(CLIter<T> iter, List<T> * fake)
{
  iter = iter.begin(fake);
  iter = iter.list->cut_fake(fake);
  if (iter.list)
  {
    iter.list->clear(iter.list);
  }
}

template<class T>
void delete_List(LIter<T> iter, List<T> * fake)
{
  iter = iter.begin(fake);
  iter = iter.list->cut_fake(fake);
  if (iter.list)
  {
    iter.list->clear(iter.list);
  }
}
