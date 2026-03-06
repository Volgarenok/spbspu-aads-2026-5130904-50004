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
    Iter tmp = Iter(new List(data_->data_, data_->next_));
    if (tmp.data_ == nullptr) throw std::logic_error("empty list");
    for (size_t i = 0; i < pos; ++i) {
      if (!tmp.hasNext()) throw std::logic_error("no such element in list");
      tmp.next();
    }
    return tmp;
  }

  Iter getLast() {
    Iter tmp = Iter(new List(data_->data_, data_->next_));
    while (tmp.hasNext()) tmp.next();
    return tmp;
  }

  void push(T data) {
    data_->next_ = new List(data, data_->next_);
  }
  bool hasNext() {
    return data_->next_ != nullptr;
  }
  void next() {
    data_ = data_->next_;
  }


};

//template <class T>
//class LIter : public Iter<T> {
//};
//template <class T>
//class LCIter : public Iter<T>{
//};

#endif
