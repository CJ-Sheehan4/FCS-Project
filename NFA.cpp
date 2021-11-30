#include <iostream>
#include <functional>
#include "NFA.h"
#include "Config.h"
using namespace std;

//constructor
template<typename State, typename C>
NFA<State, C>::NFA(function<bool(State)> initQ, State initq0, function<list<State>(State, C)> initD1,
	function<list<State>(State)> initD2, function<bool(State)> initF) {
	Q = initQ;
	q0 = initq0;
	d1 = initD1;
	d2 = initD2;
	F = initF;
}
/*
	32 - (Backtracking) Write a function that given an NFA and a string, determines if the string is accepted.
*/

template<typename State, typename C>
bool NFA<State, C>::accepts(list<int> w) {
	list<Config<State>> v;
	list<Config<State>> p = { Config<State>(this->q0, w) };
	list<State> tempStateList;
	
	while (!p.empty()) {
		Config<State> qi(p.front().curS, p.front().curStr);
		p.pop_front();
		if ((qi.curStr.empty()) && (F(qi.curS))) {
			return true;
		}
		tempStateList = d2(qi.curS);
		for (auto i : tempStateList) {
			Config<State> qj(i, qi.curStr);
			if (!findConfig(v, qj)) {
				p.push_back(qj);
				v.push_back(qj);
			}
		}
		if (!qi.curStr.empty()) {
			tempStateList = d1(qi.curS, qi.curStr.front());
			if (!tempStateList.empty()) {
				qi.curStr.pop_front();
				for (auto i : tempStateList) {
					Config<State> qj(i, qi.curStr);
					if (!findConfig(v, qj)) {
						p.push_back(qj);
						v.push_back(qj);
					}
				}
			}
		}
		
	}
	return false;
}
// helper function for task 32
template<typename State, typename C>
bool NFA<State, C>::findConfig(list<Config<State>> cL, Config<State> key) {
	for (auto i : cL) {
		if ((i.curS == key.curS) && (i.curStr == key.curStr)) {
			return true;
		}
	}
	return false;
}