#ifndef BILIST_HPP
#define BILIST_HPP

#include <cstddef>

template<class T>
class BiList {
private:
	struct Node {
		T data;
		Node* prev = nullptr;
		Node* next = nullptr;
			Node(const T& v) : data(v) {}
	};

	Node* head_ = nullptr;
	Node* tail_ = nullptr;
	std::size_t size_ = 0;

public:


	BiList() noexcept;
	BiList(const BiList& other);
	BiList(BiList&& other) noexcept;
	~BiList();

	BiList& operator=(const BiList& other);
	BiList& operator=(BiList&& other) noexcept;

	
	bool empty() const noexcept;
	size_type size() const noexcept;

	
	void push_front(const T& value);
	void push_back(const T& value);
	void pop_front();
	void pop_back();
	void clear() noexcept;

private:
	
	Node* create_node(const T& value);
	void destroy_node(Node* node) noexcept;
};

#endif 

