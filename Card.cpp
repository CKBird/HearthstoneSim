#include "Card.h"

Card::Card() {
	_cType = card_type::none;
	_cName = class_name::none;
	_cost = -1;
	_effect = "";
	_name = "";
}

Card::Card(card_type cT, class_name cN) {
	_cType = cT;
	_cName = cN;
	_cost = -1;
	_effect = "";
	_name = "";
}

void Card::printInfo()
{
}
