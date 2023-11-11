#ifndef STACK_H_
#define STACK_H_

#include <stdexcept>
#include <vector>
#include <type_traits>

namespace labWork {

	template <typename T, class Allocator = std::allocator<T>, int BLOCK_COUNT = 100>
	class stack {
	private:
		Allocator allocator;
		T * data[BLOCK_COUNT];
		int size = 0;
	public:
		using value_type = T;
		using reference = T &;
		using pointer = T *;

		stack() = default;
		~stack();

		template <typename... Args>
		reference push(Args && ...args);
		reference front();
		void pop();

		bool empty();

		template <typename U>
		class StackIterator;

		using iterator = StackIterator<T>;
		using const_iterator = StackIterator<const T>;

		template <typename U>
		class StackIterator {
		public:
			using difference_type = std::ptrdiff_t;
			using value_type = U;
			using pointer = U *;
			using reference = U &;
			using iterator_categoty = std::forward_iterator_tag;
		protected:
			pointer ptr;
		public:
			StackIterator() = default;
			StackIterator(pointer _ptr) : ptr(_ptr) {}
			StackIterator(StackIterator & other) : ptr(other.ptr) {}
			StackIterator(StackIterator && other) noexcept : ptr(other.ptr) {
				other.ptr = nullptr;
			}

			StackIterator & operator=(StackIterator & other) {
				ptr = other.ptr;

				return *this;
			}
			StackIterator & operator=(StackIterator && other) noexcept {
				ptr = other.ptr;
				other.ptr = nullptr;

				return *this;
			}

			reference operator*() {
				return *ptr;
			}

			pointer operator->() {
				return ptr;
			}

			StackIterator & operator++() {
				++ptr;
				return *this;
			}

			StackIterator operator++(int) {
				StackIterator temp(*this);
				++ptr;

				return temp;
			}

			StackIterator & operator+=(const difference_type offset) {
				ptr += offset;
				return *this;
			}

			StackIterator operator+(const difference_type offset) {
				StackIterator tmp(*this);
				return tmp += offset;
			}

			friend bool operator>(StackIterator<U> & lhs, StackIterator<U> & rhs) {
				return lhs.ptr > rhs.ptr;
			}

			friend bool operator>=(StackIterator<U> & lhs, StackIterator<U> & rhs) {
				return lhs.ptr >= rhs.ptr;
			}

			friend bool operator<(StackIterator<U> & lhs, StackIterator<U> & rhs) {
				return lhs.ptr < rhs.ptr;
			}

			friend bool operator<=(StackIterator<U> & lhs, StackIterator<U> & rhs) {
				return lhs.ptr <= rhs.ptr;
			}

			friend bool operator==(StackIterator<U> & lhs, StackIterator<U> & rhs) {
				return lhs.ptr == rhs.ptr;
			}

			friend bool operator!=(StackIterator<U> & lhs, StackIterator<U> & rhs) {
				return not(lhs == rhs);
			}

		}; // class StackIterator

		iterator begin() {
			return iterator(&front());
		}

		iterator end() {
			T * ptr = data[0];
			return ++iterator(ptr);
		}

		const_iterator begin() const {
			return const_iterator(&front());
		}

		const_iterator end() const {
			const T * ptr = data[0];
			return ++const_iterator(ptr);
		}

		const_iterator cbegin() {
			return const_iterator(&front());
		}

		const_iterator cend() {
			const T * ptr = data[0];
			return ++const_iterator(ptr);
		}

	}; // class stack

	template<typename T, class Allocator, int BLOCK_COUNT>
	inline stack<T, Allocator, BLOCK_COUNT>::~stack() {
		while (not(empty())) {
			pop();
		}
	}

	template<typename T, class Allocator, int BLOCK_COUNT>
	template<typename ...Args>
	inline T & stack<T, Allocator, BLOCK_COUNT>::push(Args && ...args) {
		if (size >= BLOCK_COUNT) {
			throw std::runtime_error("Error: Stack overflow");
		}

		T * ptr = allocator.allocate();
		allocator.construct(ptr, args...);


		data[size++] = ptr;
		return *ptr;
	}

	template<typename T, class Allocator, int BLOCK_COUNT>
	inline T & stack<T, Allocator, BLOCK_COUNT>::front() {
		if (empty()) {
			throw std::logic_error("Stack::front error: stack is empty, nothing to pop");
		}

		return *data[size - 1];
	}

	template<typename T, class Allocator, int BLOCK_COUNT>
	inline void stack<T, Allocator, BLOCK_COUNT>::pop() {
		if (empty()) {
			throw std::logic_error("Stack::pop error: stack is empty, nothing to pop");
		}

		T & frontElement = front();

		allocator.destroy(&frontElement);
		allocator.deallocate(&frontElement);

		--size;
	}

	template<typename T, class Allocator, int BLOCK_COUNT>
	inline bool stack<T, Allocator, BLOCK_COUNT>::empty() {
		return size == 0;
	}

} // namespace labWork

#endif