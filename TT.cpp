#include <iostream>
#include <functional>
#include <list>
#include <utility>
#include "TT.h"
using namespace std;
template<typename State, typename C>
TT<State, C>::TT() {
	branch = -1;
	treeL = {};
}
template<typename State, typename C>
TT<State, C>::TT(State initBranch, function<list<State>(State, C)>mC, function<list<State>(State)>mE){
	branch = initBranch;
	pair< function<list<State>(State, C)>, function<list<State>(State)>> p1(mC, mE);
	pair<pair<function<list<State>(State, C)>, function<list<State>(State)>>, TT<State, C>*> temp;
	temp.first = p1;
	temp.second = nullptr;
	treeL.push_back(temp);
	accept = false;
	reject = false;
}