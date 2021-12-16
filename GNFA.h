
/*
	TASK #51 - Define a data type to represent GNFAs
*/
#ifndef GNFA_H
#define GNFA_H
#include <iostream>
#include <functional>
#include <list>
#include "RX.h"
using namespace std;

template<typename State, typename C>
class GNFA {
public:
	//constructor
	GNFA(function<bool(State)> initQ, list<int>initSigma, function<RX<State, C>* (State, State)> initD,
		State iqstart, State iqaccept) : Q(initQ), sigma(initSigma), d(initD), qstart(iqstart), qaccept(iqaccept){}
	//fields
	function<bool(State)> Q;
	list<int> sigma;					
	function<RX<State,C>*(State,State)> d;
	State qstart;
	State qaccept;
};
#endif