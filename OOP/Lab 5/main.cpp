#include <iostream>
#include <malloc.h>

int main() {

	int a = 5;
	int & b = a;

	std::cout << &a << ' ' << &b << std::endl;
	return 0;
}