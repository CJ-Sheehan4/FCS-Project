#include <iostream>
#include <functional>
#include <string>
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
	// 1. DFA that accepts no strings
	DFA<char, int>* noStr = new DFA<char, int>(
		[](char s) {return s == 'A'; },
		'A',
		[](char s, int c) {return 'A'; },
		[](char s) {return false; }
		);
	// 2. DFA that only accepts empty string
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
	// 3. DFA that only takes strings of even length
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
	// 4. DFA for strings of only zeros
	DFA<char, int>* onlyZeros = new DFA<char, int>(
		[](char s) {return (s == 'A') || (s == 'B') || (s == 'C'); },
		'A',
		[](char s, int c) {
			if ((c == 0) && (s == 'A' || s == 'B'))
				return 'B';
			else
				return 'C';
		},
		[](char s) {return s == 'B'; }
		);
	// 5. DFA that only accepts the string of my name "CJ"
	DFA<string, char>* myName = new DFA<string, char>(
		[](string s) {return (s == "A") || (s == "B") || (s == "C") || (s == "FAIL"); },
		"A",
		[](string s, char c) {
			if ((c == 'C') && (s == "A"))
				return "B";
			else if ((c == 'J') && (s == "B"))
				return "C";
			else
				return "FAIL";
		},
		[](string s) {return s == "C"; }
		);
	// 6. DFA that only accepts strings that are not my name
	DFA<char, char>* notMyName = new DFA<char, char>(
		[](char s) {return (s == 'A') || (s == 'B') || (s == 'C'); },
		'A',
		[](char s, char c) {
			if ((c == 'C') && (s == 'A'))
				return 'B';
			else if ((c != 'C') && (s == 'A'))
				return 'A';
			else if ((c == 'J') && (s == 'B'))
				return 'C';
			else if ((c != 'J') && (s == 'B'))
				return 'A';
			else if (s == 'C')
				return 'A';
		},
		[](char s) {return s == 'A'; }
		);
	// 7. DFA that only reads a string thats a comment line
	DFA<string, char>* comments = new DFA<string, char>(
		[](string s) {return (s == "A") || (s == "B") || (s == "C") || (s == "FAIL"); },
		"A",
		[](string s, char c) {
			if ((c == '/') && (s == "A"))
				return "B";
			else if ((c == '/') && (s == "B"))
				return "C";
			else if (s == "C")
				return "C";
			else
				return "FAIL";
		},
		[](string s) {return s == "C"; }
		);
	// 8. DFA that only takes strings with the sequence "01" anywehre in the string
	// e.g. "00011111" accepts, "111100000" does not accept
	DFA<char, int>* zeroOne = new DFA<char, int>(
		[](char s) {return (s == 'A') || (s == 'B') || (s == 'C'); },
		'A',
		[](char s, int c) {
			if ((c == 0) && (s == 'A'))
				return 'B';
			else if ((c == 1) && (s == 'A'))
				return 'A';
			else if ((c == 0) && (s == 'B'))
				return 'B';
			else if ((c == 1) && (s == 'B'))
				return 'C';
			else if (s == 'C')
				return 'C';
		},
		[](char s) {return s == 'C'; }
		);
	// 9. DFA representing a traffic light
	//the states are green, yellow, and red
	// the characters are 0 and 1. 0 representing that the time has not elapsed for
	//the light to change, and 1 representing that the time has elapsed for the light to change
	//I'll say that the accept state is green. Theres also no start state, but I'll say its green so the DFA works
	DFA<char, int>* trafficLight = new DFA<char, int>(
		[](char s) {return (s == 'G') || (s == 'Y') || (s == 'R'); },
		'G',
		[](char s, int c) {
			if (s == 'G' && c == 0)
				return 'G';
			else if (s == 'G' && c == 1)
				return 'Y';
			else if (s == 'Y' && c == 0)
				return 'Y';
			else if (s == 'Y' && c == 1)
				return 'R';
			else if (s == 'R' && c == 0)
				return 'R';
			else if (s == 'R' && c == 1)
				return 'G';
		},
		[](char s) {return false; }
		);
	//10. argh
	DFA<char, char>* argh = new DFA<char, char>(
		[](char s) {return (s == 'A') || (s == 'B') || (s == 'C') || (s == 'D') || (s == 'E') || (s == 'F'); },
		'A',
		[](char s, char c) {
			if (s == 'A' && c == 'a')
				return 'B';
			else if (s == 'B' && c == 'a')
				return 'B';
			else if (s == 'B' && c == 'r')
				return 'C';
			else if (s == 'C' && c == 'r')
				return 'C';
			else if (s == 'C' && c == 'g')
				return 'D';
			else if (s == 'D' && c == 'g')
				return 'D';
			else if (s == 'D' && c == 'h')
				return 'E';
			else if (s == 'E' && c == 'h')
				return 'E';
			else
				return 'F';
		},
		[](char s) {return s == 'E'; }
		);
	//11. only accpets strings of signed binary numbers
	DFA<char, int>* signedBinary = new DFA<char, int>(
		[](char s) {return (s == 'A') || (s == 'B') || (s == 'C'); },
		'A',
		[](char s, int c) {
			if (s == 'A' && c == 1)
				return 'B';
			else if (s == 'A' && c == 0)
				return 'C';
			else if (s == 'B')
				return 'B';
			else if (s == 'C')
				return 'C';
		},
		[](char s) {return s == 'B'; }
		);
	// 12. DFA that creates accepts exactly one character
	list<int> str1 = { 1,-1 };
	DFA<char, int> onlyCharDFA = onlyChar(1);
	// testing update rule on DFA's
	list<int> str = {1,1,0,0,0,0,0,0,0,0,-1};
	runFullConfig(onlyCharDFA, str1);
	cout << endl << endl;
	runFullConfig(*onlyEven, str);
	cout << endl << endl;
	
	
	// testing myName DFA if it accepts my name
	if(!(myName->F(myName->d(myName->d("A", 'C'), 'J')))) {
		cout << "Does not accept string in DFA myName" << endl;
	}
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
}
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