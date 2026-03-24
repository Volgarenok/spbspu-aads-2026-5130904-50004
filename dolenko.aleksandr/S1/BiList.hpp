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


	BiList() noexcept = default;
	BiList(const BiList& other);
	BiList(BiList&& other) noexcept:
		head_(other.head_),
		tail_(other.tail_),
		size_(other.size_)
	{
		other.head_ = nullptr;
		other.tail_ = nullptr;
		other.size_ = 0;
	}
	~BiList() noexcept
	{
		clear();
	}

	BiList& operator=(const BiList& other);
	BiList& operator=(BiList&& other) noexcept
	{
		if (this == &other)
		{
			return *this;
		}
		clear();
		head_ = other.head_;
		tail_ = other.tail_;
		size_ = other.size_;
		other.head_ = nullptr;
		other.tail_ = nullptr;
		other.size_ = 0;
		return *this;
	}

	
	bool empty() const noexcept;
	std::size_t size() const noexcept;

	
	void push_front(const T& value)
	{
		Node< T >* node = create_node(value);
		if (!head_)
		{
			head_ = node;
			tail_ = node;
			size_ = 1;
			return;
		}
		node->next = head_;
		head_->prev = node;
		head_ = node;
		++size_;
	}
	void push_back(const T& value)
	{
		Node< T >* node = create_node(value);
		if (!tail_)
		{
			head_ = node;
			tail_ = node;
			size_ = 1;
			return;
		}
		node->prev = tail_;
		tail_->next = node;
		tail_ = node;
		++size_;
	}
	void pop_front() noexcept
	{
		if (!head_)
		{
			return;
		}
		Node< T >* old_head = head_;
		Node< T >* new_head = old_head->next;
		if (new_head)
		{
			new_head->prev = nullptr;
		}
		head_ = new_head;
		if (tail_ == old_head)
		{
			tail_ = new_head;
		}
		destroy_node(old_head);
		--size_;
	}
	void pop_back() noexcept
	{
		if (!tail_)
		{
			return;
		}
		Node< T >* old_tail = tail_;
		Node< T >* new_tail = old_tail->prev;
		if (new_tail)
		{
			new_tail->next = nullptr;
		}
		tail_ = new_tail;
		if (head_ == old_tail)
		{
			head_ = new_tail;
		}
		destroy_node(old_tail);
		--size_;
	}
	void clear() noexcept
	{
		while (head_)
		{
			pop_front();
		}
	}

private:
	
	Node< T >* create_node(const T& value)
	{
		return new Node< T >(value, nullptr, nullptr);
	}
	void destroy_node(Node< T >* node) noexcept
	{
		delete node;
	}
};

}

#endif

