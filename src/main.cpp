#include "lib.h"
#include <iostream>
namespace {
	constexpr int a = 1;
	constexpr int b = 2;
}

int main() {
	static_assert(lib::Add(a, b) == 3);

	std::cout << "🎉 Hoera! Je hebt succesvol een C++ programma gecompileerd!\n";
	return 0;
}

