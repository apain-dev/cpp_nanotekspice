//
// Created by yamino on 04/03/18.
//

#include "../../Inc/Comp4069.hpp"
#include "../../Inc/Error.hpp"
#include "../../Inc/TruthTable.hpp"

Comp4069::Comp4069()
{
	for (int i = 0; i < 14; i++) {
		_others[i] = nullptr;
		_values[i] = nts::UNDEFINED;
	}
}

void Comp4069::dump() const
{
	std::cout << "I am a Component 4069 with 6 inverter gates" << std::endl;
}

std::size_t Comp4069::getRelativeInputPin(std::size_t pin)
{
	std::size_t inputPin;

	if (pin < 7)
		inputPin = pin - 1;
	else
		inputPin = pin + 1;
	return (inputPin);
}

nts::Tristate Comp4069::compute(size_t pin)
{
	if (pin > 14)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type 4081."));
	if (_others[pin - 1] != nullptr) {
		if (getPin(pin) == nts::OUT) {
			std::size_t input = getRelativeInputPin(pin);
			_values[input - 1] = _others[input - 1]->compute(_links[input]);
			_values[pin - 1] = TruthTable::inverterTable(_values[input - 1]);
		}
		else if (getPin(pin) == nts::IN)
			_values[pin - 1] = _others[pin - 1]->compute(_links[pin]);
	}
	return (_values[pin - 1]);
}

nts::Pin Comp4069::getPin(size_t pin)
{
	nts::Pin res;

	if (pin > 14)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type 4081."));
	if (pin == 7 || pin == 14)
		res = nts::UNDEF;
	else if (pin % 2 == 0)
		res = nts::OUT;
	else
		res = nts::IN;
	return (res);
}

void Comp4069::setLink(std::size_t pin, nts::IComponent &oth, std::size_t othPin)
{
	if (pin > 14)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type 4081."));
	if (_others[pin - 1] != nullptr)
		throw (NanoException("The pin " + std::to_string(pin) + " is already connected to another pin"));
	_others[pin - 1] = &oth;
	_links[pin] = othPin;
}
