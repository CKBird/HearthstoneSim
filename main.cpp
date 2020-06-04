#include "Card.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	cout << "Creating generic 'Card'..." << endl;
	Card hMinion(card_type::minion, class_name::hunter);

	cout << "The card type is: " << hMinion.getType() << " and the class is: " << hMinion.getClassName() << endl;

	cout << "Creating Minion Card ..." << endl;

	Minion hMinion2(class_name::hunter, 5, 3, 2, "Starving Buzzard", "when you summon a beast, draw a card.");
	hMinion2.printInfo();



	return 1;
}