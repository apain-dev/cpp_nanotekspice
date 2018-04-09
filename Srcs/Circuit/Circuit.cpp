//
// Created by yamino on 02/03/18.
//

#include "../../Inc/Circuit.hpp"
#include "../../Inc/Error.hpp"
#include "../../Inc/TruthTable.hpp"

Circuit::Circuit() :_validator(Validator()), _factory(ComponentFactory()), _result(nts::UNDEFINED)
{
}

Circuit::Circuit(const std::string &file, char **av) : _factory(ComponentFactory()), _result(nts::UNDEFINED)
{
	try {
		_validator = Validator(file);
		_validator.setArgs(av);
		this->setComponents();
		this->setInputs();
		this->linkCircuit();
	} catch (NanoException &ex) {
		throw (NanoException(ex.what()));
	} catch (const char *ex) {
		throw (ex);
	};
}

Circuit::~Circuit()
{
	for (auto &comp : _circuit) {
		comp.second.reset();
	}
	for (auto &in : _inputs) {
		in.second.reset();
	}
	for (auto &out : _outputs) {
		out.second.reset();
	}
}

bool Circuit::isInCircuit(const std::string &name) const
{
	return (_circuit.find(name) != _circuit.end());
}

bool Circuit::isInInputs(const std::string &name) const
{
	return (_inputs.find(name) != _inputs.end());
}

bool Circuit::isInOutputs(const std::string &name) const
{
	return (_outputs.find(name) != _outputs.end());
}

bool Circuit::checkName(const std::string &name) const
{
	bool res = false;

	if (isInCircuit(name))
		res = true;
	if (isInInputs(name))
		res = true;
	if (isInOutputs(name))
		res = true;
	return (res);
}

void Circuit::setComponents()
{
	try {
		for (auto &comp : _validator.getComponent()) {
			if (checkName(comp[1]))
				throw (NanoException("Two components have same name: " + comp[1]));
			if (comp[0].compare("output") == 0) {
				Output *tmp = (Output *)_factory.createComponent(comp[0], "").release();
				_outputs[comp[1]] = std::unique_ptr<Output>(tmp);
			} else {
				_circuit[comp[1]] = _factory.createComponent(comp[0], "");
			}
		}
	} catch (NanoException &ex) {
		throw (NanoException(ex.what()));
	};
}

void Circuit::setInputs()
{
	try {
		for (auto &in : _validator.getInputs()) {
			if (checkName(in[0]))
				throw (NanoException("Two components have same name: " + in[0]));
			Input *tmp = (Input *)_factory.createComponent("input", in[1]).release();
			_inputs[in[0]] = std::unique_ptr<Input>(tmp);
		}
		for (auto &clock : _validator.getClocks()) {
			if (checkName(clock[0]))
				throw (NanoException("Two components have same name: " + clock[0]));
			Input *tmp = (Input *)_factory.createComponent("input", clock[1]).release();
			tmp->setClock();
			_inputs[clock[0]] = std::unique_ptr<Input>(tmp);
		}
	} catch (NanoException &ex) {
		throw (NanoException(ex.what()));
	};
}

std::string Circuit::findName(const std::string &s) const
{
	std::size_t pos = s.find(':');
	std::string name = s.substr(0, pos);

	return (name);
}

int Circuit::findPin(const std::string &s) const
{
	std::size_t pos = s.find(':');
	std::string nb = s.substr(pos + 1, s.npos);
	int pin = std::stoi(nb);

	return (pin);
}

void Circuit::linkComponent(std::string &fstName, std::string &secName, std::pair<std::size_t, std::size_t> pins)
{
	if (isInCircuit(fstName)) {
		if (isInCircuit(secName))
			_circuit[fstName]->setLink(pins.first, *_circuit[secName], pins.second);
		else if (isInInputs(secName))
			_circuit[fstName]->setLink(pins.first, *_inputs[secName], pins.second);
		else
			_circuit[fstName]->setLink(pins.first, *_outputs[secName], pins.second);
	} else if (isInInputs(fstName)) {
		if (isInCircuit(secName))
			_inputs[fstName]->setLink(pins.first, *_circuit[secName], pins.second);
		else if (isInInputs(secName))
			_inputs[fstName]->setLink(pins.first, *_inputs[secName], pins.second);
		else
			_inputs[fstName]->setLink(pins.first, *_outputs[secName], pins.second);
	} else {
		if (isInCircuit(secName))
			_outputs[fstName]->setLink(pins.first, *_circuit[secName], pins.second);
		else if (isInInputs(secName))
			_outputs[fstName]->setLink(pins.first, *_inputs[secName], pins.second);
		else
			_outputs[fstName]->setLink(pins.first, *_outputs[secName], pins.second);
	}
}

int Circuit::areOutputsAllLinked()
{
	int nb = 0;

	for (auto &out : _outputs) {
		if (!out.second->isLinked())
			nb++;
	}
	return (nb);
}

void Circuit::linkCircuit()
{
	std::string fstName;
	std::string secName;
	std::pair<int, int> pins;
	int notLinked;

	for (auto &link : _validator.getLinks()) {
		fstName = findName(link[0]);
		secName = findName(link[1]);
		if (!checkName(fstName) || !checkName(secName))
			throw (NanoException("A component in .links section does not exist."));
		pins = std::pair<int, int>(findPin(link[0]), findPin(link[1]));
		linkComponent(fstName, secName, pins);
		linkComponent(secName, fstName, std::pair<int, int>(pins.second, pins.first));
	}
	notLinked = areOutputsAllLinked();
	if (notLinked > 0)
		throw (NanoException(std::to_string(notLinked) + " output(s) are not linked."));
}

void Circuit::simulate()
{
	nts::Tristate val;

	for (auto &out : _outputs) {
		out.second->compute();
	}
	for (auto &in : _inputs) {
		if (in.second->getClock()) {
			val = in.second->compute();
			in.second->setValue(TruthTable::inverterTable(val));
		}
	}
}

const Validator &Circuit::getValidator() const
{
	return _validator;
}

void Circuit::updateInput(std::pair<std::string, std::string> update)
{
	nts::Tristate val;
	if (!isInInputs(update.first) || _inputs[update.first]->getClock())
		throw (NanoException("The input " + update.first + " does not exist. Notice that clocks can't be reset."));
	val = ComponentFactory::stot(update.second);
	_inputs[update.first]->setValue(val);
}

void Circuit::displayResult() const
{
	for (auto &out : _outputs) {
		std::cout << out.first << "=" << out.second->getValue() << std::endl;
	}
}

void Circuit::dump() const
{
	for (auto &in : _inputs) {
		in.second->dump();
	}
	for (auto &out : _outputs) {
		out.second->dump();
	}
	for (auto &comp : _circuit) {
		comp.second->dump();
	}

}