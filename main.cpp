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
	cout << "The name is: " << hMinion2.getName() << endl;
	cout << "The card type is: " << hMinion2.getType() << endl;
	cout << "The class name is: " << hMinion2.getClassName() << endl;
	cout << "The cost is: " << hMinion2.getCost() << endl;
	cout << "The attack is: " << hMinion2.getAtk() << endl;
	cout << "The health is: " << hMinion2.getHealth() << endl;
	cout << "The effect is: " << hMinion2.getEffect() << endl;



	return 1;
}