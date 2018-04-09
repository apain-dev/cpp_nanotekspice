//
// Created by yamino on 26/02/18.
//

#pragma once

#include <string>
#include <map>
#include <memory>
#include <functional>
#include "IComponent.hpp"

using create = std::unique_ptr<nts::IComponent> (const std::string &);

class ComponentFactory {
	private:
		std::map<std::string, std::function<create>> _components;

		std::unique_ptr<nts::IComponent> createInput(const std::string &value) noexcept;
		std::unique_ptr<nts::IComponent> createOutput(const std::string &value) noexcept;
		std::unique_ptr<nts::IComponent> createTrue(const std::string &value) noexcept;
		std::unique_ptr<nts::IComponent> createFalse(const std::string &value) noexcept;
		std::unique_ptr<nts::IComponent> createComp4081(const std::string &value) noexcept;
		std::unique_ptr<nts::IComponent> createComp4071(const std::string &value) noexcept;
		std::unique_ptr<nts::IComponent> createComp4011(const std::string &value) noexcept;
		std::unique_ptr<nts::IComponent> createComp4001(const std::string &value) noexcept;
		std::unique_ptr<nts::IComponent> createComp4030(const std::string &value) noexcept;
		std::unique_ptr<nts::IComponent> createComp4069(const std::string &value) noexcept;
	public:
		ComponentFactory();
		virtual ~ComponentFactory() = default;

		static nts::Tristate stot(const std::string &value);
		std::unique_ptr<nts::IComponent> createComponent(const std::string &name, const std::string &value);
};