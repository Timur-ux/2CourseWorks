#ifndef STACK_H_
#define STACK_H_

#include <vector>
#include <stdexcept>

namespace labWork {

	template <typename T, class Allocator = std::allocator<T>>
	class stack {
	private:
		Allocator allocator;
		std::vector<T *> data;
	public:
		stack() = default;
		~stack();

		template <typename... Args>
		T & push(Args && ...args);
		T & front();
		void pop();

		bool empty();

		class iterator {
		public:
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T *;
			using reference = T &;
			using iterator_categoty = std::forward_iterator_tag;
		private:
			pointer ptr;
		public:
			iterator() = default;
			iterator(pointer _ptr) : ptr(_ptr) {}
			iterator(iterator & other) : ptr(other.ptr) {}
			iterator(iterator && other) : ptr(other.ptr) {}

			iterator & operator=(iterator & other) : ptr(other.ptr) {}
			iterator & operator==(iterator && other) : ptr(other.ptr) {}

			reference operator*() {
				return *ptr;
			}

			pointer operator->() {
				return ptr;
			}

			iterator & operator++() {
				++ptr;
				return *this;
			}

			iterator operator++(int) {
				iterator temp(*this);
				++ptr;
				return temp;
			}

			friend bool operator==(iterator & lhs, iterator & rhs) {
				return lhs.ptr == rhs.ptr;
			}

			friend bool operator!=(iterator & lhs, iterator & rhs) {
				return not(lhs == rhs);
			}

		}
	};


	template<typename T, class Allocator>
	inline stack<T, Allocator>::~stack() {
		while (not(empty())) {
			pop();
		}
	}

	template<typename T, class Allocator>
	template<typename ...Args>
	inline T & stack<T, Allocator>::push(Args && ...args) {
		T * ptr = allocator.allocate(1);
		allocator.construct(ptr, args...);

		data.push_back(ptr);
		return *ptr;
	}

	template<typename T, class Allocator>
	inline T & stack<T, Allocator>::front() {
		if (empty()) {
			throw std::logic_error("Stack::front error: stack is empty, nothing to pop");
		}

		return *data[data.size() - 1];
	}

	template<typename T, class Allocator>
	inline void stack<T, Allocator>::pop() {
		if (empty()) {
			throw std::logic_error("Stack::pop error: stack is empty, nothing to pop");
		}

		T * frontElement = &front();

		allocator.destroy(frontElement);
		allocator.deallocate(frontElement);

		data.pop_back();
	}

	template<typename T, class Allocator>
	inline bool stack<T, Allocator>::empty() {
		return data.size() == 0;
	}

} // namespace labWork

#endif