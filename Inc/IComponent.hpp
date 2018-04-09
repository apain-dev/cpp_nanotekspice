//
// Created by yamino on 30/01/18.
//

#pragma once

#include <cstddef>

namespace nts {
	enum Pin {
		UNDEF,
		IN,
		OUT
	};
	enum Tristate {
		UNDEFINED = (-true),
		TRUE = true,
		FALSE = false
	};
	class IComponent {
		public:
		virtual ~IComponent() = default;

		virtual nts::Tristate compute(std::size_t pin = 1) = 0;
		virtual nts::Pin getPin(std::size_t pin = 1) = 0;
		virtual void setLink(std::size_t pin, nts::IComponent &oth,
			std::size_t othPin) = 0;
		virtual void dump() const = 0;
	};
}