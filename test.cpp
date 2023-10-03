//vimrun! ./test

#include "testlib.hpp"

#include <iostream>

int main(int argc, char** argv) {
	auto* leak = new char[256]{0};

	std::cout << "Going to leak address: " << static_cast<void*>(leak) << std::endl;

	testLeak();

	return 0;
}
