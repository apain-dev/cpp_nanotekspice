//
// Created by arthur on 3/3/18.
//

#ifndef CPP_D17_ERROR_HPP
#define CPP_D17_ERROR_HPP

#include <exception>
#include <string>
#include <utility>

class NanoException : public std::exception {
	private:
	std::string _msg;
	public:
	NanoException(std::string const &) throw();

	~NanoException() throw();

	const char *what() const throw();
};

#endif //CPP_D17_ERROR_HPP
