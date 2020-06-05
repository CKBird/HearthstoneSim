#include "CardDatabase.h"
#include "Card.h"

#include "stdio.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

CardDatabase::CardDatabase() {
	_dbFileName = "";
	internalDatabase = new map<string, Card*>;
	numMinion = numSpell = numWeapon = numHero = 0;
}

CardDatabase::CardDatabase(string dbFName) {
	_dbFileName = dbFName;
	internalDatabase = new map<string, Card*>;
	numMinion = numSpell = numWeapon = numHero = 0;
}

CardDatabase::~CardDatabase() {
	delete internalDatabase;
}

//This will use stored _dbFileName to populate all appropriate cards
bool CardDatabase::createCardDatabaseFromFile() {
	ofstream dboFile("collectibleCards.txt");
	if (!dboFile.is_open()) {
		cout << "Cannot create collectibleCards.txt" << endl;
		return false;
	}
	
	string readLine;
	ifstream dbFile(_dbFileName);
	if (dbFile.is_open()) {
		while (getline(dbFile, readLine)) {
			if (readLine.find("\"collectible\":true") == string::npos)
				continue;
			if (readLine.find("\"type\":\"Hero\"") != string::npos)
				continue;
			//cout << "readLine: " << readLine << endl;
			dboFile << readLine << endl;
			/* Now process the 'line' which contains the entire card*/
			this->processCard(readLine);
		}
		dbFile.close();
	} else {
		cout << "Unable to open file " << _dbFileName << endl;
		return false;
	}
	return true;
}

void CardDatabase::processCard(string APIText) {
	/* Turn APIText into a card object.
	1. Parse input string into different pieces
	2. Determine type of 'Card' to make
	3. Store data
	4. Store Card in internalDatabase */

	//Separating character is comma-newline-quote
	string del = ",\"";
	size_t pos = 0;
	string token;
	vector<string> vStr;
	while ((pos = APIText.find(del)) != string::npos) {
		token = APIText.substr(0, pos);
		//cout << token << endl;
		vStr.push_back(token);
		APIText.erase(0, pos + del.length());
	}
	vStr.push_back(APIText);
	//cout << APIText << endl;

	string field;
	string value;
	size_t pos2;
	string name, type, cost, text, playerClass, attack, health, durability, armor = "";
	for (int i = 0; i < vStr.size(); i++) {
		//cout << vStr.at(i) << endl;
		pos2 = (vStr.at(i)).find("\"");
		if (pos2 != string::npos) {
			field = (vStr.at(i)).substr(0, pos2);
			//Work with field
			(vStr.at(i)).erase(0, pos2 + 1);
			//Now vStr holds the rest of the item
			value = removeQuotes(removeColon(vStr.at(i)));
			if (field == "name") {				
				name = value;
			}
			else if (field == "type") {				
				type = value;
			}
			else if (field == "cost") {				
				cost = value;
			}
			else if (field == "text") {				
				text = value;
			}
			else if (field == "playerClass") {				
				playerClass = value;
			}
			else if (field == "attack") {				
				attack = value;
			}
			else if (field == "health") {				
				health = value;
			}
			else if (field == "durability") {
				durability = value;
			}
			else if (field == "armor") {	
				armor = value;
			}
		}
	}

	if (type != "") {
		if (playerClass == "") {
			return;
		}
		class_name cName = class_name::none;
		if (playerClass == "Demon Hunter") {
			cName = class_name::demon_hunter;
		}
		else if (playerClass == "Druid") {
			cName = class_name::druid;
		}
		else if (playerClass == "Hunter") {
			cName = class_name::hunter;
		}
		else if (playerClass == "Mage") {
			cName = class_name::mage;
		}
		else if (playerClass == "Paladin") {
			cName = class_name::paladin;
		}
		else if (playerClass == "Priest") {
			cName = class_name::priest;
		}
		else if (playerClass == "Rogue") {
			cName = class_name::rogue;
		}
		else if (playerClass == "Shaman") {
			cName = class_name::shaman;
		}
		else if (playerClass == "Warlock") {
			cName = class_name::warlock;
		}
		else if (playerClass == "Warrior") {
			cName = class_name::warrior;
		}
		else if (playerClass == "Neutral") {
			cName = class_name::neutral;
		}
		else {
			cout << "Incorrect class found... " << playerClass << endl;
			return;
		}
		
		Card* tempCard;
		if (type == "Minion") {
			//Create minion card
			tempCard = new Minion(cName, atoi(cost.c_str()), atoi(attack.c_str()), atoi(health.c_str()), name, text);
			numMinion++;
		}
		else if (type == "Spell") {
			//Create spell card
			tempCard = new Spell(cName, atoi(cost.c_str()), name, text);
			numSpell++;
		}
		else if (type == "Weapon") {
			//Create weapon card
			tempCard = new Weapon(cName, atoi(cost.c_str()), atoi(attack.c_str()), atoi(durability.c_str()), name, text);
			numWeapon++;
		}
		else if (type == "Hero") {
			//create hero card
			//Hero::Hero(class_name cN, int cost, int armor, string name, string effect)
			tempCard = new Hero(cName, atoi(cost.c_str()), atoi(armor.c_str()), name, text);
			numHero++;
		}
		else {
			cout << "Incorrect type found: " << type << endl;
			return;
		}
		internalDatabase->insert(make_pair(name, tempCard));
		//cout << "TempCard is: " << endl;
		//tempCard->printInfo();
	}
}

void CardDatabase::printInfo() {
	cout << "Number of Cards in Database: " << internalDatabase->size() << endl
		<< "Number of Minions: " << numMinion << endl
		<< "Number of Spells: " << numSpell << endl
		<< "Number of Weapons: " << numWeapon << endl
		<< "Number of Heroes: " << numHero << endl;
}

string& CardDatabase::removeQuotes(string &str) {
	str.erase(remove(str.begin(), str.end(), '\"'), str.end());
	return str;
}

string& CardDatabase::removeColon(string& str) {
	str.erase(remove(str.begin(), str.end(), ':'), str.end());
	return str;
}