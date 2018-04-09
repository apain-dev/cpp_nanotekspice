//
// Created by yamino on 01/03/18.
//

#include "../../Inc/Output.hpp"
#include "../../Inc/Error.hpp"

Output::Output() : _other(nullptr), _value(nts::UNDEFINED)
{
}

void Output::dump() const
{
	std::cout << "I am an output and my value is " << (_value == nts::TRUE ? "true" : _value == nts::FALSE ? "false" : "undefined") << std::endl;
}

nts::Tristate Output::compute(std::size_t pin)
{
	if (pin != 1)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type Output."));
	this->_value = this->_other->compute(_links.second);
	return (_value);
}

nts::Pin Output::getPin(std::size_t pin)
{
	if (pin != 1)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type Output."));
	return (nts::OUT);
}

void Output::setLink(std::size_t pin, nts::IComponent &oth, std::size_t othPin)
{
	if (pin != 1)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type Output."));
	if (_other != nullptr)
		throw (NanoException("The pin " + std::to_string(pin) + " is already connected to another pin."));
	_other = &oth;
	_links = std::pair<std::size_t, std::size_t>(pin, othPin);
}

bool Output::isLinked()
{
	bool res = false;

	if (_other != nullptr)
		res = true;
	return (res);
}

char Output::getValue() const
{
	char res = 'U';

	if (_value == nts::TRUE)
		res = '1';
	if (_value == nts::FALSE)
		res = '0';
	return (res);
}