//
// Created by yamino on 03/03/18.
//

#pragma once

#include "IComponent.hpp"

class TruthTable {
	public:
		static nts::Tristate andTruthTable(nts::Tristate, nts::Tristate);
		static nts::Tristate orTruthTable(nts::Tristate, nts::Tristate);
		static nts::Tristate XorTruthTable(nts::Tristate, nts::Tristate);
		static nts::Tristate inverterTable(nts::Tristate);
};