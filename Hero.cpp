#include "Card.h"

Hero::Hero(class_name cN, int cost, int armor, string name, string effect)
{
	_cType = card_type::hero;
	_cName = cN;
	_cost = cost;
	_armor = armor;
	_name = name;
	_effect = effect;
}

void Hero::printInfo() {

	return;
}