#include <iostream>
#include <functional>
#include "NFA.h"
using namespace std;

//constructor
template<typename State, typename C>
NFA<State, C>::NFA(function<bool(State)> initQ, State initq0, function<list<State>(State, C)> initD1,
	function<list<State>(State)> initD2, function<bool(State)> initF) {
	Q = initQ;
	q0 = initq0;
	d1 = initD1;
	d2 = initD2;
	F = initF;
}
// Task 10 - accepts function
template<typename State, typename C>
bool NFA<State, C>::accept(list<int> str) {
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