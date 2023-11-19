#include <iostream>
#include <map>

#include "stack.hpp"
#include "allocator.hpp"

using myMap = std::map<int, int, std::less<int>, labWork::Allocator<std::pair<const int, int>>>;
using myStack = labWork::stack<std::pair<int, int>, labWork::Allocator<std::pair<int, int>>>;


unsigned long long int factorial(int n) {
	if (n > 0) {
		return n * factorial(n - 1);
	}
	return 1;
}

int main() {
	std::cout << "Map with custom allocator" << std::endl;

	myMap map;
	for (int i = 0; i < 10; ++i) {
		map[i] = factorial(i);
	}

	for (auto & element : map) {
		std::cout << element.first << ' ' << element.second << std::endl;
	}

	std::cout << "Custom stack with custom allocator" << std::endl;

	myStack stack;
	for (int i = 0; i < 10; ++i) {
		stack.push(std::make_pair(i, factorial(i)));
	}

	for (auto & element : stack) {
		std::cout << element.first << ' ' << element.second << std::endl;
	}

	return 0;
}