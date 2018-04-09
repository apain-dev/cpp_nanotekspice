//
// Created by yamino on 01/03/18.
//

#pragma once

#include <memory>
#include <iostream>
#include "IComponent.hpp"

class Output : public nts::IComponent {
	private:
		nts::IComponent *_other;
		std::pair<std::size_t, std::size_t> _links;
		nts::Tristate  _value;
	public:
		Output();
		~Output() override = default;

		nts::Tristate compute(std::size_t pin = 1) override;
		nts::Pin getPin(std::size_t pin = 1) override;
		void setLink(std::size_t pin, nts::IComponent &oth, std::size_t othPin) override;
		bool isLinked();
		void dump() const override;
		char getValue() const;
};