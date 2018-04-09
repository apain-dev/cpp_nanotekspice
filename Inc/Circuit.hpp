//
// Created by yamino on 27/02/18.
//

#pragma once

#include <map>
#include <vector>
#include <memory>
#include "IComponent.hpp"
#include "Input.hpp"
#include "Output.hpp"
#include "ComponentFactory.hpp"
#include "Validator.hpp"

class Circuit {
	private:
		Validator _validator;
		ComponentFactory _factory;
		std::map<std::string, std::unique_ptr<nts::IComponent>> _circuit;
		std::map<std::string, std::unique_ptr<Input>> _inputs;
		std::map<std::string, std::unique_ptr<Output>> _outputs;
		nts::Tristate _result;

		std::string findName(const std::string &s) const;
		bool checkName(const std::string &name) const;
		int findPin(const std::string &s) const;
		bool isInCircuit(const std::string &name) const;
		bool isInInputs(const std::string &name) const;
		bool isInOutputs(const std::string &name) const;
 		void linkComponent(std::string &fstName, std::string &secName, std::pair<std::size_t, std::size_t> pins);
		int areOutputsAllLinked();

	public:
		Circuit();
		Circuit(const std::string &file, char **av);
		~Circuit();

		void setComponents();
		void setInputs();
		void linkCircuit();
		void simulate();
		void displayResult() const;
		void dump() const;
		void updateInput(std::pair<std::string, std::string>);
		const Validator &getValidator() const;
};