//
// Created by yamino on 03/03/18.
//

#include "../../Inc/False.hpp"
#include "../../Inc/Error.hpp"

False::False() : _other(nullptr), _value(nts::FALSE)
{
}

void False::dump() const
{
	std::cout << "I am a false component so my value is always false" << std::endl;
}

nts::Tristate False::compute(size_t pin)
{
	if (pin != 1)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type Input."));
	return (_value);
}

nts::Pin False::getPin(size_t pin)
{
	if (pin != 1)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type Input."));
	return (nts::IN);
}

void False::setLink(std::size_t pin, nts::IComponent &oth, std::size_t othPin)
{
	if (pin != 1)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type Input."));
	if (_other != nullptr)
		throw (NanoException("The pin " + std::to_string(pin) + " is already connected to another pin."));
	_other = &oth;
	_links = std::pair<std::size_t, std::size_t>(pin, othPin);
}