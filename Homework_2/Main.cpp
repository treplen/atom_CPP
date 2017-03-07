#include <iostream>
#include "Array.h"

int main()
{
	Array a(20);
	for (int i = 0; i < 20; i++)
		a[i] = i;
	for (int i = 0; i < 20; i++)
		std::cout << a[i] << std::endl;
	std::cout << std::endl;
	std::cout << *(a + 3);
	_getwch();

	return 0;
}