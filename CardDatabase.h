#pragma once
#include <string>
#include <iostream>
#include <map>
#include "Card.h"

using namespace std;

/* CardDatabase class is built to handle creating the original card database previously
acquired from the Blizzard-provided API. Currently, to update this file needs to be
manually downloaded from the API again, processed to add newline characters,
and then saved into the appropriate working directory for this project.

In the future it is possible to add scheduled API calls to update database as needed. */

class CardDatabase {
public:
	CardDatabase();
	CardDatabase(string dbFName);
	~CardDatabase();

	typedef multimap<int, Card*> innerMap;
	typedef map<card_type, innerMap> middleMap;
	typedef map<class_name, middleMap> db;

	bool createCardDatabaseFromFile();
	void processCard(string APIText);
	bool initializeDatabase();
	bool insertCardToDatabase(Card* crd);

	//inline Card* getCard(string name) { return internalDatabase->at(name); }


	void printInfo();
	void outputCards(class_name cN = class_name::none, card_type cT = card_type::none, int cost = -1);

	string& removeQuotes(string &str);
	string& removeColon(string& str);

private:
	string _dbFileName;
	//map<string, Card*>* internalDatabase;
	int numMinion, numSpell, numWeapon, numHero;
	db* database;
};