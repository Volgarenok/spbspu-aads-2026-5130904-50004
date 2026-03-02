#ifndef LIST_H
#define LIST_H

template <class T> class List;

template <class T>
class LIter {
  friend class List<T>;
  List<T>* that;


};

template <class T>
class LCIter {
  friend class List<T>;
  List<T>* that;
};

template <class T>
class List {
  T data;
  List<T>* next = nullptr;
};
#endif
