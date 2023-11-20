#include <gtest/gtest.h>

auto main(int argc, char * argw[]) -> int {
	testing::InitGoogleTest(&argc, argw);
	return RUN_ALL_TESTS();
}