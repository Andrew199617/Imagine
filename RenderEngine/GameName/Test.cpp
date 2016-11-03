#include "Test.h"
#include <iostream>

Test::~Test()
{
}

void Test::Update(float)
{
	std::cout << "Hello from dll" << std::endl;
}
