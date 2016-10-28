#include "Test.h"
#include <iostream>

Test::~Test()
{
}

bool Test::Update(float)
{
	std::cout << "Hello from dll" << std::endl;
	return true;
}
