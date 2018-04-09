//
// Created by yamino on 01/03/18.
//

#include "../../Inc/Input.hpp"
#include "../../Inc/Error.hpp"

Input::Input() : _other(nullptr), _value(nts::UNDEFINED), _isClock(false)
{
}

void Input::setValue(nts::Tristate val)
{
	_value = val;
}

void Input::dump() const
{
	std::cout << "I am an input and my value is " << (_value == nts::TRUE ? "true" : _value == nts::FALSE ? "false" : "undefined") << std::endl;
}

nts::Tristate Input::compute(size_t pin)
{
	if (pin != 1)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type Input."));
	return (_value);
}

nts::Pin Input::getPin(size_t pin)
{
	if (pin != 1)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type Input."));
	return (nts::IN);
}

void Input::setLink(std::size_t pin, nts::IComponent &oth, std::size_t othPin)
{
	if (pin != 1)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type Input."));
	if (_other != nullptr)
		throw (NanoException("The pin " + std::to_string(pin) + " is already connected to another pin."));
	_other = &oth;
	_links = std::pair<std::size_t, std::size_t>(pin, othPin);
}

void Input::setClock()
{
	_isClock = true;
}

bool Input::getClock()
{
	return (_isClock);
}