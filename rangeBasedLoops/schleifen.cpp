#include <iostream>
#include "rangeBasedClass.cpp"

int main (int argc, char* argv[]) {
	//int i = 0;
	//while (i <= 100) {
	//	std::cout << i << std::endl;
	//	++i;
	//}

	// int i = 1;
	// do {
	// 	std::cout << i << std::endl;
	// 	i++;
	// } while (i <= 100);


	RangeBasedForClass range{0, 20};
	
	for (auto member : range){
		cout << member+1 << endl;
	}

}