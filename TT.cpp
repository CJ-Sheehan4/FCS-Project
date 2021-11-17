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
	d.first = mC;
	d.second = mE;
	accept = false;
	reject = false;
}
template<typename State, typename C>
list<shared_ptr<TT<State, C>>> TT<State, C>::push(list<list<State>> next) {
	for (auto i : next) {
		for (auto j : i) {
			this->treeL.push_back(make_shared<TT<int, int>>(j, this->d.first, this->d.second));

		}
	}
	return this->treeL;
}
template<typename State, typename C>
void TT<State, C>::printTreeL(void) {
	for (auto i : treeL) {
		cout << i->branch;
	}
}
template<typename State, typename C>
list<shared_ptr<TT<State, C>>> TT<State, C>::createTreeL(C c) {
	list<list<int>> next;
	list<shared_ptr<TT<State, C>>> ret;
	next.push_back(d.first(branch, c));
	next.push_back(d.second(branch));
	ret = this->push(next);
	next = {};
	return ret;
}
template<typename State, typename C>
list<list<shared_ptr<TT<State, C>>>> TT<State, C>::nextLayer(C c) {
	list<list<int>> next;
	list<list<shared_ptr<TT<State, C>>>> ret;
	for (auto i : treeL) {
		next.push_back(i->d.first(i->branch, c));
		next.push_back(i->d.second(i->branch));
		ret.push_back(i->push(next));
		next = {};
	}
	return ret;
}