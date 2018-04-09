//
// Created by yamino on 26/02/18.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "../../Inc/Parser.hpp"

Parser::Parser(const std::string &name) : _filename(name)
{
}

void Parser::help()
{
	std::cout
		<< "Usage: ./nanotekspice circuit_file.nts input_name=input_value"
		<< std::endl;
}

void Parser::readFile()
{
	std::ifstream file(this->_filename);

	if (file.is_open()) {
		this->_content = std::string(
			(std::istreambuf_iterator<char>(file)),
			(std::istreambuf_iterator<char>()));
		file.close();
	} else
		throw (std::invalid_argument("The file does not exist."));
}

std::vector<std::string> Parser::getContent()
{
	return (split(this->_content, '\n'));
}

std::vector<std::string> Parser::split(const std::string &text, char sep)
{
	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != std::string::npos) {
		if (end != start) {
			tokens.push_back(text.substr(start, end - start));
		}
		start = end + 1;
	}
	if (end != start) {
		tokens.push_back(text.substr(start));
	}
	return tokens;
}

void Parser::epur(std::string &s)
{
	bool space = false;
	auto p = s.begin();
	for (auto ch : s)
		if (std::isspace(ch)) {
			space = p != s.begin();
		} else {
			if (space)
				*p++ = ' ';
			*p++ = ch;
			space = false;
		}
	s.erase(p, s.end());
}
