#include <gtest/gtest.h>
#include <type_traits>

#include "allocator.hpp"

TEST(AllocatorTestSet, InnerTypesIsConvertible) {
	bool p2constP = std::is_convertible_v<myAlloc::Allocator<int>::pointer, myAlloc::Allocator<int>::const_pointer>;
	bool p2voidP = std::is_convertible_v<myAlloc::Allocator<int>::pointer, myAlloc::Allocator<int>::void_pointer>;
	bool p2constVoidP = std::is_convertible_v<myAlloc::Allocator<int>::pointer, myAlloc::Allocator<int>::const_void_pointer>;
	bool constP2constVoidP = std::is_convertible_v<myAlloc::Allocator<int>::const_pointer, myAlloc::Allocator<int>::const_void_pointer>;
	bool voidP2constVoidP = std::is_convertible_v<myAlloc::Allocator<int>::void_pointer, myAlloc::Allocator<int>::const_void_pointer>;

	ASSERT_TRUE(
		   p2constP
		&& p2voidP
		&& p2constVoidP
		&& constP2constVoidP
		&& voidP2constVoidP
	);
}