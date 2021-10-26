#include <iostream>
#include <functional>
#include "DFA.h"
using namespace std;

//constructor
template<typename State, typename C>
DFA<State,C>::DFA(function<bool(State)> initQ, State initq0,
	function<State(State, C)> initD, function<bool(State)> initF) { 
	Q = initQ;
	q0 = initq0;
	d = initD;
	F = initF;
}
// Task 10 - accepts function
template<typename State, typename C>
bool DFA<State,C>::accept(list<int> str) {
	list<int>::iterator it;
	State curS = this->q0;
	for (it = str.begin(); it != str.end(); it++) {
		curS = this->d(curS, *it);
	}
	if (this->F(curS))
		return true;
	else
		return false;
}