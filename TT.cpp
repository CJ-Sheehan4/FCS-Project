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
TT<State, C>::TT(State initBranch, function<list<State>(State, C)>mC, function<list<State>(State)>mE, list<int> initStr) {
	branch = initBranch;
	d.first = mC;
	d.second = mE;
	accept = false;
	reject = false;
	curStr = initStr;
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
list<shared_ptr<TT<State, C>>> TT<State, C>::push2(pair<list<State>, list<State>> next) {
	list<int> tempStr = this->curStr;
	if (!tempStr.empty()) {
		tempStr.pop_front();
	}
	
	for (auto i : next.first) {
		treeL.push_back(make_shared<TT<int, int>>(i, d.first, d.second, tempStr));
	}
	for (auto i : next.second) {
		treeL.push_back(make_shared<TT<int, int>>(i, d.first, d.second, curStr));
	}
	return this->treeL;
}
template<typename State, typename C>
void TT<State, C>::printTreeL(void) {
	for (auto i : treeL) {
		cout << i->branch << "-";
		i->printCurStr();
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
void TT<State, C>::printCurStr(void) {
	for (auto i : this->curStr)
		cout << i;
	cout << " ";
}