#include <iostream>
#include <functional>
#include <list>
#include "DFA.h"
#include "DFA.cpp"
using namespace std;
template<typename State, typename Str>
class Config {
public:
	Config() : curS('A'), curStr({0}) {}
	Config(State si, Str stri) : curS(si), curStr(stri) {}
	void printStr(void) {
		for (auto i : curStr) {
			cout << i;
		}
	};
	//public fields
	State curS;
	Str curStr;
};

list<list<int>> getLayer(list<int> sigma, int N);
list<int> lexi(list<int> sigma, int N);
void printLayer(list<list<int>> layer);
void printElement(list<int> element);
//DFA<char, int> *onlyCharFunc(int c);
template<typename State, typename C>
void update(DFA<char, int> dfa, Config<State, C>& cfg);
DFA<char, int> onlyChar(int c);
void runFullConfig(DFA<char, int>& dfa, list<int> str);


int main() {
	//Task #1
	list<int> sigma = { 0,1 };	// -1 represents epsilon, the alphabet consists of positive integers, including 0

	//Task #2 - using a list to represent a string (e.g. list<int> str = {0,1,2,99,-1}); 

	list<list<int>> layerOne = getLayer(sigma, 2);
	printLayer(layerOne);
	cout  << endl;
	list<int> element = lexi(sigma, 6);
	printElement(element);
	
	//testing DFA setters
	DFA<char, int>* test = new DFA<char, int>(
		[](char s) {return s == 'A'; },
		'A',
		[](char s, int c) {return s; },
		[](char s) {return s == 'A'; }
		);
	cout << endl << "Test DFA setters: " << endl;
	test->setQ([](char s) {return s == 'B'; });
	test->setd([](char s, int c) {return 'B'; });
	test->setF([](char s) {return s == 'B'; });
	if (!(test->Q('B'))) {
		cout << "Q fail";
	}
	else if (test->d('B', 1) != 'B') {
		cout << "d fail";
	}
	else if (!(test->F('B'))) {
		cout << "F fail";
	}
	
	cout << endl;
	//DFA that accepts no strings
	DFA<char, int>* noStr = new DFA<char, int>(
		[](char s) {return s == 'A'; },
		'A',
		[](char s, int c) {return 'A'; },
		[](char s) {return false; }
		);
	//DFA that only accepts empty string
	DFA<char, int>* onlyEmpty = new DFA<char, int>(
		[](char s) {return (s == 'A') || (s == 'B'); },
		'A',
		[](char s, int c) {
			if (s == 'A' && c != -1)
				return 'B';
			else if (s == 'B')
				return 'B';
			else
				return 'A';
		},
		[](char s) {return s == 'A'; }
		);
	//DFA that only takes strings of even length
	DFA<char, int>* onlyEven = new DFA<char, int>(
		[](char s) {return (s == 'A') || (s == 'B'); },
		'A',
		[](char s, int c) {
			if ((c == 1 || c == 0) && s == 'A')
				return 'B';
			else
				return 'A';
		},
		[](char s) {return s == 'A'; }
		);

	//testing DFA's with update
	list<int> str = {1,1,0,0,0,0,0,0,0,0,-1};
	list<int> str1 = {1,-1};
	runFullConfig(*onlyEven, str);
	cout << endl;
	DFA<char, int> onlyCharDFA = onlyChar(1);
	runFullConfig(onlyCharDFA, str1);
	return 0;
}
list<list<int>> getLayer(list<int> sigma, int N) {
	list<int>::iterator i;
	list<list<int>>::iterator j;
	list<int>::iterator sigmaIt;
	list<list<list<int>>> uniLayers;
	list<list<int>> newLayer;
	list<list<int>> layer;
	list<int>temp;
	list<int> epsilon = { -1 };
	int count = 0;
	layer.push_back(epsilon);
	uniLayers.push_back(layer);
	
	while (count <= N) {
		if (count == 1) {
			layer.clear();
			for (i = sigma.begin(); i != sigma.end(); i++) { //first push in layer one of all character in sigma
				temp.push_back(*i);
				layer.push_back(temp);
				temp.clear();
			}
			uniLayers.push_back(layer);
		}
		else if(count > 1){	//then it looks at previous layer to determin next
			layer.clear();
			layer = uniLayers.back();
			for (sigmaIt = sigma.begin(); sigmaIt != sigma.end(); sigmaIt++) {
				for (j = layer.begin(); j != layer.end(); j++) {
					for (i = j->begin(); i != j->end(); i++) {
						temp.push_back(*i);
					}
					temp.push_front(*sigmaIt); // pushes elemeent to front 
					newLayer.push_back(temp); 
					temp.clear();
				}
			}
			uniLayers.push_back(newLayer);	//returns the last element of the total layers, being the layer you want
			newLayer.clear();
		}
		count++;
	}
	return uniLayers.back();
}

