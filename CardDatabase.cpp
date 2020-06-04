#include "CardDatabase.h"

#include "stdio.h"
#include <iostream>
#include <fstream>

using namespace std;

CardDatabase::CardDatabase() {
	_dbFileName = "";
}

CardDatabase::CardDatabase(string dbFName) {
	_dbFileName = dbFName;
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
		}
		dbFile.close();
	} else {
		cout << "Unable to open file " << _dbFileName << endl;
		return false;
	}
	return true;
}