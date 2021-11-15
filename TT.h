/*
	TASK #28 - Define a data type to represent trace trees.
*/
#ifndef TT_H
#define TT_H
#include <iostream>
#include <functional>
#include <list>
#include <utility>
using namespace std;

template<typename State, typename C>
class TT {
public:
	// default
	TT();
	//constructor
	TT(State initBranch, function<list<State>(State, C)> mC, function<list<State>(State)>mE);
	State branch;
	list<pair<pair<function<list<State>(State, C)>, function<list<State>(State)>>, TT<State, C>*>> treeL;
	bool accept;
	bool reject;
};
#endif