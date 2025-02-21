#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN // This tells Doctest to provide a main() - only do this in one cpp file
#include "doctest/doctest.h"
#include "lib.h"
#include <string>
#include <iostream>

TEST_CASE("Library Add"){
	for(std::size_t i = 0; i < 10; ++i) {
		REQUIRE(lib::Add(i, i*2) == i*3);
	}
}

/* 
	Hoewel onderstaande testen (meestal) slagen, bevatten ze programmeerfouten omdat
	ze geheugen aanspreken waar dat eigenlijk niet mag: voorbij het einde van de lijst, etc.

	Er bestaan 'Sanitizers' om veelvoorkomende programmeerfouten zoals deze op te sporen
	en sneller aan het licht te brengen. (cfr. https://github.com/google/sanitizers)

	De *Address Sanitizer* (ASan) helpt programmeerfouten zoals 'use after free', 'memory leaks',
	'buffer overflow' edm. op te sporen. Deze kan worden geactiveerd door `g++` op te roepen met de 
	parameter `-fsanitize=address`. 

	Ga naar CMakeLists.txt (niet test/CMakeLists.txt) en haal de regel uit commentaar die deze 
	parameter toevoegt wanneer g++ wordt opgeroepen.

*/

TEST_CASE("One off error"){

	int a[2] = {0,1};
	int b = a[2];

	REQUIRE(b != 0);
}

TEST_CASE("Use after free"){

	int* array = new int[5]{1,2,3,4,5};
	REQUIRE(array[2] == 3);
	delete[] array;

	REQUIRE(array[4] == 5); // BOOM!

}
