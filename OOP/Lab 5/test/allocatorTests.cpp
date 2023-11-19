#include <gtest/gtest.h>
#include <type_traits>

#include "allocator.hpp"

TEST(AllocatorTestSet, InnerTypesIsConvertible) {
	bool p2constP = std::is_convertible_v<labWork::Allocator<int>::pointer, labWork::Allocator<int>::const_pointer>;
	bool p2voidP = std::is_convertible_v<labWork::Allocator<int>::pointer, labWork::Allocator<int>::void_pointer>;
	bool p2constVoidP = std::is_convertible_v<labWork::Allocator<int>::pointer, labWork::Allocator<int>::const_void_pointer>;
	bool constP2constVoidP = std::is_convertible_v<labWork::Allocator<int>::const_pointer, labWork::Allocator<int>::const_void_pointer>;
	bool voidP2constVoidP = std::is_convertible_v<labWork::Allocator<int>::void_pointer, labWork::Allocator<int>::const_void_pointer>;

	ASSERT_TRUE(
		   p2constP
		&& p2voidP
		&& p2constVoidP
		&& constP2constVoidP
		&& voidP2constVoidP
	);
}

TEST(AllocatorTestSet, allocateTest) {
	labWork::Allocator<int, 2> allocator;

	int * pint = allocator.allocate(1);

	EXPECT_NE(pint, nullptr);
	EXPECT_THROW(allocator.allocate(1000), std::bad_alloc);

	allocator.deallocate(pint);
}