//
// Created by yamino on 04/03/18.
//

#include "../../Inc/Comp4001.hpp"
#include "../../Inc/Error.hpp"
#include "../../Inc/TruthTable.hpp"

Comp4001::Comp4001()
{
	for (int i = 0; i < 14; i++) {
		_others[i] = nullptr;
		_values[i] = nts::UNDEFINED;
	}
}

void Comp4001::dump() const
{
	std::cout << "I am a Component 4001 with 4 NOR gates" << std::endl;
}

std::pair<std::size_t, std::size_t> Comp4001::getRelativeInputPins(size_t pin)
{
	std::pair<std::size_t, std::size_t> inputPins;

	if (pin == 3)
		inputPins = std::pair<std::size_t, std::size_t>(1, 2);
	if (pin == 4)
		inputPins = std::pair<std::size_t, std::size_t>(5, 6);
	if (pin == 10)
		inputPins = std::pair<std::size_t, std::size_t>(8, 9);
	if (pin == 11)
		inputPins = std::pair<std::size_t, std::size_t>(12, 13);
	return (inputPins);
}

nts::Tristate Comp4001::compute(size_t pin)
{
	if (pin > 14)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type 4071."));
	if (_others[pin - 1] != nullptr) {
		if (getPin(pin) == nts::OUT) {
			std::pair<std::size_t, std::size_t> pins = getRelativeInputPins(pin);
			if (_others[pins.first - 1] != nullptr)
				_values[pins.first - 1] = _others[pins.first - 1]->compute(_links[pins.first]);
			if (_others[pins.second - 1] != nullptr)
				_values[pins.second - 1] = _others[pins.second - 1]->compute(_links[pins.second]);
			_values[pin - 1] = TruthTable::inverterTable(TruthTable::orTruthTable(_values[pins.first - 1], _values[pins.second - 1]));
		}
		else if (getPin(pin) == nts::IN) {
			_values[pin - 1] = _others[pin - 1]->compute(_links[pin]);
		}
	}
	return (_values[pin - 1]);
}

nts::Pin Comp4001::getPin(size_t pin)
{
	nts::Pin res;

	if (pin > 14)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type 4071."));
	if (pin == 7 || pin == 14)
		res = nts::UNDEF;
	else if (pin == 3 || pin == 4 || pin == 10 || pin == 11)
		res = nts::OUT;
	else
		res = nts::IN;
	return (res);
}

void Comp4001::setLink(std::size_t pin, nts::IComponent &oth, std::size_t othPin)
{
	if (pin > 14)
		throw (NanoException("The pin " + std::to_string(pin) + " does not exist on a component of type 4071."));
	if (_others[pin - 1] != nullptr)
		throw (NanoException("The pin " + std::to_string(pin) + " is already connected to another pin"));
	_others[pin - 1] = &oth;
	_links[pin] = othPin;
}