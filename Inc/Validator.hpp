//
// Created by arthur on 2/27/18.
//

#ifndef CPP_D17_VALIDATOR_HPP
#define CPP_D17_VALIDATOR_HPP

#include <string>
#include <vector>
#include <ostream>
#include <algorithm>
#include <sstream>
#include <iostream>
#include "Parser.hpp"

class Validator {
	private:
	std::vector<std::vector<std::string>> _inputs;
	std::vector<std::vector<std::string>> _clocks;
	std::vector<std::vector<std::string>> _outputs;
	std::vector<std::vector<std::string>> _links;
	std::vector<std::string> _content;
	std::vector<std::vector<std::string>> _chipset;
	std::vector<std::vector<std::string>> _argsContent;
	Parser *parser;

	public:
	Validator();

	explicit Validator(const std::string &fileContent);

	virtual ~Validator();

	void setFormat();

	void shootHashtags();

	void setInputs();

	void setLinks();

	void dump() const;

	std::vector<std::vector<std::string>> getComponent();

	void validate();

	void validateName();

	void setArgs(char **);

	std::vector<std::string> translateArgs(char **args);

	void fillInputs();

	const std::vector<std::vector<std::string>> &getLinks() const;

	const std::vector<std::vector<std::string>> &getInputs() const;

	const std::vector<std::vector<std::string>> &getClocks() const;
};

#endif //CPP_D17_VALIDATOR_HPP
