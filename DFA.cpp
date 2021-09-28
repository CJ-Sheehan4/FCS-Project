#include <iostream>
#include "DFA.h"
using namespace std;

//constructor
template<typename State, typename C>
DFA<State,C>::DFA(bool (*Q_ptr)(State), State initq0, 
	State(*d_ptr)(State, C), bool (*F_ptr)(State)) { 
	Q = Q_ptr;
	q0 = initq0;
	d = d_ptr;
	F = F_ptr;
}