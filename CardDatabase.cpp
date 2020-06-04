#include "CardDatabase.h"
#include "Card.h"

#include "stdio.h"
#include <iostream>
#include <fstream>

using namespace std;

CardDatabase::CardDatabase() {
	_dbFileName = "";
	internalDatabase = new map<string, Card>;
}

CardDatabase::CardDatabase(string dbFName) {
	_dbFileName = dbFName;
	internalDatabase = new map<string, Card>;
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

}