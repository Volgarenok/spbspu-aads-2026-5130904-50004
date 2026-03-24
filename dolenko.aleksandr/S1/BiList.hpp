#ifndef BILIST_HPP
#define BILIST_HPP

#include <cstddef>
#include "Node.hpp"

namespace dolenko
{

template<class T>
class BiList {
private:
	Node< T >* head_ = nullptr;
	Node< T >* tail_ = nullptr;
	std::size_t size_ = 0;

public:


	BiList() noexcept;
	BiList(const BiList& other);
	BiList(BiList&& other) noexcept;
	~BiList();

	BiList& operator=(const BiList& other);
	BiList& operator=(BiList&& other) noexcept;

	
	bool empty() const noexcept;
	std::size_t size() const noexcept;

	
	void push_front(const T& value);
	void push_back(const T& value);
	void pop_front();
	void pop_back();
	void clear() noexcept;

private:
	
	Node< T >* create_node(const T& value)
	{
		// Strong exception safety: if construction throws, no node is created.
		return new Node< T >(value, nullptr, nullptr);
	}
	void destroy_node(Node< T >* node) noexcept
	{
		delete node;
	}
};

}

#endif

