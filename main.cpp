#include <iostream>
#include <functional>
#include <string>
#include <list>
#include <utility>
#include <optional>
#include <algorithm>
#include <typeinfo>
#include "DFA.h"
#include "DFA.cpp"

using namespace std;
template<typename State>
class Config {
public:
	Config() : curS(0), curStr({0}) {}
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
// function declarations
list<list<int>> getLayer(list<int> sigma, int N);
list<int> lexi(list<int> sigma, int N);
void printLayer(list<list<int>> layer);
void printElement(list<int> element);
template<typename State, typename C>
Config<State> update(DFA<State, C> *dfa, Config<State> cfg);
DFA<int, int> *onlyChar(int c);
template<typename State, typename C>
list<Config<State>> trace(DFA<State, C>* dfa, list<int> str);
template<typename State>
void printConfigList(list<Config<State>>& TL);
void printConfigList_pair(list<Config<pair<int, int>>>& TL);
void testDFA(DFA<int, int>* dfa, string DFAName, bool noAccepts, bool allAccepts, 
	list<list<int>> accepts, list<list<int>> nAccepts);
pair<bool, list<int>> wouldBeAccept(DFA<int, int>*dfa, list<int> sigma);
void testWouldBeAccept(pair<bool, list<int>> dfaPairStr);
template<typename State, typename C>
DFA<State, C>* complement(DFA<State, C> dfa);
template<typename State, typename State2, typename C>
DFA<pair<State, State2>, C>* unionDFA(DFA<State, C> A, DFA<State2, C> B);
template<typename State1, typename State2, typename C>
void testUnion(DFA<pair<State1, State2>, C>* dfa, string DFAName, bool noAccepts, bool allAccepts, 
	list<list<int>> strL);
int main() {
	list<int> englishAlpha = { '/', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
		'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	list<int> binaryAlpha = { 0, 1 };
	list<int> zeroNineAlpha = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	//Task #1
	//list<int> sigma = { 0, 1 } ;	// the alphabet
	//Task #2 - using a list to represent a string (e.g. list<int> str = {0,1,2,99,-1}); 
	/*
	list<list<int>> layerOne = getLayer(sigma, 2);
	printLayer(layerOne);
	cout  << endl;
	list<int> element = lexi(sigma, 6);
	printElement(element);
	*/

	// DFA that accepts no strings
	DFA<int, int>* noStr = new DFA<int, int>(
		[](int s) {return s == 0; },
		0,
		[](int s, int c) {return 0; },
		[](int s) {return false; }
	);
	testDFA(noStr, "No String", true, false,
		{ {} },
		{ { 0, 0, 0 }, { 1 }, { 1, 2, 3 }, { 1, 2, 3, 4, 5 }, { 1, 2, 3, 4, 5, 6, 7 }, { 1, 1, 1, 1, 1, 1 } }
	);
	testWouldBeAccept(wouldBeAccept(noStr, zeroNineAlpha));
	cout << endl;

	// DFA that only accepts empty string
	DFA<int, int>* onlyEmpty = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1); },
		0,
		[](int s, int c) {
			if (s == 0)
				return 1;
			else
				return 1;
		},
		[](int s) {return s == 0; }
		);
	testDFA(onlyEmpty, "Only Empty Str", false, false,
		{ { } },
		{ { 0, 0, 0 }, { 1 }, { 1, 2, 3 }, { 1, 2, 3, 4, 5 }, { 1, 2, 3, 4, 5, 6, 7 }, { 1, 1, 1, 1, 1, 1, 1, 1 } }
	);
	testWouldBeAccept(wouldBeAccept(onlyEmpty, zeroNineAlpha));
	cout << endl;

	// DFA that only takes strings of even length
	DFA<int, int>* onlyEven = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1); },
		0,
		[](int s, int c) {
			if (s == 0)
				return 1;
			else
				return 0;
		},
		[](int s) {return s == 0; }
		);
	testDFA(onlyEven, "Only Even", false, false,
		{ { 0,1 }, { 0,0 }, { 1,1 }, { 1,2,3,4 }, { 1,2,3,4,5,6 }, { 1,1,1,1,1,1,1,1 } },
		{ { 0,0,0 }, { 1 }, { 1,2,3 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 } }
	);
	testWouldBeAccept(wouldBeAccept(onlyEven, zeroNineAlpha));
	cout << endl;

	// DFA for strings of only zeros
	DFA<int, int>* onlyZeros = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2); },
		0,
		[](int s, int c) {
			if ((c == 0) && (s == 0 || s == 1))
				return 1;
			else
				return 2;
		},
		[](int s) {return s == 1; }
		);
	testDFA(onlyZeros, "Only Zero's", false, false,
		{ { 0 }, { 0, 0 }, { 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } },//accepts
		{ { }, { 1 }, { 0, 0, 0, 1 }, { 1, 2, 3, 4, 5 }, { 1, 2, 3, 4, 5, 6, 7 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1 } }//does not accept
	);
	testWouldBeAccept(wouldBeAccept(onlyZeros, zeroNineAlpha));
	cout << endl;

	// DFA that only accepts the string of my name "CJ"
	DFA<int, int>* myName = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3); },
		0,
		[](int s, int c) {
			if ((c == 67) && (s == 0))
				return 1;
			else if ((c == 74) && (s == 1))
				return 2;
			else
				return 3;
		},
		[](int s) {return s == 2; }
		);
	testDFA(myName, "My name", false, false,
		{ { 'C', 'J' }, { 67,74 } },	//accepts
		{ { }, { 1 }, { 0,0,0,1 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 } }
	);
	testWouldBeAccept(wouldBeAccept(myName, englishAlpha));
	cout << endl;

	// DFA that only accepts strings that are not my name
	DFA<int, int>* notMyName = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3); },
		0,
		[](int s, int c) {
			if ((c == 67) && (s == 0))
				return 1;
			else if ((c != 67) && (s == 0))
				return 0;
			else if ((c == 74) && (s == 1))
				return 2;
			else if ((c != 74) && (s == 1))
				return 0;
			else if ((s == 2))
				return 3;
			else if (s == 3)
				return 3;
		},
		[](int s) {return s == 0 || s == 1 || s == 3; }
		);
	testDFA(notMyName, "Not My Name", false, false,
		{ { }, { 1 }, { 0,0,0,1 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 } },
		{ { 'C', 'J' }, { 67,74 } }
	);
	testWouldBeAccept(wouldBeAccept(notMyName, englishAlpha));
	cout << endl;

	// DFA that only reads a string that's a comment line
	DFA<int, int>* comments = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3); },
		0,
		[](int s, int c) {
			if ((c == 47) && (s == 0))
				return 1;
			else if ((c == 47) && (s == 1))
				return 2;
			else if (s == 2)
				return 2;
			else
				return 3;
		},
		[](int s) {return s == 2; }
		);
	testDFA(comments, "Comments", false, false,
		{ { '/','/' }, { '/','/' , 'A'}, {'/','/','C', 'J'}, {'/','/', 'y','a'},
			{'/', '/' , 'A', 'B', 'C' }, {'/','/', 5, 6, 'y'} },
		{ { }, { '/', 1 }, { 0,0,0,1 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 } }
	);
	testWouldBeAccept(wouldBeAccept(comments, englishAlpha));
	cout << endl;

	// DFA that only takes strings with the sequence "01" anywehre in the string
	// e.g. "00011111" accepts, "111100000" does not accept
	DFA<int, int>* zeroOne = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2); },
		0,
		[](int s, int c) {
			if ((c == 0) && (s == 0))
				return 1;
			else if ((c == 1) && (s == 0))
				return 0;
			else if ((c == 0) && (s == 1))
				return 1;
			else if ((c == 1) && (s == 1))
				return 2;
			else if (s == 2)
				return 2;
		},
		[](int s) {return s == 2; }
		);
	testDFA(zeroOne, "Zero One", false, false,
		{ { 0, 1 }, { 0,0,1,0 }, { 0,1,0,0,0,0,0 }, { 1,1,1,1,1,1,0,1 }, { 0,0,0,1,1,1,1,1 }, { 1,1,1,1,1,0,1,1,1 } },
		{ { }, { 1 }, { 1,1,1,0 }, { 1, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1 } }
	);
	testWouldBeAccept(wouldBeAccept(zeroOne, binaryAlpha));
	cout << endl;

	// DFA representing a traffic light
	// the states are green, yellow, and red
	// the characters are 0 and 1. 0 representing that the time has not elapsed for
	// the light to change, and 1 representing that the time has elapsed for the light to change
	// I'll say that the accept state is green. Theres also no start state, but I'll say its green so the DFA works
	DFA<int, int>* trafficLight = new DFA<int, int>(
		[](int s) {return (s == 'G') || (s == 'Y') || (s == 'R'); },
		'G',
		[](int s, int c) {
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
		[](int s) {return false; }
		);
	testDFA(noStr, "Traffic Light", true, false,
		{ { } },
		{ { 0,0,0 }, { 1 }, { 1, 1, 1}, { 1, 0, 1, 0, 1 }, { 1, 1, 1, 0, 0, 0}, { 0, 0, 1, 1} }
	);
	testWouldBeAccept(wouldBeAccept(trafficLight, binaryAlpha));
	cout << endl;

	// argh
	DFA<int, int>* ARGH = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3) || (s == 4) || (s == 5); },
		0,
		[](int s, int c) {
			if (s == 0 && c == 65) // 65 = A
				return 1;
			else if (s == 1 && c == 65)
				return 1;
			else if (s == 1 && c == 82) // 82 = R
				return 2;
			else if (s == 2 && c == 82)
				return 2;
			else if (s == 2 && c == 71) // 71 = G
				return 3;
			else if (s == 3 && c == 71)
				return 3;
			else if (s == 3 && c == 72) // 72 = H 
				return 4;
			else if (s == 4 && c == 72)
				return 4;
			else
				return 5;
		},
		[](int s) {return s == 4; }
		);
	testDFA(ARGH, "ARGH", false, false,
		{ { 'A','R','G','H' }, { 'A','R','R','G','H' }, { 'A','A','R','R','G','G','H','H' }, { 'A','R','G','G','H' },
			{ 'A','R','G','H','H' }, { 'A','A','A','R','R','R','G','G','G','H','H','H' } },
		{ { }, { 1 }, { 1,2,3,4,5 }, { 'A','R','G' }, { 'A','R','H','G' }, { 'O','K' } }
	);
	testWouldBeAccept(wouldBeAccept(ARGH, englishAlpha));
	cout << endl;

	// only accpets strings of signed binary numbers
	DFA<int, int>* signedBinary = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2); },
		0,
		[](int s, int c) {
			if (s == 0 && c == 1)
				return 1;
			else if (s == 0 && c == 0)
				return 2;
			else if (s == 1)
				return 1;
			else if (s == 2)
				return 2;
		},
		[](int s) {return s == 1; }
		);
	testDFA(signedBinary, "Signed Binary", false, false,
		{ { 1, 0 }, { 1,1,0 }, { 1,1,1,0 }, { 1,0,1,0,1,0 }, { 1,1,1,1,1,1 }, { 1,0,0,0,0,0 } },
		{ { }, { 0,1 }, { 0,0,0,1 }, { 0,1,1,1,1,1,1,1 }, { 0,1,0,0,0,0,0,0 }, { 0,0,1,1,1,0,0 } }
	);
	testWouldBeAccept(wouldBeAccept(signedBinary, binaryAlpha));
	cout << endl;

	// DFA that creates accepts exactly one character
	list<int> str1 = { 1 };
	DFA<int, int>* onlyCharDFA = onlyChar(1);
	testDFA(onlyCharDFA, "Only Char", false, false,
		{ { 1 } },
		{ { }, { 0,1 }, { 0,0,0,1 }, { 0,1,1,1,1,1,1,1 }, { 0,1,0,0,0,0,0,0 }, { 0,0,1,1,1,0,0 } }
	);
	testWouldBeAccept(wouldBeAccept(onlyCharDFA, binaryAlpha));
	cout << endl;
	/*
		Task #13 - testing all DFAs that are complements
	*/
	// ~noStr
	DFA<int, int>* cNoStr = complement(*noStr);
	testDFA(cNoStr, "~noStr", false, true,
		{ { }, { 0, 0, 0 }, { 1 }, { 1, 2, 3, 4 }, { 3, 2, 1 }, { 1, 2, 3, 4, 5, 6, 7 } },
		{ { } }
	);
	testWouldBeAccept(wouldBeAccept(cNoStr, zeroNineAlpha));
	cout << endl;
	// ~onlyEmpty
	DFA<int, int>* cOnlyEmpty = complement(*onlyEmpty);
	testDFA(cOnlyEmpty, "~onlyEmpty", false, false,
		{ { 0, 0, 0 }, { 1 }, { 1, 2, 3, 4 }, { 3, 2, 1 }, { 1, 2, 3, 4, 5, 6, 7 }, { 1, 1, 1, 1, 1, } },
		{ { } }
	);
	testWouldBeAccept(wouldBeAccept(cOnlyEmpty, zeroNineAlpha));
	cout << endl;
	//~onlyEven
	DFA<int, int>* cOnlyEven = complement(*onlyEven);
	testDFA(cOnlyEven, "~Only Even (odd)", false, false,
		{ { 0,0,0 }, { 1 }, { 1,2,3 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 } },
		{ { 0,1 }, { 0,0 }, { 1,1 }, { 1,2,3,4 }, { 1,2,3,4,5,6 }, { 1,1,1,1,1,1,1,1 } }
	);
	testWouldBeAccept(wouldBeAccept(cOnlyEven, zeroNineAlpha));
	cout << endl;
	// ~onlyZeros
	DFA<int, int>* cOnlyZeros = complement(*onlyZeros);
	testDFA(cOnlyZeros, "~onlyZeros", false, false,
		{ { }, { 1 }, { 0, 0, 0, 1 }, { 0, 2, 3, 4, 5 }, { 1, 2, 3, 4, 5, 6, 7 }, { 1, 0, 0, 0, 0, 0, 0, 0, 0 } },
		{ { 0 }, { 0, 0 }, { 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } }
	);
	testWouldBeAccept(wouldBeAccept(cOnlyZeros, zeroNineAlpha));
	cout << endl;
	// ~myName
	DFA<int, int>* cMyName = complement(*myName);
	testDFA(cMyName, "~myName", false, false,
		{ { }, { 1 }, { 0,0,0,1 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 } },
		{ { 'C', 'J' }, { 67,74 } }
	);
	testWouldBeAccept(wouldBeAccept(cMyName, englishAlpha));
	cout << endl;
	// ~notMyName
	DFA<int, int>* cNotMyName = complement(*notMyName);
	testDFA(cNotMyName, "~notMyName", false, false,
		{ { 'C', 'J' }, { 67,74 } },
		{ { }, { 1 }, { 0,0,0,1 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 } }
	);
	testWouldBeAccept(wouldBeAccept(cNotMyName, englishAlpha));
	cout << endl;
	// ~comments DFA
	DFA<int, int>* cComments = complement(*comments);
	testDFA(cComments, "~comments", false, false,
		{ { }, { '/', 1 }, { 0,0,0,1 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 } },
		{ { '/','/' }, { '/','/' , 'A'}, {'/','/','C', 'J'}, {'/','/', 'y','a'},
			{'/', '/' , 'A', 'B', 'C' }, {'/','/', 5, 6, 'y'} }
	);
	testWouldBeAccept(wouldBeAccept(cComments, englishAlpha));
	cout << endl;
	// ~zerOne
	DFA<int, int>* cZeroOne = complement(*zeroOne);
	testDFA(cZeroOne, "~zeroOne", false, false,
		{ { }, { 1 }, { 1,1,1,0 }, { 1, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1 } },
		{ { 0, 1 }, { 0,0,1,0 }, { 0,1,0,0,0,0,0 }, { 1,1,1,1,1,1,0,1 }, { 0,0,0,1,1,1,1,1 }, { 1,1,1,1,1,0,1,1,1 } }
	);
	testWouldBeAccept(wouldBeAccept(cZeroOne, binaryAlpha));
	cout << endl;
	// ~trafficLight
	DFA<int, int>* cTrafficLight = complement(*trafficLight);
	testDFA(cTrafficLight, "~trafficLight", false, true,
		{ { 0,0,0 }, { 1 }, { 1, 1, 1}, { 1, 0, 1, 0, 1 }, { 1, 1, 1, 0, 0, 0}, { 0, 0, 1, 1} },
		{ { } }
	);
	testWouldBeAccept(wouldBeAccept(cTrafficLight, englishAlpha));
	cout << endl;
	// ~ARGH
	DFA<int, int>* cARGH = complement(*ARGH);
	testDFA(cARGH, "~ARGH", false, false,
		{ { }, { 1 }, { 1,2,3,4,5 }, { 'A','R','G' }, { 'A','R','H','G' }, { 'O','K' } },
		{ { 'A','R','G','H' }, { 'A','R','R','G','H' }, { 'A','A','R','R','G','G','H','H' }, { 'A','R','G','G','H' },
			{ 'A','R','G','H','H' }, { 'A','A','A','R','R','R','G','G','G','H','H','H' } }
	);
	testWouldBeAccept(wouldBeAccept(cARGH, englishAlpha));
	cout << endl;
	// ~signedBinary
	auto* cSignedBinary = complement(*signedBinary);
	testDFA(cSignedBinary, "~signedBinary", false, false,
		{ { }, { 0,1 }, { 0,0,0,1 }, { 0,1,1,1,1,1,1,1 }, { 0,1,0,0,0,0,0,0 }, { 0,0,1,1,1,0,0 } },
		{ { 1, 0 }, { 1,1,0 }, { 1,1,1,0 }, { 1,0,1,0,1,0 }, { 1,1,1,1,1,1 }, { 1,0,0,0,0,0 } }
	);
	testWouldBeAccept(wouldBeAccept(cSignedBinary, binaryAlpha));
	cout << endl;
	// ~onlyChar
	DFA<int, int>* cOnlyChar = complement(*onlyCharDFA);
	testDFA(cOnlyChar, "~onlyChar", false, false,
		{ { }, { 0,1 }, { 0,0,0,1 }, { 0,1,1,1,1,1,1,1 }, { 0,1,0,0,0,0,0,0 }, { 0,0,1,1,1,0,0 } },
		{ { 1 } }
	);
	testWouldBeAccept(wouldBeAccept(cOnlyChar, binaryAlpha));
	cout << endl;
	/*
		Task #15 - testing the union function
	*/
	auto* onlyZeros_U_signedBinary = unionDFA(*onlyZeros, *signedBinary);
	auto* threeDFAUnion = unionDFA(*onlyZeros_U_signedBinary, *onlyEven);
	auto* comments_U_myName = unionDFA(*myName, *comments);
	auto* myName_U_onlyEmpty = unionDFA(*myName, *onlyEmpty);
	auto* noStr_U_notMyName = unionDFA(*noStr, *notMyName);
	auto* zeroOne_U_trafficLight = unionDFA(*zeroOne, *trafficLight);
	auto* ARGH_U_signedBinary = unionDFA(*ARGH, *signedBinary);
	auto* zeroOne_U_zeroOne = unionDFA(*zeroOne, *zeroOne);
	auto* comments_U_onlyCharDFA = unionDFA(*comments, *onlyCharDFA);
	auto* myName_U_cMyName = unionDFA(*myName, *cMyName);
	auto* ARGH_U_myName = unionDFA(*ARGH, *myName);
	auto* cZeroOne_U_cOnlyEven = unionDFA(*cZeroOne, *cOnlyEven);

	testUnion(onlyZeros_U_signedBinary, "onlyZeros_U_signedBinary", false, false,
		{ {0}, {1}, {1,0}, {0,0,0}, {1,0,0}, {0,0,0,0}, {0,1}, {0,0,0,1}, {0,1,0}, {0,1,1,1}, {2}, {0,1,1,0} }
	);
	testUnion(threeDFAUnion, "(onlyZeros U signedBinary) U onlyEven", false, false,
		{ {0}, {1}, {1,0}, {0,0,0}, {1,1,1}, {0,1}, {0,1,1}, {0,1,1}, {0,1,0}, {0,1,1,1,0}, {2}, {0,1,1,0,0} }
	);
	testUnion(comments_U_myName, "comments_U_myName", false, false,
		{ {'/','/',0}, {'C','J'}, {'/','/','C','J'}, { 67,74 }, {'/','/'}, {'/','/', 'y','a'},
		{'/',1,1}, {0,1,1}, {0,1,0}, {0,1,1,1,0}, {2}, {'/',0,1,1,0} }
	);
	testUnion(myName_U_onlyEmpty, "myName_U_onlyEmpty", false, false,
		{ {}, {'C','J'}, { 67,74 }, {}, {'C','J'}, { 67,74 },
		{'/',1,1}, {0,1,1}, {0,1,0}, {0,1,1,1,0}, {2}, {'/',0,1,1,0} }
	);
	testUnion(noStr_U_notMyName, "noStr_U_notMyName", false, false,
		{ { }, { 1 }, { 0,0,0,1 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 },
		{'C','J'},{ 67,74 },{'C','J'},{ 67,74 },{'C','J'},{ 67,74 } }
	);
	testUnion(zeroOne_U_trafficLight, "zeroOne_U_trafficLight", false, false,
		{ { 0, 1 }, { 0,0,1,0 }, { 0,1,0,0,0,0,0 }, { 1,1,1,1,1,1,0,1 }, { 0,0,0,1,1,1,1,1 }, { 1,1,1,1,1,0,1,1,1 },
		{ }, { 1 }, { 1,1,1,0 }, { 1, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1 } }
	);
	testUnion(ARGH_U_signedBinary, "ARGH_U_signedBinary", false, false,
		{ { 'A','R','G','H' }, { 'A','R','R','G','H' }, { 'A','A','R','R','G','G','H','H' },
		{ 1, 0 }, { 1,1,0 }, { 1,1,1,0 },
		{ }, { 'A','R','G' }, { 'A','R','H','G' }, { 0,1 }, { 0,0,0,1 },{0} }
	);
	testUnion(zeroOne_U_zeroOne, "zeroOne_U_zeroOne", false, false,
		{ { 0, 1 }, { 0,0,1,0 }, { 0,1,0,0,0,0,0 }, { 1,1,1,1,1,1,0,1 }, { 0,0,0,1,1,1,1,1 }, { 1,1,1,1,1,0,1,1,1 },
		{ }, { 1 }, { 1,1,1,0 }, { 1, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1 } }
	);
	testUnion(comments_U_onlyCharDFA, "comments_U_onlyCharDFA", false, false,
		{ {'/','/',0}, {'/','/','C','J'}, {1}, {'/','/'}, {'/','/', 'y','a'}, {'/','/','o','k'},
		{'/',1,1}, { }, {0,1,0}, {0,1,1,1,0}, {2}, {'/',0,1,1,0} }
	);
	testUnion(myName_U_cMyName, "myName_U_cMyName", false, true,
		{ { 'C', 'J' }, { 67,74 } ,{'/','/'}, {1}, {0,0,0,1}, {1,2,3,4,5},
		{},{}, {}, {}, {}, {} }
	);
	testUnion(ARGH_U_myName, "ARGH_U_myName", false, false,
		{ { 'C', 'J' }, { 67,74 }, { 'A','R','G','H' }, { 'A','R','R','G','H' },
			{ 'A','A','R','R','G','G','H','H' }, { 'A','R','R','G','H' },
		 {'/','/'},{1}, {0,0,0,1}, {1,2,3,4,5}, {2}, {'/',0,1,1,0} }
	);
	testUnion(cZeroOne_U_cOnlyEven, "cZeroOne_U_cOnlyEven", false, false,
		{ { }, { 1 }, { 1,1,1,0 }, { 0,0,0 }, { 1 }, { 1,2,3 },
		{ 0, 1 }, { 0,0,1 }, { }, { 0,1,0,0 }, { 0,1,0 }, { 1,1 }}
	);
	
	cout << endl;
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
Config<State> update(DFA<State, C>* dfa, Config<State> cfg) {
	list<int>::iterator i = cfg.curStr.begin();
	cfg.curS = dfa->d(cfg.curS, *i);
	cfg.curStr.pop_front();
	return cfg;
}
DFA<int, int> *onlyChar(int c) {
	//onlyChar
	DFA<int, int> *onlyCharDFA = new DFA<int, int> (
		[](int curS) {return ((curS == 0) || (curS == 1) || (curS == 2)); },
		0,
		[c](int curS, int curC) {
			if (curS == 0 && curC == c)
				return 1;
			else 
				return 2;
		} ,
		[](int curS) {return curS == 1; }
	);
	return onlyCharDFA;
}
//Task #11 - a function that returns a list of configurations that a DFA visits
template<typename State, typename C>
list<Config<State>> trace(DFA<State, C> *dfa, list<int> str) {
	Config<State> config(dfa->q0, str);
	list<Config<State>> lc;
	lc.push_back(config);
	while (config.curStr.size() != 0) {
		config = update(dfa, config);
		lc.push_back(config);
	}
	return lc;
}
template<typename State>
void printConfigList(list<Config<State>>& TL) {
	if (typeid(State) == typeid(int)) {
		list<Config<int>>::iterator j;
		for (j = TL.begin(); j != TL.end(); j++) {
			cout << '[';
			cout << j->curS;
			cout << ']';
			j->printStr();
			cout << ' ';
		}
	}
}
void printConfigList_pair(list<Config<pair<int, int>>>& TL) {
	list<Config<pair<int, int>>>::iterator i;
	for (i = TL.begin(); i != TL.end(); i++) {
		cout << '[' << i->curS.first << ", " << i->curS.second << ']';
		i->printStr();
		cout << ' ';
	}
}
void testDFA(DFA<int, int>* dfa, string DFAName, bool noAccepts, bool allAccepts,
	list<list<int>> accepts, list<list<int>> nAccepts) {
	int count = 0;
	//nested for-loops for all the strings it should accept
	if (!noAccepts) {
		for (auto i : accepts) {
			if (!dfa->accept(i)) {
				cout << "\t\t" << DFAName << "-FAIL at index " << count << endl;
			}
			count++;
		}
	}
	//nested for-loops for all the strings it should NOT accept
	if (!allAccepts) {
		for (auto i : nAccepts) {
			if (dfa->accept(i)) {
				cout << "\t\t" << DFAName << "-FAIL at index " << count << endl;
			}
			count++;
		}
	}
	list<list<int>>::iterator t = accepts.begin();
	list <Config<int>> traceList = trace(dfa, *t);
	cout << DFAName <<":" << endl;
	printConfigList(traceList);
	cout << endl;

	
}
// Task #12
pair<bool, list<int>> wouldBeAccept(DFA<int, int>* dfa, list<int> sigma) {
	pair<bool, list<int>> ret;
	ret.first = false;
	list<Config<int>> h = { Config<int>(dfa->q0, {}) };
	list<int> v = {dfa->q0};
	int qi, qj;
	list<int> w;
	while (!h.empty()) {
		qi = h.front().curS;
		w = h.front().curStr;
		h.pop_front();
		if (dfa->F(qi)) {
			ret.first = true;
			ret.second = w;
			break;
		}
		for (auto i : sigma) {
			qj = dfa->d(qi, i);
			auto found = find(v.begin(), v.end(), qj);
			if (found == v.end()) {
				v.push_back(qj);
				w.push_back(i);
				h.push_back(Config<int>(qj, w));
				w.pop_back();
			}
		}
	}
	return ret;
}
void testWouldBeAccept(pair<bool, list<int>> dfaPairStr) {
	if (dfaPairStr.first) {
		cout << "possible string: ";
		cout << '{';
		for (auto i : dfaPairStr.second) {
			cout << i;
		}
		cout << '}';
	}
	else {
		cout << "*** DFA accepts no strings! ***";
	}
	cout << endl;
}
// Task #13 - complement
template<typename State, typename C>
DFA<State, C> *complement(DFA<State, C> dfa) {
	DFA<int, int> *cDFA = new DFA<int, int>(
		dfa.Q,
		dfa.q0,
		dfa.d,
		[=](int s) { return !dfa.F(s); }
		);
	return cDFA;
}
// Task #14 - union
template<typename State, typename State2, typename C>
DFA<pair<State, State2>, C>* unionDFA(DFA<State, C> A, DFA<State2, C> B) {
	DFA<pair<State, State2>, C>* uDFA = new DFA<pair<State, State2>, C>(
		[=](pair<State, State2> s) { return A.Q(s.first) && B.Q(s.second); },
		pair<State, State2>(A.q0, B.q0),
		[=](pair<State, State2> s, C c) {
			return pair<State, State2>(A.d(s.first, c), B.d(s.second, c));
		},
		[=](pair<State, State2> s) {
			return (A.F(s.first) && B.Q(s.second)) || A.Q(s.first) && (B.F(s.second));
		}
		);
	return uDFA;
}
//Task #15
template<typename State1, typename State2, typename C>
void testUnion(DFA<pair<State1,State2>, C>*dfa, string DFAName, bool noAccepts, bool allAccepts, 
	list<list<int>> strL) {
	int count = 0;
	for (auto i : strL) {
		if (!allAccepts) {
			if (count > 5) {
				if (dfa->accept(i)) {
					cout << "\t\t" << DFAName << "### FAIL at index " << count << endl;
				}
			}
		}
		if (!noAccepts) {
			if (count <= 5) {
				if (!dfa->accept(i)) {
					cout << "\t\t" << DFAName << "### FAIL at index " << count << endl;
				}

			}
		}
		count++;
	}
}