//
// Created by yamino on 26/02/18.
//

#pragma once

#include <string>
#include <vector>
#include <fstream>

class Parser {

	public:
	Parser() = default;

	Parser(const std::string &name);

	virtual ~Parser() = default;

	void help();

	void readFile();

	std::vector<std::string> getContent();

	void epur(std::string &s);

	std::vector<std::string> split(const std::string &text, char sep);

	private:
	std::string _filename;
	std::string _content;
};