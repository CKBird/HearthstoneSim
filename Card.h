#pragma once
#include <string>
#include <iostream>

using namespace std;

//Changes to the following enum classes must be maintained in the operator<< as well
enum class card_type { none, minion, spell, weapon, hero };
enum class class_name {
	none, demon_hunter, druid, hunter, mage, paladin,
	priest, rogue, shaman, warlock, warrior, neutral
};

//Base class for Minion, Spell, Hero classes
class Card {
public:
	Card(); //Prevent compiler from making
	Card(card_type cT, class_name cN);

	virtual void printInfo();

	card_type getType() { return _cType;}
	int getCost() { return _cost; }
	string getEffect() { return _effect; }
	string getName() { return _name; }
	class_name getClassName() { return _cName; }

	void setType(card_type cT) { _cType = cT; }
	void setCost(int cost) { _cost = cost; }
	void setEffect(string effect) { _effect = effect; }
	void setName(string name) { _name = name; }
	void setClassName(class_name cN) { _cName = cN; }

	friend ostream& operator<< (ostream& out, const card_type& value);
	friend ostream& operator<< (ostream& out, const class_name& value);

protected:
	card_type _cType;
	int _cost;
	string _effect, _name;
	class_name _cName;
};


class Minion : public Card {
public:
	Minion(class_name cN, int cost, int atk, int health, string name, string effect = "");
	
	void printInfo();
	
	int getHealth() { return _health; }
	int getAtk() { return _atk; }

	bool setHealth(int health) { _health = health; }
	bool setAtk(int atk) { _atk = atk; }
private:
	bool assertType() { if (_cType != card_type::minion) return false; }
	int _atk, _health;
};

class Spell : public Card {
public:
	Spell(class_name cN, int cost, string name, string effect = "");

	void printInfo();
private:
	bool assertType() { if (_cType != card_type::spell) return false; }
};

class Weapon : public Card {
public:
	Weapon(class_name cN, int cost, int atk, int dura, string name, string effect = "");

	void printInfo();
private:
	bool assertType() { if (_cType != card_type::weapon) return false; }
	int _atk, _dura;
};

class Hero : public Card {
public:
	Hero(class_name cN, int cost, int armor, string name, string effect = "");
	void printInfo();
private:
	bool assertType() { if (_cType != card_type::hero) return false; }
	int _armor;
};

inline
std::ostream& operator<<(std::ostream& out, const card_type& value) {
	const char* s = 0;
#define PROCESS_VAL(p) case(p): s = #p; break;
	switch (value) {
		PROCESS_VAL(card_type::none);
		PROCESS_VAL(card_type::minion);
		PROCESS_VAL(card_type::spell);
		PROCESS_VAL(card_type::weapon);
		PROCESS_VAL(card_type::hero);
	}
#undef PROCESS_VAL
	return out << s;
}

inline
std::ostream& operator<<(std::ostream& out, const class_name& value) {
	const char* s = 0;
#define PROCESS_VAL(p) case(p): s = #p; break;
	switch (value) {
		PROCESS_VAL(class_name::none);
		PROCESS_VAL(class_name::demon_hunter);
		PROCESS_VAL(class_name::druid);
		PROCESS_VAL(class_name::hunter);
		PROCESS_VAL(class_name::mage);
		PROCESS_VAL(class_name::paladin);
		PROCESS_VAL(class_name::priest);
		PROCESS_VAL(class_name::rogue);
		PROCESS_VAL(class_name::shaman);
		PROCESS_VAL(class_name::warlock);
		PROCESS_VAL(class_name::warrior);
		PROCESS_VAL(class_name::neutral);
	}
#undef PROCESS_VAL
	return out << s;
}