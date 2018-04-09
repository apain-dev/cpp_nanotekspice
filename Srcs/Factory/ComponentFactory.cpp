//
// Created by yamino on 27/02/18.
//

#include "../../Inc/ComponentFactory.hpp"
#include "../../Inc/Input.hpp"
#include "../../Inc/Output.hpp"
#include "../../Inc/Error.hpp"
#include "../../Inc/True.hpp"
#include "../../Inc/False.hpp"
#include "../../Inc/Comp4081.hpp"
#include "../../Inc/Comp4071.hpp"
#include "../../Inc/Comp4011.hpp"
#include "../../Inc/Comp4001.hpp"
#include "../../Inc/Comp4030.hpp"
#include "../../Inc/Comp4069.hpp"

ComponentFactory::ComponentFactory()
{
	this->_components["input"] = std::bind(&ComponentFactory::createInput, this, std::placeholders::_1);
	this->_components["output"] = std::bind(&ComponentFactory::createOutput, this, std::placeholders::_1);
	this->_components["true"] = std::bind(&ComponentFactory::createTrue, this, std::placeholders::_1);
	this->_components["false"] = std::bind(&ComponentFactory::createFalse, this, std::placeholders::_1);
	this->_components["4081"] = std::bind(&ComponentFactory::createComp4081, this, std::placeholders::_1);
	this->_components["4071"] = std::bind(&ComponentFactory::createComp4071, this, std::placeholders::_1);
	this->_components["4011"] = std::bind(&ComponentFactory::createComp4011, this, std::placeholders::_1);
	this->_components["4001"] = std::bind(&ComponentFactory::createComp4001, this, std::placeholders::_1);
	this->_components["4030"] = std::bind(&ComponentFactory::createComp4030, this, std::placeholders::_1);
	this->_components["4069"] = std::bind(&ComponentFactory::createComp4069, this, std::placeholders::_1);
}

std::unique_ptr<nts::IComponent> ComponentFactory::createComponent(const std::string &name, const std::string &value)
{
	std::unique_ptr<nts::IComponent> ptr;
	auto it = _components.find(name);

	if (it == _components.end())
		throw (NanoException("The component " + name + " does not exist."));
	ptr = this->_components[name](value);
	return (ptr);

}

nts::Tristate  ComponentFactory::stot(const std::string &value)
{
	int val = std::stoi(value);
	nts::Tristate res = nts::UNDEFINED;

	if (val == 1)
		res = nts::TRUE;
	if (val == 0)
		res = nts::FALSE;
	return (res);
}

std::unique_ptr<nts::IComponent> ComponentFactory::createInput(const std::string &value) noexcept
{
	std::unique_ptr<Input> ptr(new Input);

	ptr->setValue(this->stot(value));
	return (ptr);
}

std::unique_ptr<nts::IComponent> ComponentFactory::createOutput(const std::string &value) noexcept
{
	std::unique_ptr<Output> ptr(new Output);

	(void)value;
	return (ptr);
}

std::unique_ptr<nts::IComponent> ComponentFactory::createTrue(const std::string &value) noexcept
{
	std::unique_ptr<True> ptr(new True);

	(void)value;
	return (ptr);
}

std::unique_ptr<nts::IComponent> ComponentFactory::createFalse(const std::string &value) noexcept
{
	std::unique_ptr<False> ptr(new False);

	(void)value;
	return (ptr);
}

std::unique_ptr<nts::IComponent> ComponentFactory::createComp4081(const std::string &value) noexcept
{
	std::unique_ptr<Comp4081> ptr(new Comp4081);

	(void)value;
	return (ptr);
}

std::unique_ptr<nts::IComponent> ComponentFactory::createComp4071(const std::string &value) noexcept
{
	std::unique_ptr<Comp4071> ptr(new Comp4071);

	(void)value;
	return (ptr);
}

std::unique_ptr<nts::IComponent> ComponentFactory::createComp4011(const std::string &value) noexcept
{
	std::unique_ptr<Comp4011> ptr(new Comp4011);

	(void)value;
	return (ptr);
}

std::unique_ptr<nts::IComponent> ComponentFactory::createComp4001(const std::string &value) noexcept
{
	std::unique_ptr<Comp4001> ptr(new Comp4001);

	(void)value;
	return (ptr);
}

std::unique_ptr<nts::IComponent> ComponentFactory::createComp4030(const std::string &value) noexcept
{
	std::unique_ptr<Comp4030> ptr(new Comp4030);

	(void)value;
	return (ptr);
}

std::unique_ptr<nts::IComponent> ComponentFactory::createComp4069(const std::string &value) noexcept
{
	std::unique_ptr<Comp4069> ptr(new Comp4069);

	(void)value;
	return (ptr);
}