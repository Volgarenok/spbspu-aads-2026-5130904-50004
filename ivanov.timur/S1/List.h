#ifndef LIST_H
#define LIST_H

template <class T>
class Iter {
  struct List {
    T data_;
    List* next_;
  };

  List* data_;
  explicit Iter(List<T>* data): data_(data) {}

  T pull() {
    return data_->data_;
  }

  Iter getIterByPos(size_t pos) {

  }

  Iter getLast() {
    while (hasNext)
  }

  void push(T data) {
    data_->next_ = new List(data, data_->next_);
  }
  bool hasNext() {
    return data_->next_ != nullptr;
  }


};

//template <class T>
//class LIter : public Iter<T> {
//};
//template <class T>
//class LCIter : public Iter<T>{
//};

#endif
