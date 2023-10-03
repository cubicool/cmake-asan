#include <iostream>

void testLeak() {
	auto* leak = new char[128]{0};

	std::cout << "Going to leak 128 bytes inside testlib: " << static_cast<void*>(leak) << std::endl;
}
