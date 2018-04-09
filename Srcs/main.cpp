#include <iostream>
#include "../Inc/Validator.hpp"
#include "../Inc/Error.hpp"
#include "../Inc/Invite.hpp"

int main(int ac, char **av)
{
	Parser parse;

	if (ac < 2) {
		parse.help();
		return (84);
	}
	
	try {
		auto invite = new Invite(av);
		(void)(invite);
	} catch (const NanoException &ex) {
		std::cout << ex.what() << std::endl;
		parse.help();
		return (84);
	} catch (const char *e){
		std::cout << e << std::endl;
		return (84);
	};

	return (0);
}
