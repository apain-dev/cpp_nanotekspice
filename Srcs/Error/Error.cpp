#include "../../Inc/Error.hpp"

NanoException::NanoException(std::string const &message) throw()
	: _msg(message)
{
}

NanoException::~NanoException() throw()
{
}

const char *NanoException::what() const throw()
{
	return (_msg.c_str());
}