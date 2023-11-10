#include <gtest/gtest.h>
#include "allocator.hpp"
#include "stack.hpp"

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

	stack.push(std::string(rawString1));
	stack.push(rawString2);
	stack.pop();

	std::string & returnedString = stack.front();

	ASSERT_EQ(expectedString, returnedString);
}