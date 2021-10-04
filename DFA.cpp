#include <iostream>
#include <functional>
#include "DFA.h"
using namespace std;

//constructor
template<typename State, typename C>
DFA<State,C>::DFA(bool (*Q_ptr)(State), State initq0, 
	function<State(State, C)> initD, bool (*F_ptr)(State)) { 
	Q = Q_ptr;
	q0 = initq0;
	d = initD;
	F = F_ptr;
}