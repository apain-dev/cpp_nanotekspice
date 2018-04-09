//
// Created by arthur on 2/27/18.
//

#include "../../Inc/Validator.hpp"
#include "../../Inc/Error.hpp"

Validator::Validator()
{
}

Validator::Validator(const std::string &file)
{
	parser = new Parser(file);
	parser->readFile();
	_content = parser->getContent();
	this->shootHashtags();
	this->setFormat();
	this->setLinks();
	this->setInputs();
	this->validate();
}

Validator::~Validator()
{
}

const std::vector<std::vector<std::string>> &Validator::getInputs() const
{
	return _inputs;
}

const std::vector<std::vector<std::string>> &Validator::getLinks() const
{
	return _links;
}

std::vector<std::vector<std::string>> Validator::getComponent()
{
	std::vector<std::vector<std::string>> component;

	for (auto &i : _outputs) {
		component.emplace_back(i);
	}
	for (auto &i : _chipset) {
		component.emplace_back(i);
	}
	return component;
}

void Validator::setLinks()
{
	bool lock = false;
	std::vector<std::string> tmp;
	for (auto &i : _content) {
		if (lock) {
			tmp = parser->split(i, ' ');
			_links.emplace_back(tmp);
			tmp.empty();
		}
		if (i.find(".links") != std::string::npos)
			lock = !lock;
	}
}

void Validator::setInputs()
{
	std::vector<std::string> tmp;
	for (auto &i : _content) {
		if (i.find("input") != std::string::npos) {
			tmp = parser->split(i, ' ');
			_inputs.emplace_back(tmp);
			tmp.empty();
		} else if (i.find("output") != std::string::npos) {
			tmp = parser->split(i, ' ');
			_outputs.emplace_back(tmp);
			tmp.empty();
		} else if (i.find("clock") != std::string::npos) {
			tmp = parser->split(i, ' ');
			_clocks.emplace_back(tmp);
			tmp.empty();
		} else if (i.find(".links") == std::string::npos &&
			i.find(".chipsets") == std::string::npos) {
			tmp = parser->split(i, ' ');
			_chipset.emplace_back(tmp);
			tmp.empty();
		}
		if (i.find(".links") != std::string::npos)
			break;
	}
}

void Validator::setFormat()
{
	int find = 0;
	auto n = std::string::npos;
	for (auto &i : _content) {
		find += (i.find(".chipsets") != n ||
			(find == 1 && i.find(".links") != n)) ? 1 : 0;
	}

	if (find != 2)
		throw NanoException(
			"File must contain one '.chipsets' & then one '.links'");
}

void Validator::setArgs(char **args)
{
	bool result = false;
	int value = -1;

	std::vector<std::string> argsContainer = translateArgs(args);
	std::vector<std::string> str;
	if ((_inputs.size() + _clocks.size()) !=
		argsContainer.size())
		throw NanoException(
			"no input or too few value find. ex : ./nano *.nts input={0/1}");
	for (auto &i : argsContainer) {
		str = parser->split(i, '=');
		for (auto &e: _inputs) {
			if (e[1] == str[0])
				result = true;
		}
		if (!result) {
			for (auto &e: _clocks) {
				str = parser->split(i, '=');
				if (e[1] == str[0])
					result = true;
			}
		}
		if (!result)
			throw NanoException("Arguments: input not known");
		try {
			value = std::stoi(str[1], nullptr);
		} catch (...) {
			throw NanoException(
				"Input : wrong value should be 0 or 1");
		}
		if (value != 0 && value != 1)
			throw NanoException(
				"Input : wrong value should be 0 or 1");
		result = false;
		_argsContent.emplace_back(str);
	}
	this->fillInputs();
}

void Validator::validate()
{
	if (_outputs.empty())
		throw NanoException("Too few output");
	validateName();
}

void Validator::validateName()
{
	std::vector<std::vector<std::string>> allowed;
	std::vector<std::string> str;
	bool result = false;

	for (auto &e: _chipset)
		allowed.emplace_back(e);
	for (auto &e: _inputs)
		allowed.emplace_back(e);
	for (auto &e: _outputs)
		allowed.emplace_back(e);
	for (auto &e: _clocks)
		allowed.emplace_back(e);
	for (auto &i: _links) {
		str = parser->split(i[1], ':');

		for (auto &e: _chipset) {
			if (e[1] == str[0]) {
				result = true;
				break;
			}
		}
		if (!result) {
			for (auto &e: _outputs) {
				if (e[1] == str[0]) {
					result = true;
					break;
				}
			}
		}
		if (!result)
			throw NanoException("Links: chipset's name not known");
		result = false;
		for (auto &e: allowed) {
			str = parser->split(i[0], ':');
			if (e[1] == str[0]) {
				result = true;
				break;
			}
		}
		if (!result)
			throw NanoException("Links: input / output not known");
		result = false;
	}
}

void Validator::shootHashtags()
{
	std::vector<std::string> newContent;
	newContent = _content;
	_content.clear();
	for (auto &i: newContent) {
		if (!i.empty() && i.find('#') == std::string::npos) {
			parser->epur(i);
			_content.emplace_back(i);
		}
	}
}

void Validator::dump()const
{

	std::cout << "\t\t Links" << std::endl;
	for (auto &link : _links) {
		std::cout << link[0] << " | " << link[1] << std::endl;
	}
	std::cout << "\t\t Inputs" << std::endl;

	for (auto &link : _inputs) {
		std::cout << link[0] << " | " << link[1] << std::endl;
	}
	std::cout << "\t\t Outputs" << std::endl;

	for (auto &link : _outputs) {
		std::cout << link[0] << " | " << link[1] << std::endl;
	}
	std::cout << "\t\t Chipset" << std::endl;
	for (auto &c : _chipset) {
		std::cout << c[0] << " | " << c[1] << std::endl;
	}
	std::cout << "\t\t Clock" << std::endl;
	for (auto &c : _clocks) {
		std::cout << c[0] << " | " << c[1] << std::endl;
	}
}

const std::vector<std::vector<std::string>> &Validator::getClocks() const
{
	return _clocks;
}

std::vector<std::string> Validator::translateArgs(char **args)
{
	std::vector<std::string> argsContainer;

	for (int i = 0; args[i]; i++) {
		if (i > 1)
			argsContainer.emplace_back(args[i]);
	}
	return argsContainer;
}

void Validator::fillInputs()
{
	int test = 0;
	auto confirm = static_cast<int>(_inputs.size() + _clocks.size());

	for (auto &i : _inputs) {
		for (auto &e : _argsContent) {
			if (e[0] == i[1]) {
				i.erase(i.begin());
				i.push_back(e[1]);
				test++;
				break;
			}
		}
	}

	for (auto &i : _clocks) {
		for (auto &e : _argsContent) {
			if (e[0] == i[1]) {
				i.erase(i.begin());
				i.push_back(e[1]);
				test++;
				break;
			}
		}
	}
	if (test != confirm)
		throw NanoException("Inputs & Clocks: value should be given");
}
