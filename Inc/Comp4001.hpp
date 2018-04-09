//
// Created by yamino on 04/03/18.
//


#pragma once

#include <memory>
#include <iostream>
#include <map>
#include "IComponent.hpp"

class Comp4001 : public nts::IComponent {
	private:
	nts::IComponent *_others[14];
	std::map<std::size_t, std::size_t> _links;
	nts::Tristate _values[14];
	std::pair<std::size_t, std::size_t> getRelativeInputPins(size_t pin);
	public:
	Comp4001();
	~Comp4001() override = default;

	nts::Tristate compute(std::size_t pin = 1) override;
	nts::Pin getPin(std::size_t pin = 1) override;
	void setLink(std::size_t pin, nts::IComponent &oth, std::size_t othPin) override;
	void dump() const override;
};