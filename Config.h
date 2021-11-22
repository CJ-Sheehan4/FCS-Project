#ifndef CONFIG_H
#define CONFIG_H
#include <iostream>
#include <functional>
#include <list>
using namespace std;

template<typename State>
class Config {
public:
	Config() { curS = -1; curStr.push_back(-1); }
	Config(State si, list<int> stri) : curS(si), curStr(stri) {}
	void printStr(void) {
		for (auto i : curStr) {
			cout << i;
		}
	};
	//public fields
	State curS;
	list<int> curStr;
};
#endif
