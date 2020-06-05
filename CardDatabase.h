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

	bool createCardDatabaseFromFile();
	void processCard(string APIText);
	inline Card* getCard(string name) { return internalDatabase->at(name); }
	/* Other potential APIs
	Specific Class Return
	Specific Card Return
	Specific Cost Return etc */

	void printInfo();

	string& removeQuotes(string &str);
	string& removeColon(string& str);

private:
	string _dbFileName;
	map<string, Card*>* internalDatabase;
	int numMinion, numSpell, numWeapon, numHero;
};