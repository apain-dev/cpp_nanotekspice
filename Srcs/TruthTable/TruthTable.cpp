//
// Created by yamino on 03/03/18.
//

#include "../../Inc/TruthTable.hpp"

nts::Tristate TruthTable::andTruthTable(nts::Tristate fst, nts::Tristate sec)
{
	nts::Tristate res;

	if (fst == nts::FALSE || sec == nts::FALSE)
		res = nts::FALSE;
	else if (fst == nts::TRUE && sec == nts::TRUE)
		res = nts::TRUE;
	else
		res = nts::UNDEFINED;
	return (res);
}

nts::Tristate TruthTable::orTruthTable(nts::Tristate fst, nts::Tristate sec)
{
	nts::Tristate res;

	if (fst == nts::TRUE || sec == nts::TRUE)
		res = nts::TRUE;
	else if (fst == nts::FALSE && sec == nts::FALSE)
		res = nts::FALSE;
	else
		res = nts::UNDEFINED;
	return (res);
}

nts::Tristate TruthTable::XorTruthTable(nts::Tristate fst, nts::Tristate sec)
{
	nts::Tristate res;

	if (fst == nts::UNDEFINED || sec == nts::UNDEFINED)
		res = nts::UNDEFINED;
	else if (fst == sec)
		res = nts::FALSE;
	else
		res = nts::TRUE;
	return (res);
}

nts::Tristate TruthTable::inverterTable(nts::Tristate value)
{
	nts::Tristate res = nts::UNDEFINED;

	if (value == nts::TRUE)
		res = nts::FALSE;
	else if (value == nts::FALSE)
		res = nts::TRUE;
	return (res);
}