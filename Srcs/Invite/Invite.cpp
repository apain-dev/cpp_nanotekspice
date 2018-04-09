/*
** EPITECH PROJECT, 2017
** cpp_d01
** File description:
** no description
*/
#include "../../Inc/Invite.hpp"
#include "../../Inc/Error.hpp"

Invite::Invite(char **args)
{
	circuit = new Circuit(args[1], args);
	setInputs();
	circuit->simulate();
	circuit->displayResult();
	myMap["exit"] = this->exit;
	myMap["simulate"] = this->simulate;
	myMap["display"] = this->display;
	myMap["dump"] = this->dump;
	myMap["--debug"] = this->debug;
	start();
}

Invite::~Invite()
{
	delete (circuit);
}

void Invite::setInputs()
{
	auto validator = circuit->getValidator();
	_inputs = validator.getInputs();
}

bool Invite::start()
{

	std::cout << PROMPT;

	for (std::string line; std::getline(std::cin, line);) {
		try {
			this->Parse(line);
		} catch (const NanoException &e) {
			std::cout << "Error: " << e.what() << std::endl;
		}
		std::cout << PROMPT;
	}
	return true;
}

void Invite::Parse(std::string cmd)
{
	bool success = false;
	std::vector<std::string> cmdContainer;
	auto parser = new Parser;
	int inputValue;

	for (auto &i : myMap) {
		if (cmd.find(i.first) != std::string::npos) {
			(i.second)(this, "");
			success = true;
			break;
		}
	}
	cmdContainer = parser->split(cmd, '=');
	if (!success && cmdContainer.size() == 2) {
		for (auto &i : _inputs) {
			if (i[0] == cmdContainer[0]) {
				try {
					inputValue = std::stoi(cmdContainer[1]);
					if (inputValue == 0 ||
						inputValue == 1) {

						circuit->updateInput(
							std::make_pair(
								cmdContainer[0],
								cmdContainer[1]));

						success = true;
						break;
					} else
						throw NanoException("");
				} catch (...) {
					throw NanoException(
						"wrong command : input={0,1}");
				}
			}
		}
	}
	if (!success)
		throw NanoException("command not found");
}

void Invite::exit(Invite *invite, const std::string &args)
{
	(void)(args);
	(void)(invite);
	std::exit(0);
}

Invite::Invite()
{
}

void Invite::simulate(Invite *invite, const std::string &args)
{
	(void)(args);
	invite->circuit->simulate();
}

void Invite::display(Invite *invite, const std::string &args)
{
	(void)(args);
	invite->circuit->displayResult();
}

void Invite::dump(Invite *invite, const std::string &args)
{
	(void)(args);
	invite->circuit->dump();
}

void Invite::debug(Invite *invite, const std::string &str)
{
	(void)(str);
	auto validator = invite->circuit->getValidator();
	validator.dump();
}
