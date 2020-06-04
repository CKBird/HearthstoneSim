#include "Card.h"

Weapon::Weapon(class_name cN, int cost, int atk, int dura, string name, string effect)
{
	_cType = card_type::weapon;
	_cName = cN;
	_cost = cost;
	_atk = atk;
	_dura = dura;
	_name = name;
	_effect = effect;
}

void Weapon::printInfo() {

	return;
}