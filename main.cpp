#include "bounded_int.h"
#include <iostream>

int main() {
	bounded_int<1, 10> a = 5;
	bounded_int<2, 15> b = 7;
	auto c = a + b;	//bounded_int<3, 25, int>
	try {
		a = c;
	}
	catch (const std::exception & f) {
		std::cout << f.what();
	}
	

}

