/*
	TASK #28 - Define a data type to represent trace trees.
*/
#ifndef TT_H
#define TT_H
#include <iostream>
#include <functional>
#include <list>
#include <utility>
#include <memory>
using namespace std;

template<typename State, typename C>
class TT {
public:
	// default
	TT();
	// constructor
	TT(State initBranch, function<list<State>(State, C)> mC, function<list<State>(State)>mE);
	// helper
	list<shared_ptr<TT<State, C>>> push(list<list<State>> next);
	void printTreeL(void);
	list<shared_ptr<TT<State, C>>> createTreeL(C c);
	list<list<shared_ptr<TT<State, C>>>> nextLayer(C c);
	// fields
	State branch;
	pair<function<list<State>(State, C)>, function<list<State>(State)>> d;
	list<shared_ptr<TT<State, C>>> treeL;
	bool accept;
	bool reject;
};
#endif