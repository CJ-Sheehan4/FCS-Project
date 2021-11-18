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