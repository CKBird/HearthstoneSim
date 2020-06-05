#include "Card.h"
#include "CardDatabase.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	//Card hMinion(card_type::minion, class_name::hunter);

	//Minion hMinion2(class_name::hunter, 5, 3, 2, "Starving Buzzard", "when you summon a beast, draw a card.");
	//hMinion2.printInfo();

	cout << "Creating card database from file hsdataoutput.txt" << endl;
	string fName("hsdataoutput.txt");
	CardDatabase* cd = new CardDatabase(fName);
	cd->createCardDatabaseFromFile();

	cout << "Finished..." << endl;

	cd->printInfo();

	cout << "Attempting to find card Battlefiend..." << endl;

	cd->getCard("Battlefiend")->printInfo();

	return 1;
}