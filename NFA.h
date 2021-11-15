/*
	TASK #23 - Define a data type to represent NFAs.
*/
#ifndef NFA_H
#define NFA_H
#include <iostream>
#include <functional>
#include <list>
using namespace std;

template<typename State, typename C>
class NFA {
public:
	//constructor
	NFA(function<bool(State)> initQ, State initq0, function<list<State>(State, C)> initD1, 
		function<list<State>(State)> initD2, function<bool(State)> initF);
	//bool accept(list<int> str);
	//fields
	function<bool(State)> Q;			// function pointer representing the set of states
	State q0;					// q0 is of type State and holds the first state of the DFA
	function<list<State>(State, C)> d1;
	function<list<State>(State)> d2;// function pointer representing the delta function
	function<bool(State)> F;			// function pointer representing the set of accepting states
};
#endif