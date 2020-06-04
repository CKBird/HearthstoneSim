#include "Card.h"

Spell::Spell(class_name cN, int cost, string name, string effect)
{
	_cType = card_type::spell;
	_cName = cN;
	_cost = cost;
	_name = name;
	_effect = effect;
}

void Spell::printInfo() {
	cout << "Name: " << _name << endl
		<< "Type: " << _cType << endl
		<< "Class: " << _cName << endl
		<< "Cost: " << _cost << endl
		<< "Effect: " << _effect << endl;
	return;
}