//
// Created by arthur on 2/26/18.
//

#include <stdexcept>
#include <iostream>
#include "actionner.hpp"

bool exit(std::string str)
{
	(void)(str);
	exit(0);
}

bool sayHello(std::string str)
{
	std::cout << "Coucou" << std::endl;
	return true;
}