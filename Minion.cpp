#include "Card.h"

Minion::Minion(class_name cN, int cost, int atk, int health, string name, string effect)
{
	_cType = card_type::minion;
	_cName = cN;
	_cost = cost;
	_atk = atk;
	_health = health;
	_name = name;
	_effect = effect;
}

void Minion::printInfo() {
	cout << "Name: " << _name << endl
		<< "Type: " << _cType << endl
		<< "Class: " << _cName << endl
		<< "Cost: " << _cost << endl
		<< "Attack: " << _atk << endl
		<< "Health: " << _health << endl
		<< "Effect: " << _effect << endl;
	return;
}