void printLayer(list<list<int>> layer) {
	list<list<int>>::iterator rowIt;
	list<int>::iterator columnIt;
	for (rowIt = layer.begin(); rowIt != layer.end(); rowIt++) {
		cout << "{";
		for (columnIt = rowIt->begin(); columnIt != rowIt->end(); columnIt++) {
			cout << *columnIt;
			if (columnIt == --rowIt->end()) {
				break;
			}
			else {
				cout << ", ";
			}
		}
		cout << "}";
	}
}

list<int> lexi(list<int> sigma, int N) {
	list<int> strElement;
	list<list<int>> layerN;
	list<list<int>>::iterator it;
	int i = 0;
	bool found = false;
	while (!found) {
		layerN = getLayer(sigma, i); // get layer i, 
		int size = layerN.size();
		if (N >= size) { //if element is >= to the size of layer, subtract size from the n
			N = N - size;
		}
		else {
			it = layerN.begin();
			while (N > 0) {		//count from the beginning of that layer until element found
				N--;
				it++;
			}
			strElement = *it;
			found = true;
		}
		i++;
	}
	return strElement;
}
void printElement(list<int> element) {
	list<int>::iterator i;
	cout << "Element: {";
	for (i = element.begin(); i != element.end(); i++) {
		cout << *i;
	}
	cout << "}";
}/*
DFA<char, int>* onlyCharFunc(int c) {
	char s = 'A';
	
	DFA<char, int>* onlyChar = new DFA<char, int>(
		[](char s) {return (s == 'A') || (s == 'B') || (s == 'C'); },
		'A',
		[](char s, int curC) {
			if (curC == 1)
				return 'Z';
		},
		[](char s) {return s == 'B'; }
	);
	return onlyChar;
}
*/
template<typename State, typename C>
void update(DFA<char, int> dfa, Config<State, C>& cfg) {
	list<int>::iterator i = cfg.curStr.begin();
	cfg.curS = dfa.d(cfg.curS, *i);
	cfg.curStr.pop_front();
	
}
DFA<char, int> onlyChar(int c) {
	//onlyChar
	DFA<char, int> onlyCharDFA(
		[](char curS) {return ((curS == 'A') || (curS == 'B') || (curS == 'C')); },
		'A',
		[c](char curS, int curC) { 
			if (curS == 'A' && curC == c)
				return 'B';
			else 
				return 'C';
		} ,
		[](char curS) {return curS == 'B'; }
	);
	return onlyCharDFA;
}
void runFullConfig(DFA<char,int> &dfa, list<int> str) {
	Config<char, list<int>> config(dfa.q0, str);
	cout << '[' << config.curS << ']';
	config.printStr();
	while (config.curStr.front() != -1) {
		update(dfa, config);
		cout << '[' << config.curS << ']';
		config.printStr();
	}
	if (!(dfa.F(config.curS))) {
		cout << endl << "Does not accept!" << endl;
	}
}