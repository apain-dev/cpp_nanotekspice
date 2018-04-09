//
// Created by arthur on 2/26/18.
//

#ifndef CPP_D17_INVITE_HPP
#define CPP_D17_INVITE_HPP

#include <vector>
#include <functional>
#include "Circuit.hpp"

#define PROMPT "> "

class Invite {
	public:
	std::map<std::string,  std::function<void (Invite *invite, const std::string&)>> myMap;
	Circuit *circuit;
	std::vector<std::vector<std::string>> _inputs;
	Invite();

	explicit Invite(char **);
	~Invite();

	bool start();

	void Parse(std::string cmd);

	static void exit(Invite *invite, const std::string &args);

	static void simulate(Invite *invite, const std::string &args);
	static void display(Invite *invite, const std::string &args);
	static void dump(Invite *, const std::string &a);
	static void debug(Invite *, const std::string &);
	void setInputs();
};

#endif //CPP_D17_INVITE_HPP
