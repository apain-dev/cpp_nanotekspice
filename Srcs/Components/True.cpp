//
// Created by yamino on 03/03/18.
//

#include "../../Inc/True.hpp"
#include "../../Inc/Error.hpp"

True::True() : _other(nullptr), _value(nts::TRUE)
{
}

void True::dump() const
{
	std::cout << "I am a true component so my value is always true" << std::endl;
}

nts::Tristate True::compute(size_t pin)
{
	if (pin != 1)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type Input."));
	return (_value);
}

nts::Pin True::getPin(size_t pin)
{
	if (pin != 1)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type Input."));
	return (nts::IN);
}

void True::setLink(std::size_t pin, nts::IComponent &oth, std::size_t othPin)
{
	if (pin != 1)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type Input."));
	if (_other != nullptr)
		throw (NanoException("The pin " + std::to_string(pin) + " is already connected to another pin."));
	_other = &oth;
	_links = std::pair<std::size_t, std::size_t>(pin, othPin);
}