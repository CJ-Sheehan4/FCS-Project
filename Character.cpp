#include <iostream>
#include "Character.h"
using std::cout;
Character::Character() {
	repVal = 0;
}
Character::Character(int initRepVal) {
	repVal = initRepVal;
}
int Character::getCharacter() {
	return repVal;
}
void Character::setCharacter(int setRepVal) {
	repVal = setRepVal;
}
void Character::print() {
	cout << repVal << " ";
}