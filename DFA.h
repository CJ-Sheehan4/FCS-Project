#ifndef DFA_H
#define DFA_H
#include <iostream>
#include <functional>
#include <list>
using namespace std;

template<typename State, typename C>
class DFA {
public:
	//constructor
	DFA(function<bool(State)> initQ, State initq0, function<State(State, C)> initD, function<bool(State)> initF);
	//setters
	void setQ(function<bool(State)>QSet) { Q = QSet; };
	void setq0(State q0Set) { q0 = q0Set; };
	void setd(function<State(State, C)>DSet) { d = DSet; };
	void setF(function <bool(State)>FSet) { F = FSet; };
	bool accept(list<int> str);
	//fields
	function<bool(State)> Q;			// function pointer representing the set of states
	State q0;					// q0 is of type State and holds the first state of the DFA
	function<State(State, C)> d;		// function pointer representing the delta function
	function<bool(State)> F;			// function pointer representing the set of accepting states
};
#endif