#include <iostream>
#include <vector>

int main() {
	std::vector<int *> v;
	for (int i = 0; i < 5; ++i) {
		int * temp = new int{ i };
		v.emplace_back(temp);
	}

	int * temp = v[0];

	for (int * i : v) {
		std::cout << *i << ' ';
	}
	std::cout << std::endl << *temp << ' ';
	++temp;
	std::cout << *temp;

	return 0;
}