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

Spell::Spell(class_name cN, int cost, string name, string effect)
{
	_cType = card_type::spell;
	_cName = cN;
	_cost = cost;
	_name = name;
	_effect = effect;
}

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

Hero::Hero(class_name cN, int cost, int armor, string name, string effect)
{
	_cType = card_type::hero;
	_cName = cN;
	_cost = cost;
	_armor = armor;
	_name = name;
	_effect = effect;
}
