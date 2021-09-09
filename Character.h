#pragma once
class Character {
public:
	Character();
	Character(int initRepVal);
	int getCharacter();
	void setCharacter(int setRepVal);
	void print();
private:
	// this is a integer value that represemnmts the actual 
	// abstract value of the character
	int repVal;
};