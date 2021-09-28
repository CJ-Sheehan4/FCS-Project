#ifndef DFA_H
#define DFA_H
#include <iostream>
#include <list>
using namespace std;

template<typename State, typename C>
class DFA {
public:
	//constructor
	DFA(bool (*Q_ptr)(State), State initq0, State(*d_ptr)(State, C), bool (*F_ptr)(State));
	void setQ(bool (*Q_ptr)(State)) { Q = Q_ptr; };
	void setq0(State initq0) { q0 = initq0; };
	void setd(State(*d_ptr)(State, C)) { d = d_ptr; };
	void setF(bool (*F_ptr)(State)) { F = F_ptr; };
	//fields
	bool (*Q)(State);			// function pointer representing the set of states
	State q0;					// q0 is of type State and holds the first state of the DFA
	State (*d)(State, C);	// function pointer representing the delta function
	bool (*F)(State);			// function pointer representing the set of accepting states
};
#endif