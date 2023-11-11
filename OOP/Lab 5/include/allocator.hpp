#ifndef MY_ALLOCATOR_H_
#define MY_ALLOCATOR_H_

#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <type_traits>

namespace labWork {
	template <typename T, int BLOCKS_COUNT = 100>
	class Allocator {
	private:
		void * allocatorMemory;
		std::vector <T *> freeBlocks;
		std::size_t freeCount;
	public:
		using pointer = T *;
		using const_pointer = const T *;
		using void_pointer = void *;
		using const_void_pointer = const void *;

		using value_type = T;
		using reference_type = T &;
		using const_reference_type = const T &;

		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;

		template <typename U>
		struct rebind {
			using other = Allocator<U>;
		};

		Allocator() {
			allocatorMemory = malloc(sizeof(T) * BLOCKS_COUNT);

			for (int i = 0; i < BLOCKS_COUNT; ++i) {
				freeBlocks.push_back(static_cast<T *>(allocatorMemory + i * sizeof(T)));
			}

			freeCount = BLOCKS_COUNT;
		}

		~Allocator() {
			if (freeCount < BLOCKS_COUNT) {
				std::cerr << "WARNING: not all objects was deallocated when allocator's dectructor was called" << std::endl;
			}

			free(allocatorMemory);
		}

		pointer allocate(size_type n = 1) {
			pointer result = nullptr;
			if (freeCount >= n) {
				auto lastFree = --std::end(freeBlocks);

				result = *lastFree;

				freeBlocks.erase(lastFree);
				--freeCount;
			}
			else {
				throw std::bad_alloc();
			}

			return result;
		}

		void deallocate(pointer p, size_type n = 1) noexcept {
			freeBlocks.push_back(p);
			++freeCount;
		}

		template<typename U, typename... Args>
		void construct(U * p, Args && ...args) {
			if (not(p >= allocatorMemory and p < allocatorMemory + BLOCKS_COUNT * sizeof(T))) {
				throw std::invalid_argument("Allocator::construct error: given pointer must point on allocator memory");
			}

			new ((void *)p) T(std::forward<Args>(args)...);
		}

		void destroy(pointer p) {
			p->~T();
		}
	};

	template <typename T, typename U>
	constexpr bool operator==(Allocator<T> & lhs, Allocator<U> & rhs) {
		return &lhs == &rhs;
	}

	template <typename T, typename U>
	constexpr bool operator!=(Allocator<T> & lhs, Allocator<U> & rhs) {
		return not(lhs == rhs);
	}


} // namespace myAlloc


#endif