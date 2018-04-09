//
// Created by yamino on 03/03/18.
//


#pragma once

#include <memory>
#include <iostream>
#include "IComponent.hpp"

class False : public nts::IComponent {
	private:
	nts::IComponent *_other;
	std::pair<std::size_t, std::size_t> _links;
	nts::Tristate _value;
	public:
	False();
	~False() override = default;

	nts::Tristate compute(std::size_t pin = 1) override;
	nts::Pin getPin(std::size_t pin = 1) override;
	void setLink(std::size_t pin, nts::IComponent &oth, std::size_t othPin) override;
	void dump() const override;
};