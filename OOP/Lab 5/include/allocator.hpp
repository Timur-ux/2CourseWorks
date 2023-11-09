#ifndef MY_ALLOCATOR_H_
#define MY_ALLOCATOR_H_

#include <vector>
#include <malloc.h>

namespace myAlloc {
	template <typename T, int BLOCKS_COUNT = 100>
	class Allocator {
	private:
		void * usedBlocks;
		vector <void *> freeBlocks;
		size_type freeCount;
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
			usedBlocks = malloc(sizeof(T) * BLOCKS_COUNT);

			for (int i = 0; i < BLOCKS_COUNT; ++i) {
				freeBlocks[i] = usedBlocks + i * sizeof(T);
			}

			freeCount = BLOCKS_COUNT;
		}

		~Allocator() {
			if (freeCount < BLOCKS_COUNT) {
				std::cerr << "WARNING: not all objects was deallocated when allocator's dectructor was called" << std::endl;
			}

			delete usedBlocks;
		}

		pointer allocate(size_type n) {

		}

		void deallocate(pointer p, size_type n) {

		}
	};
} // namespace myAlloc


#endif