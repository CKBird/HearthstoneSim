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
	//internalDatabase = new map<string, Card*>;
	numMinion = numSpell = numWeapon = numHero = 0;
	database = new db;
}

CardDatabase::CardDatabase(string dbFName) {
	_dbFileName = dbFName;
	//internalDatabase = new map<string, Card*>;
	numMinion = numSpell = numWeapon = numHero = 0;
	database = new db;
}

CardDatabase::~CardDatabase() {
	//delete internalDatabase;
	delete database;
}

//This will use stored _dbFileName to populate all appropriate cards
bool CardDatabase::createCardDatabaseFromFile() {
	ofstream dboFile("collectibleCards.txt");
	if (!dboFile.is_open()) {
		cout << "Cannot create collectibleCards.txt" << endl;
		return false;
	}
	
	//Before we start adding to database, must initialize it
	if (!initializeDatabase()) {
		return false;
	}

	string readLine;
	ifstream dbFile(_dbFileName);
	if (dbFile.is_open()) {
		while (getline(dbFile, readLine)) {
			if (readLine.find("\"collectible\":true") == string::npos)
				continue; //Don't handle tokens yet
			//if (readLine.find("\"type\":\"Hero\"") != string::npos) {} Allow heroes through, sort them by cost later
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
			//If there's no cost, hero isn't truly a 'card' and skip
			if (cost == "") return;
			tempCard = new Hero(cName, atoi(cost.c_str()), atoi(armor.c_str()), name, text);
			numHero++;
		}
		else {
			cout << "Incorrect type found: " << type << endl;
			return;
		}
		if (!insertCardToDatabase(tempCard)) {
			cout << "Error inserting card..." << endl;
		}
		//cout << "TempCard is: " << endl;
		//tempCard->printInfo();
	}
}

bool CardDatabase::initializeDatabase()
{
	//set up the map < class_name,	map*<card_type, multimap*<int, Card*>	>	>
	//create empty <class_name, map*<...>> for each class
	//Create empty <card_type, multimap*<...>> for each card type for each class
	//Don't need to populate the multimaps, they will be populated once we start adding cards to it

	for (class_name className : all_classes) { //Creating the empty class_name, map*<...>
		//map* tempMap = new map<card_type, multimap<int, Card*>>;
		middleMap mMap;
		database->insert(make_pair(className, mMap));
		for (card_type cardType : all_types) { //Create the empty multimap<>
			//multimap* tempMMap = new multimap<int, Card*>;
			innerMap iMap;
			database->at(className).insert(make_pair(cardType, iMap));
		}
	}
	return true;
}

bool CardDatabase::insertCardToDatabase(Card* crd) {
	//Initially, simply insert card into the card map
	//internalDatabase->insert(make_pair(crd->getName(), crd));
	//return true;

	//Extend this solution to allow for faster search and better sorting
	//Instead of having all cards in one container, have multiple containers
	//Each container should sort the cards by some important value
	//If we assume by class and then by cardtype...
	//Create a map of multimaps
	//Each map will be a different class (11 total)
	//Each map will contain a multimap for each card type
	//Ex: Map: Demon Hunter
	//DemonHunterMap: Mininons, Spells, Weapons, Heroes
	//Now that we have a map of multimaps, we want each 'key' in the sub-multimap to be as medium-small as possible
	//Fast to find keys, slow to search through all the cards of same key
	//DemonHunterMap:Minions:: insert cards by minimal-key
	//Minions have cost, effect, name, attack and health
	//If we do key based on name(or effect), every key will only have 1 card...
	//But if we want to find all demon hunter cards with cost 3, we have to search _every_ object
	//This only leaves attack, health, or cost. Since we can only have 1 key and attack/health are implicitly linked as 'stats'
	//We should key by cost

	//DemonHunterMap::MultiMapMinions::Key:Cost, Value: Card
	//To find all 'minions' just go to each classes map, find the multimap of minions and print all elements
	//To find all '2 cost cards' go to each classes map, find all cards that have key of 0 in each of the 4 cardtype multimaps, and print
	//To find all '3 attack demon hunter cards' go to demon hunter map, find minion multimap, and (unfortunately) search every minion for 3 attack

	//As with all databases, we need to decide which operations are most common and which are least common
	//For future, we plan on implementing a 'collection view' which sorts by class, then by cost (disregard type)
	//But we know that API accessors and devs will want to sort by type before cost
	//Attack, Health, Armor, Durability etc are very niche searches, so we decide for them to take the efficiency hit

	/*
		Maps:			Demon Hunter, ...
						/		|		|		\
		Multimaps: Minion	Spell		Weapon		Hero
		Multimap::Key = Cost

					DemonHunter::Minion
					/		|		|		\ ...
				0-cost	1-cost		2-cost	3-cost ...
	*/

	//To implement, we have a card with all relevant data, 
	//format the pair for the deepest multimap (cost, card)
	//Then format the pair for card type map (card_type, multimap)
	//Then finally insert into the class_name,map(multimap)) class_name map

	pair<int, Card*> p1 = make_pair(crd->getCost(), crd);
	database->at(crd->getClassName()).at(crd->getType()).insert(p1);
	return true;
}

void CardDatabase::printInfo() {
	cout << "Number of Classes in Database: " << database->size() << endl
		//<< "Number of Types in Class Demon Hunter: " << database->at(class_name::demon_hunter).size() << endl
		//<< "Number of Druid Minions: " << database->at(class_name::druid).at(card_type::minion).size() << endl
		//<< "Number of Rogue Spells that cost 0: " << database->at(class_name::rogue).at(card_type::spell).count(0) << endl
		<< "Number of Minions: " << numMinion << endl
		<< "Number of Spells: " << numSpell << endl
		<< "Number of Weapons: " << numWeapon << endl
		<< "Number of Heroes: " << numHero << endl;
}

void CardDatabase::outputCards(class_name cN, card_type cT, int cost) {
	int foundCount = 0;
	if (cN == class_name::none && cT == card_type::none) { //Default to none means print all
		for (class_name className : all_classes) {
			for (card_type cardType : all_types) {

			}
		}
	
	}
	else if (cN == class_name::none) {
		for (class_name className : all_classes) {

		}
	}
	else if (cT == card_type::none) {
		for (card_type cardType : all_types) {

		}
	}
	else {
		cout << "Printing out all cards of class: " << cN << "of type " << cT << endl;
		for (auto it = database->at(cN).at(cT).begin(); it != database->at(cN).at(cT).end(); ++it) {
			if ((*it).first == cost) {
				cout << "Cost: " << (*it).first << " - Name: " << (*it).second->getName() << endl;
				foundCount++;
			}
		}
	}
	cout << foundCount << " cards matched your search!" << endl;
}

string& CardDatabase::removeQuotes(string &str) {
	str.erase(remove(str.begin(), str.end(), '\"'), str.end());
	return str;
}

string& CardDatabase::removeColon(string& str) {
	str.erase(remove(str.begin(), str.end(), ':'), str.end());
	return str;
}