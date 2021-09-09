#include <iostream>
#include <vector>
#include "Character.h"
using namespace std;

int main() {
	
	Character cOne(1);
	Character cTwo(2);
	Character cThree(3);

	cout << "Test: constructors" << endl;
	vector<Character> alphabet = {Character(), cOne, cTwo, cThree};
	int size = alphabet.size();
	for (int i = 0; i < size; i++) {
		alphabet[i].print();
	}

	cout << endl << "Test: getter" << endl;
	int firstVal = alphabet[0].getCharacter();
	cout << firstVal << endl;
	cout << "Test: setter" << endl;
	alphabet[0].setCharacter(9);
	cout << alphabet[0].getCharacter() << endl;
	

	return 0;
}
