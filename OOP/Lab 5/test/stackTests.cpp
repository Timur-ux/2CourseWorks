#include <gtest/gtest.h>
#include "allocator.hpp"
#include "stack.hpp"

class StackIteratorsTests : public ::testing::Test {
public:
	labWork::stack<std::string, labWork::Allocator<std::string>> stack;
	labWork::stack<const std::string, labWork::Allocator<const std::string>> constStack;
	std::vector<std::string> data = {
		"abcde",
		"",
		"Stack Overflow",
		"Nauchno-Tehnicheskiy Rэp",
		"ahalay-mahalay",
		"focus-pocus",
		"figli-migli",
		"Imperious, full of Crusiatous Avada Krakozabra"
	};

	void SetUp() {
		for (int i = data.size() - 1; i >= 0; --i) {
			stack.push(data[i]);
			constStack.push(data[i]);
		}
	}

	void TearDown() {

	}
};

TEST(StackTestsSet, pushTest) {
	labWork::stack<std::string, labWork::Allocator<std::string>> stack;
	const char * rawString = "abcde";
	std::string expectedString(rawString);

	std::string & returnedString = stack.push(rawString);

	ASSERT_EQ(expectedString, returnedString);
}

TEST(StackTestsSet, frontTest) {
	labWork::stack<std::string, labWork::Allocator<std::string>> stack;
	const char * rawString = "abcde";
	std::string expectedString(rawString);

	stack.push(rawString);

	std::string & returnedString = stack.front();

	ASSERT_EQ(expectedString, returnedString);
}

TEST(StackTestsSet, popTest) {
	labWork::stack<std::string, labWork::Allocator<std::string>> stack;
	const char * rawString1 = "abcde";
	const char * rawString2 = "abc123";
	std::string expectedString(rawString1);

	stack.push(rawString1);
	stack.push(rawString2);
	stack.pop();

	std::string & returnedString = stack.front();

	ASSERT_EQ(expectedString, returnedString);
}

TEST_F(StackIteratorsTests, iteratorTest) {
	int i = 0;
	for (auto it = std::begin(stack), last = std::end(stack)
		; it != last
		; ++it, ++i) {
		EXPECT_EQ(*it, data[i]);
	}
}

TEST_F(StackIteratorsTests, constIteratorTest) {
	int i = 0;
	for (auto it = std::begin(constStack), last = std::end(constStack)
		; it != last
		; ++it, ++i) {
		EXPECT_EQ(*it, data[i]);
	}
}