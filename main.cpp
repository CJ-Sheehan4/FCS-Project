#include <iostream>
#include <functional>
#include <string>
#include <list>
#include <utility>
#include <optional>
#include <algorithm>
#include <typeinfo>
#include <memory>
#include <variant>
#include "DFA.h"
#include "NFA.h"
#include "TT.h"
#include "Config.h"
#include "DFA.cpp"
#include "NFA.cpp"
#include "TT.cpp"
using namespace std;

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
template<typename State, typename C>
void testDFA(DFA<State, C>* dfa, string DFAName, bool noAccepts, bool allAccepts,
	list<list<int>> accepts, list<list<int>> nAccepts);
template<typename State, typename C>
pair<bool, list<int>> wouldBeAccept(DFA<State, C>* dfa, list<int> sigma);
void testWouldBeAccept(pair<bool, list<int>> dfaPairStr);
template<typename State, typename C>
DFA<State, C>* complement(DFA<State, C> *dfa);
template<typename State, typename State2, typename C>
DFA<pair<State, State2>, C>* unionDFA(DFA<State, C> *A, DFA<State2, C> *B);
template<typename State1, typename State2, typename C>
void testUandInter(DFA<pair<State1, State2>, C>* dfa, string DFAName, bool noAccepts, bool allAccepts, 
	list<list<int>> strL);
template<typename State, typename State2, typename C>
DFA<pair<State, State2>, C>* intersect(DFA<State, C> *A, DFA<State2, C> *B);
template<typename State1, typename State2, typename C>
bool subset(DFA<State1, C> *X, DFA<State2, C> *Y, list<int> sigma);
template<typename State1, typename State2, typename C>
void testSubset(DFA<State1, C>* X, DFA<State2, C>* Y, bool answer, string name, list<int> sigma);
template<typename State1, typename State2, typename C>
bool equality(DFA<State1, C>* X, DFA<State2, C>* Y, list<int> sigma);
template<typename State1, typename State2, typename C>
void testEquality(DFA<State1, C>* X, DFA<State2, C>* Y, bool answer, string name, list<int> sigma);
template<typename State, typename C>
NFA<State, C>* DFAtoNFA(DFA<State, C> *dfa);
template<typename State, typename C>
void testNFA(NFA<State, C>* nfa, list<int> str);
template<typename State>
list<Config<State>> createTrace(list<State> states, list<int> str);
template<typename State, typename C>
bool oracle(NFA<State, C>* nfa, list<int> str, list<Config<State>> ts);
template<typename State, typename C>
void oracleLoop(NFA<State, C>* nfa, string name, list<list<int>> strs, list<list<Config<State>>> ts);
template<typename State, typename C>
shared_ptr <TT<State, C>> forking(NFA<State, C>* nfa, list<int> str);
template<typename State, typename C>
void treeLoop(list<shared_ptr <TT<State, C>>> tL, list<int> str);
template<typename State, typename C>
void testNFAAccepts(NFA<State, C>* nfa, list<int> str, bool strShouldAccept, string name);
template<typename State, typename C>
NFA<pair<int, State>, C>* unionNFA(NFA<State, C>* a, NFA<State, C>* b);
template<typename State, typename C>
NFA<pair<int, State>, C>* concat(NFA<State, C>* a, NFA<State, C>* b);
template<typename State>
list<pair<int, State>> nfaH(list<State> l, int tag);
template<typename State, typename C>
void testNFA(NFA<State, C>* nfa, string name, bool noAccepts, bool allAccepts,
	list<list<int>> strL);
template<typename State, typename C>
NFA<State, C>* star(NFA<State, C>* a);
template<typename State, typename C>
DFA<list<State>, C>* NFAtoDFA(NFA<State, C>* nfa);
template<typename State, typename C>
list<State> E(list<State> x, NFA<State, C>* nfa);
template<typename State, typename C>
void testQ_q0_F(DFA<State, C>* dfa, list<list<int>>Q, list<int>q0, list<list<int>>F);

int main(void) {
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
	//testDFA(noStr, "No String", true, false,
	//	{ {} },
	//	{ { 0, 0, 0 }, { 1 }, { 1, 2, 3 }, { 1, 2, 3, 4, 5 }, { 1, 2, 3, 4, 5, 6, 7 }, { 1, 1, 1, 1, 1, 1 } }
	//);
	//testWouldBeAccept(wouldBeAccept(noStr, zeroNineAlpha));
	//cout << endl;

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
	//testDFA(onlyEmpty, "Only Empty Str", false, false,
	//	{ { } },
	//	{ { 0, 0, 0 }, { 1 }, { 1, 2, 3 }, { 1, 2, 3, 4, 5 }, { 1, 2, 3, 4, 5, 6, 7 }, { 1, 1, 1, 1, 1, 1, 1, 1 } }
	//);
	//testWouldBeAccept(wouldBeAccept(onlyEmpty, zeroNineAlpha));
	//cout << endl;

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
	/*
	testDFA(onlyEven, "Only Even", false, false,
		{ { 0,1 }, { 0,0 }, { 1,1 }, { 1,2,3,4 }, { 1,2,3,4,5,6 }, { 1,1,1,1,1,1,1,1 } },
		{ { 0,0,0 }, { 1 }, { 1,2,3 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 } }
	);
	testWouldBeAccept(wouldBeAccept(onlyEven, zeroNineAlpha));
	cout << endl;
	*/
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
	/*
	testDFA(onlyZeros, "Only Zero's", false, false,
		{ { 0 }, { 0, 0 }, { 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } },//accepts
		{ { }, { 1 }, { 0, 0, 0, 1 }, { 1, 2, 3, 4, 5 }, { 1, 2, 3, 4, 5, 6, 7 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1 } }//does not accept
	);
	testWouldBeAccept(wouldBeAccept(onlyZeros, zeroNineAlpha));
	cout << endl;
	*/
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
	/*
	testDFA(myName, "My name", false, false,
		{ { 'C', 'J' }, { 67,74 } },	//accepts
		{ { }, { 1 }, { 0,0,0,1 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 } }
	);
	testWouldBeAccept(wouldBeAccept(myName, englishAlpha));
	cout << endl;
*/
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
	/*
	testDFA(notMyName, "Not My Name", false, false,
		{ { }, { 1 }, { 0,0,0,1 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 } },
		{ { 'C', 'J' }, { 67,74 } }
	);
	testWouldBeAccept(wouldBeAccept(notMyName, englishAlpha));
	cout << endl;
*/
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
	/*
	testDFA(comments, "Comments", false, false,
		{ { '/','/' }, { '/','/' , 'A'}, {'/','/','C', 'J'}, {'/','/', 'y','a'},
			{'/', '/' , 'A', 'B', 'C' }, {'/','/', 5, 6, 'y'} },
		{ { }, { '/', 1 }, { 0,0,0,1 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 } }
	);
	testWouldBeAccept(wouldBeAccept(comments, englishAlpha));
	cout << endl;
*/
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
			else if ((c == 1) && (s == 2))
				return 2;
			else if ((c == 0) && (s == 2))
				return 2;
		},
		[](int s) {return s == 2; }
		);
	/*
	testDFA(zeroOne, "Zero One", false, false,
		{ { 0, 1 }, { 0,0,1,0 }, { 0,1,0,0,0,0,0 }, { 1,1,1,1,1,1,0,1 }, { 0,0,0,1,1,1,1,1 }, { 1,1,1,1,1,0,1,1,1 } },
		{ { }, { 1 }, { 1,1,1,0 }, { 1, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1 } }
	);
	testWouldBeAccept(wouldBeAccept(zeroOne, binaryAlpha));
	cout << endl;
*/
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
	/*
	testDFA(noStr, "Traffic Light", true, false,
		{ { } },
		{ { 0,0,0 }, { 1 }, { 1, 1, 1}, { 1, 0, 1, 0, 1 }, { 1, 1, 1, 0, 0, 0}, { 0, 0, 1, 1} }
	);
	testWouldBeAccept(wouldBeAccept(trafficLight, binaryAlpha));
	cout << endl;
*/
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
	/*
	testDFA(ARGH, "ARGH", false, false,
		{ { 'A','R','G','H' }, { 'A','R','R','G','H' }, { 'A','A','R','R','G','G','H','H' }, { 'A','R','G','G','H' },
			{ 'A','R','G','H','H' }, { 'A','A','A','R','R','R','G','G','G','H','H','H' } },
		{ { }, { 1 }, { 1,2,3,4,5 }, { 'A','R','G' }, { 'A','R','H','G' }, { 'O','K' } }
	);
	testWouldBeAccept(wouldBeAccept(ARGH, englishAlpha));
	cout << endl;
*/
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
			else
				return 2;
		},
		[](int s) {return s == 1; }
		);
	/*
	testDFA(signedBinary, "Signed Binary", false, false,
		{ { 1, 0 }, { 1,1,0 }, { 1,1,1,0 }, { 1,0,1,0,1,0 }, { 1,1,1,1,1,1 }, { 1,0,0,0,0,0 } },
		{ { }, { 0,1 }, { 0,0,0,1 }, { 0,1,1,1,1,1,1,1 }, { 0,1,0,0,0,0,0,0 }, { 0,0,1,1,1,0,0 } }
	);
	testWouldBeAccept(wouldBeAccept(signedBinary, binaryAlpha));
	cout << endl;
*/
	// DFA that creates accepts exactly one character
	list<int> str1 = { 1 };
	DFA<int, int>* onlyCharDFA = onlyChar(1);
	/*
	testDFA(onlyCharDFA, "Only Char", false, false,
		{ { 1 } },
		{ { }, { 0,1 }, { 0,0,0,1 }, { 0,1,1,1,1,1,1,1 }, { 0,1,0,0,0,0,0,0 }, { 0,0,1,1,1,0,0 } }
	);
	testWouldBeAccept(wouldBeAccept(onlyCharDFA, binaryAlpha));
	cout << endl;
*/
	/*
		Task #13 - testing all DFAs that are complements
	*/
	// ~noStr
	DFA<int, int>* cNoStr = complement(noStr);
	/*
	testDFA(cNoStr, "~noStr", false, true,
		{ { }, { 0, 0, 0 }, { 1 }, { 1, 2, 3, 4 }, { 3, 2, 1 }, { 1, 2, 3, 4, 5, 6, 7 } },
		{ { } }
	);
	testWouldBeAccept(wouldBeAccept(cNoStr, zeroNineAlpha));
	cout << endl;
*/
	// ~onlyEmpty
	DFA<int, int>* cOnlyEmpty = complement(onlyEmpty);
	/*
	testDFA(cOnlyEmpty, "~onlyEmpty", false, false,
		{ { 0, 0, 0 }, { 1 }, { 1, 2, 3, 4 }, { 3, 2, 1 }, { 1, 2, 3, 4, 5, 6, 7 }, { 1, 1, 1, 1, 1, } },
		{ { } }
	);
	testWouldBeAccept(wouldBeAccept(cOnlyEmpty, zeroNineAlpha));
	cout << endl;
*/
	//~onlyEven
	DFA<int, int>* cOnlyEven = complement(onlyEven);
	/*
	testDFA(cOnlyEven, "~Only Even (odd)", false, false,
		{ { 0,0,0 }, { 1 }, { 1,2,3 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 } },
		{ { 0,1 }, { 0,0 }, { 1,1 }, { 1,2,3,4 }, { 1,2,3,4,5,6 }, { 1,1,1,1,1,1,1,1 } }
	);
	testWouldBeAccept(wouldBeAccept(cOnlyEven, zeroNineAlpha));
	cout << endl;
*/
	// ~onlyZeros
	DFA<int, int>* cOnlyZeros = complement(onlyZeros);
	/*
	testDFA(cOnlyZeros, "~onlyZeros", false, false,
		{ { }, { 1 }, { 0, 0, 0, 1 }, { 0, 2, 3, 4, 5 }, { 1, 2, 3, 4, 5, 6, 7 }, { 1, 0, 0, 0, 0, 0, 0, 0, 0 } },
		{ { 0 }, { 0, 0 }, { 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0 } }
	);
	testWouldBeAccept(wouldBeAccept(cOnlyZeros, zeroNineAlpha));
	cout << endl;
*/
	// ~myName
	DFA<int, int>* cMyName = complement(myName);
	/*
	testDFA(cMyName, "~myName", false, false,
		{ { }, { 1 }, { 0,0,0,1 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 } },
		{ { 'C', 'J' }, { 67,74 } }
	);
	testWouldBeAccept(wouldBeAccept(cMyName, englishAlpha));
	cout << endl;
*/
	// ~notMyName
	DFA<int, int>* cNotMyName = complement(notMyName);
	/*
	testDFA(cNotMyName, "~notMyName", false, false,
		{ { 'C', 'J' }, { 67,74 } },
		{ { }, { 1 }, { 0,0,0,1 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 } }
	);
	testWouldBeAccept(wouldBeAccept(cNotMyName, englishAlpha));
	cout << endl;
*/
	// ~comments DFA
	DFA<int, int>* cComments = complement(comments);
	/*
	testDFA(cComments, "~comments", false, false,
		{ { }, { '/', 1 }, { 0,0,0,1 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 } },
		{ { '/','/' }, { '/','/' , 'A'}, {'/','/','C', 'J'}, {'/','/', 'y','a'},
			{'/', '/' , 'A', 'B', 'C' }, {'/','/', 5, 6, 'y'} }
	);
	testWouldBeAccept(wouldBeAccept(cComments, englishAlpha));
	cout << endl;
*/
	// ~zerOne
	DFA<int, int>* cZeroOne = complement(zeroOne);
	/*
	testDFA(cZeroOne, "~zeroOne", false, false,
		{ { }, { 1 }, { 1,1,1,0 }, { 1, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1 } },
		{ { 0, 1 }, { 0,0,1,0 }, { 0,1,0,0,0,0,0 }, { 1,1,1,1,1,1,0,1 }, { 0,0,0,1,1,1,1,1 }, { 1,1,1,1,1,0,1,1,1 } }
	);
	testWouldBeAccept(wouldBeAccept(cZeroOne, binaryAlpha));
	cout << endl;
*/
	// ~trafficLight
	DFA<int, int>* cTrafficLight = complement(trafficLight);
	/*
	testDFA(cTrafficLight, "~trafficLight", false, true,
		{ { 0,0,0 }, { 1 }, { 1, 1, 1}, { 1, 0, 1, 0, 1 }, { 1, 1, 1, 0, 0, 0}, { 0, 0, 1, 1} },
		{ { } }
	);
	testWouldBeAccept(wouldBeAccept(cTrafficLight, englishAlpha));
	cout << endl;
*/
	// ~ARGH
	DFA<int, int>* cARGH = complement(ARGH);
	/*
	testDFA(cARGH, "~ARGH", false, false,
		{ { }, { 1 }, { 1,2,3,4,5 }, { 'A','R','G' }, { 'A','R','H','G' }, { 'O','K' } },
		{ { 'A','R','G','H' }, { 'A','R','R','G','H' }, { 'A','A','R','R','G','G','H','H' }, { 'A','R','G','G','H' },
			{ 'A','R','G','H','H' }, { 'A','A','A','R','R','R','G','G','G','H','H','H' } }
	);
	testWouldBeAccept(wouldBeAccept(cARGH, englishAlpha));
	cout << endl;
*/
	// ~signedBinary
	auto* cSignedBinary = complement(signedBinary);
	/*
	testDFA(cSignedBinary, "~signedBinary", false, false,
		{ { }, { 0,1 }, { 0,0,0,1 }, { 0,1,1,1,1,1,1,1 }, { 0,1,0,0,0,0,0,0 }, { 0,0,1,1,1,0,0 } },
		{ { 1, 0 }, { 1,1,0 }, { 1,1,1,0 }, { 1,0,1,0,1,0 }, { 1,1,1,1,1,1 }, { 1,0,0,0,0,0 } }
	);
	testWouldBeAccept(wouldBeAccept(cSignedBinary, binaryAlpha));
	cout << endl;
*/
	// ~onlyChar
	DFA<int, int>* cOnlyChar = complement(onlyCharDFA);
	/*
	testDFA(cOnlyChar, "~onlyChar", false, false,
		{ { }, { 0,1 }, { 0,0,0,1 }, { 0,1,1,1,1,1,1,1 }, { 0,1,0,0,0,0,0,0 }, { 0,0,1,1,1,0,0 } },
		{ { 1 } }
	);
	testWouldBeAccept(wouldBeAccept(cOnlyChar, binaryAlpha));
	cout << endl;
*/
	/*
		Task #15- testing the union function
	*/
	auto* onlyZeros_U_signedBinary = unionDFA(onlyZeros, signedBinary);
	if (!onlyZeros_U_signedBinary->Q(pair<int, int>(2,1))) {
		cout << "\t\t" << "### FAIL Q###" << endl;
	}
	auto* threeDFAUnion = unionDFA(onlyZeros_U_signedBinary, onlyEven);
	auto* comments_U_myName = unionDFA(myName, comments);
	auto* myName_U_onlyEmpty = unionDFA(myName, onlyEmpty);
	auto* noStr_U_notMyName = unionDFA(noStr, notMyName);
	auto* zeroOne_U_trafficLight = unionDFA(zeroOne, trafficLight);
	auto* ARGH_U_signedBinary = unionDFA(ARGH, signedBinary);
	auto* zeroOne_U_zeroOne = unionDFA(zeroOne, zeroOne);
	auto* comments_U_onlyCharDFA = unionDFA(comments, onlyCharDFA);
	auto* myName_U_cMyName = unionDFA(myName, cMyName);
	auto* ARGH_U_myName = unionDFA(ARGH, myName);
	auto* cZeroOne_U_cOnlyEven = unionDFA(cZeroOne, cOnlyEven);
	auto* fourUDFA = unionDFA(threeDFAUnion, myName);
	testUandInter(onlyZeros_U_signedBinary, "onlyZeros_U_signedBinary", false, false,
		{ {0}, {1}, {1,0}, {0,0,0}, {1,0,0}, {0,0,0,0}, 
		{0,1}, {0,0,0,1}, {0,1,0}, {0,1,1,1}, {2}, {0,1,1,0} }
	);
	testUandInter(threeDFAUnion, "(onlyZeros U signedBinary) U onlyEven", false, false,
		{ {0}, {1}, {1,0}, {0,0,0}, {1,1,1}, {0,1}, {0,1,1}, 
		{0,1,1}, {0,1,0}, {0,1,1,1,0}, {2}, {0,1,1,0,0} }
	);
	testUandInter(fourUDFA, "fourUDFA", false, false,
		{ {0}, {1}, {1,0}, {'C','J'}, {2,2}, {0,1}, {0,1,1}, {0,1,1}, {0,1,0}, {0,1,1,1,0}}
	);
	testUandInter(comments_U_myName, "comments_U_myName", false, false,
		{ {'/','/',0}, {'C','J'}, {'/','/','C','J'}, { 67,74 }, {'/','/'}, {'/','/', 'y','a'},
		{'/',1,1}, {0,1,1}, {0,1,0}, {0,1,1,1,0}, {2}, {'/',0,1,1,0} }
	);
	testUandInter(myName_U_onlyEmpty, "myName_U_onlyEmpty", false, false,
		{ {}, {'C','J'}, { 67,74 }, {}, {'C','J'}, { 67,74 },
		{'/',1,1}, {0,1,1}, {0,1,0}, {0,1,1,1,0}, {2}, {'/',0,1,1,0} }
	);
	testUandInter(noStr_U_notMyName, "noStr_U_notMyName", false, false,
		{ { }, { 1 }, { 0,0,0,1 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 },
		{'C','J'},{ 67,74 },{'C','J'},{ 67,74 },{'C','J'},{ 67,74 } }
	);
	testUandInter(zeroOne_U_trafficLight, "zeroOne_U_trafficLight", false, false,
		{ { 0, 1 }, { 0,0,1,0 }, { 0,1,0,0,0,0,0 }, { 1,1,1,1,1,1,0,1 }, { 0,0,0,1,1,1,1,1 }, { 1,1,1,1,1,0,1,1,1 },
		{ }, { 1 }, { 1,1,1,0 }, { 1, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1 } }
	);
	testUandInter(ARGH_U_signedBinary, "ARGH_U_signedBinary", false, false,
		{ { 'A','R','G','H' }, { 'A','R','R','G','H' }, { 'A','A','R','R','G','G','H','H' },
		{ 1, 0 }, { 1,1,0 }, { 1,1,1,0 },
		{ }, { 'A','R','G' }, { 'A','R','H','G' }, { 0,1 }, { 0,0,0,1 }, {0} }
	);
	testUandInter(zeroOne_U_zeroOne, "zeroOne_U_zeroOne", false, false,
		{ { 0, 1 }, { 0,0,1,0 }, { 0,1,0,0,0,0,0 }, { 1,1,1,1,1,1,0,1 }, { 0,0,0,1,1,1,1,1 }, { 1,1,1,1,1,0,1,1,1 },
		{ }, { 1 }, { 1,1,1,0 }, { 1, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1 } }
	);
	testUandInter(comments_U_onlyCharDFA, "comments_U_onlyCharDFA", false, false,
		{ {'/','/',0}, {'/','/','C','J'}, {1}, {'/','/'}, {'/','/', 'y','a'}, {'/','/','o','k'},
		{'/',1,1}, { }, {0,1,0}, {0,1,1,1,0}, {2}, {'/',0,1,1,0} }
	);
	testUandInter(myName_U_cMyName, "myName_U_cMyName", false, true,
		{ { 'C', 'J' }, { 67,74 } ,{'/','/'}, {1}, {0,0,0,1}, {1,2,3,4,5},
		{},{}, {}, {}, {}, {} }
	);
	testUandInter(ARGH_U_myName, "ARGH_U_myName", false, false,
		{ { 'C', 'J' }, { 67,74 }, { 'A','R','G','H' }, { 'A','R','R','G','H' },
			{ 'A','A','R','R','G','G','H','H' }, { 'A','R','R','G','H' },
		 {'/','/'},{1}, {0,0,0,1}, {1,2,3,4,5}, {2}, {'/',0,1,1,0} }
	);
	testUandInter(cZeroOne_U_cOnlyEven, "cZeroOne_U_cOnlyEven", false, false,
		{ { }, { 1 }, { 1,1,1,0 }, { 0,0,0 }, { 1 }, { 1,2,3 },
		{ 0, 1 }, { 0, 0,0, 1 }, {1,1,0,1}, { 0,1,0,0 }, {0,1,1,1 }, {0,0,0,0,0,1 } }
	);
	/*
		Tasks #17 - INTERSECT TESTS
	*/
	auto* onlyZeros_INT_signedBinary = intersect(onlyZeros, signedBinary);
	if (!onlyZeros_INT_signedBinary->Q(pair<int, int>(2, 1))) {
		cout << "\t\t" << "### FAIL Q###" << endl;
	}
	auto* zeroOne_INT_signed = intersect(zeroOne, signedBinary);
	auto* threeDFAINT = intersect(zeroOne_INT_signed, onlyEven);
	auto* myName_INT_onlyEmpty = intersect(myName, onlyEmpty);
	auto* noStr_INT_notMyName = intersect(noStr, notMyName);
	auto* zeroOne_INT_trafficLight = intersect(zeroOne, trafficLight);
	auto* ARGH_INT_signedBinary = intersect(ARGH, signedBinary);
	auto* zeroOne_INT_zeroOne = intersect(zeroOne, zeroOne);
	auto* comments_INT_onlyCharDFA = intersect(comments, onlyCharDFA);
	auto* myName_INT_cMyName = intersect(myName, cMyName);
	auto* ARGH_INT_myName = intersect(ARGH, myName);
	auto* cZeroOne_INT_cOnlyEven = intersect(cZeroOne, cOnlyEven);
	// accepts no str
	testUandInter(onlyZeros_INT_signedBinary, "onlyZeros_INT_signedBinary", true, false,
		{ {0}, {1}, {1,0}, {0,0,0}, {1,0,0}, {0,0,0,0}, {0,1}, {0,0,0,1}, {0,1,0}, {0,1,1,1}, {2}, {0,1,1,0} }
	);
	testUandInter(zeroOne_INT_signed, "zeroOne_INT_signed", false, false,
		{ {1,0,1}, {1,0,0,0,1}, {1,0,1,1,1}, {1,0,1,0,1,0}, {1,0,1,0,0,0}, {1,0,1,1,1,0,1,0,0},
		{1,0}, {0,1}, {0,0,1,1,0}, {1,1,1}, {1,1,1,0,0,0}, {0,1,0,1,1,1} }
	);
	testUandInter(threeDFAINT, "(zeroOne ^ signedBinary) ^ onlyEven", false, false,
		{ {1,0,1,1}, {1,0,1,0}, {1,0,1,0,1,0}, {1,1,1,1,0,1}, {1,1,1,1,1,1,0,1}, {1,0,0,0,0,1},
		{0,1}, {1,1}, {1,0,1}, {2}, {0,1,1,0,1,1} }
	);
	// accepts no str
	testUandInter(myName_INT_onlyEmpty, "myName_INT_onlyEmpty", true, false,
		{ {}, {'C','J'}, { 67,74 }, {}, {'C','J'}, { 67,74 },
		{'/',1,1}, {0,1,1}, {0,1,0}, {0,1,1,1,0}, {2}, {'/',0,1,1,0} }
	);
	// accepts no str
	testUandInter(noStr_INT_notMyName, "noStr_INT_notMyName", true, false,
		{ { }, { 1 }, { 0,0,0,1 }, { 1,2,3,4,5 }, { 1,2,3,4,5,6,7 }, { 1,1,1,1,1,1,1,1,1 },
		{'C','J'},{ 67,74 },{'C','J'},{ 67,74 },{'C','J'},{ 67,74 } }
	);
	// accepts no str
	testUandInter(zeroOne_INT_trafficLight, "zeroOne_INT_trafficLight", true, false,
		{ { 0, 1 }, { 0,0,1,0 }, { 0,1,0,0,0,0,0 }, { 1,1,1,1,1,1,0,1 }, { 0,0,0,1,1,1,1,1 }, { 1,1,1,1,1,0,1,1,1 },
		{ }, { 1 }, { 1,1,1,0 }, { 1, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1 } }
	);
	// accepts no str
	testUandInter(ARGH_INT_signedBinary, "ARGH_INT_signedBinary", true, false,
		{ { 'A','R','G','H' }, { 'A','R','R','G','H' }, { 'A','A','R','R','G','G','H','H' },
		{ 1, 0 }, { 1,1,0 }, { 1,1,1,0 },
		{ }, { 'A','R','G' }, { 'A','R','H','G' }, { 0,1 }, { 0,0,0,1 },{0} }
	);
	testUandInter(zeroOne_INT_zeroOne, "zeroOne_INT_zeroOne", false, true,
		{ { 0, 1 }, { 0,0,1,0 }, { 0,1,0,0,0,0,0 }, { 1,1,1,1,1,1,0,1 }, { 0,0,0,1,1,1,1,1 }, { 1,1,1,1,1,0,1,1,1 },
		{ }, { 1 }, { 1,1,1,0 }, { 1, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1 } }
	);
	// accepts no str
	testUandInter(comments_INT_onlyCharDFA, "comments_INT_onlyCharDFA", true, false,
		{ {'/','/',0}, {'/','/','C','J'}, {1}, {'/','/'}, {'/','/', 'y','a'}, {'/','/','o','k'},
		{'/',1,1}, { }, {0,1,0}, {0,1,1,1,0}, {2}, {'/',0,1,1,0} }
	);
	// accepts no str
	testUandInter(myName_INT_cMyName, "myName_INT_cMyName", true, false,
		{ { 'C', 'J' }, { 67,74 } ,{'/','/'}, {1}, {0,0,0,1}, {1,2,3,4,5},
		{},{}, {}, {}, {}, {} }
	);
	// accepts no str
	testUandInter(ARGH_INT_myName, "ARGH_INT_myName", true, false,
		{ { 'C', 'J' }, { 67,74 }, { 'A','R','G','H' }, { 'A','R','R','G','H' },
			{ 'A','A','R','R','G','G','H','H' }, { 'A','R','R','G','H' },
		 {'/','/'},{1}, {0,0,0,1}, {1,2,3,4,5}, {2}, {'/',0,1,1,0} }
	);
	testUandInter(cZeroOne_INT_cOnlyEven, "cZeroOne_INT_cOnlyEven", false, false,
		{ { 1 }, { 1,0,0 }, { 0,0,0 }, { 1,1,1,0,0 }, { 1,2,3 },{ 1,1,1 },
		{ 0, 1 }, { 0,0,1 }, { }, { 0,1,0,0 }, { 0,1,0 }, { 1,1 } }
	);
	cout << endl;
	/*
		TASK #19 - Write a dozen tests for your subset function.
	*/
	testSubset(myName, cNotMyName, true, "myName subset of cNotMyName", englishAlpha);
	testSubset(onlyEmpty, onlyEven, true, "onlyEmpty subset of onlyEven", binaryAlpha);
	testSubset(onlyCharDFA, cOnlyEven, true, "onlyCharDFA subset of cOnlyEven", binaryAlpha);
	testSubset(trafficLight, noStr, true, "trafficLight subset of noStr", binaryAlpha);
	testSubset(signedBinary, cOnlyZeros, true, "signedBinary subset of cOnlyZeros", binaryAlpha);
	testSubset(myName, comments_U_myName, true, "myName subset of comments_U_myName", englishAlpha);
	testSubset(ARGH, ARGH_U_signedBinary, true, "ARGH subset of ARGH_U_signedBinary", englishAlpha);
	testSubset(signedBinary, ARGH_U_signedBinary, true, "signedBinary subset of ARGH_U_signedBinary", englishAlpha);
	testSubset(onlyEven, onlyZeros, false, "onlyEven subset of onlyZeros", binaryAlpha);
	testSubset(cOnlyEmpty, onlyEven, false, "cOnlyEmpty subset of onlyEven", binaryAlpha);
	testSubset(onlyCharDFA, onlyEven, false, "onlyCharDFA subset of onlyEven", binaryAlpha);
	testSubset(myName_U_onlyEmpty, comments_U_myName, false, "myNameUonlyEmpty, commentsUmyName", englishAlpha);
	testSubset(cZeroOne_INT_cOnlyEven, cSignedBinary, false, "cZeroOneINTcOnlyEven, cSignedBinary", binaryAlpha);
	testSubset(onlyEmpty, myName, false, "onlyEmpty subset of myName", englishAlpha);
	/*
		TASK #21 - Write a dozen tests for your equality function.
	*/

	/*
		7 cases that are true, L(DFA_a) == L(DFA_b)
	*/ 
	// onlyEven == onlyEven: testing a case that should obviously be true
	testEquality(onlyEven, onlyEven, true, "onlyEven != onlyEven", binaryAlpha);
	// trafficLight == noStr: although they are difined differently, both DFAs accept no str
	testEquality(trafficLight, noStr, true, "trafficLight != noStr", binaryAlpha);
	// onlyEven and onlyEven2: They are equal under the binary alphabet, but not the English alphabet
	// because onlyEven2 is defined to only move a state when there is a character of either 1 or 0
	DFA<int, int>* onlyEven2 = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1); },
		0,
		[](int s, int c) {
			if (s == 0 && (c == 0 || c == 1))
				return 1;
			else if (s == 1 && (c == 0 || c == 1))
				return 0;
			else
				return 0;
		},
		[](int s) {return s == 0; }
		);
	testEquality(onlyEven, onlyEven2, true, "onlyEven != onlyEven2", binaryAlpha);
	// onlyEmpty == onlyEmpty2: the DFA's are defined differently, however, accept the same L
	DFA<int, int>* onlyEmpty2 = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1); },
		0,
		[](int s, int c) {
			return 1;
		},
		[](int s) {return s == 0; }
		);
	testEquality(onlyEmpty, onlyEmpty2, true, "onlyEmpty != onlyEmpty2", binaryAlpha);
	// onlyEmpty == onlyEmpty2: These DFA's accept any L due to it not caring 
	// as to what the alphabet is.
	testEquality(onlyEmpty, onlyEmpty2, true, "onlyEmpty != onlyEmpty2", englishAlpha);
	//myName == myName2: I used a different start state, and different states, 
	// but its essentially the same DFA just reversed. You could also think of it as
	// the same direction but the states are named differently
	DFA<int, int>* myName2 = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2); },
		3,
		[](int s, int c) {
			if ((c == 67) && (s == 3))
				return 2;
			else if ((c == 74) && (s == 2))
				return 1;
			else
				return 0;
		},
		[](int s) {return s == 1; }
		);
	testEquality(myName, myName2, true, "myName != myName2", englishAlpha);
	// ARGH == noStr:
	// because ARGH is defined to only move states if it sees char of 'A','R','G',or 'H', otherwise it fails. 
	// therefore under the alphabet of binary, where there is only the characters of 1 and 0, it accepts no str
	testEquality(ARGH, noStr, true, "ARGH != noStr", binaryAlpha);
	/*
		6 cases of DFAs that are not equal, L(DFA_a) != L(DFA_b)
	*/
	// onlyZeros != onlyZeros2: onlyZeros2 accepts strings of only zeros and the empty str 
	// Theres only the different of that one accept that makes these not equal
	DFA<int, int>* onlyZeros2 = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1); },
		0,
		[](int s, int c) {
			if ((c == 0) && (s == 0))
				return 0;
			else
				return 1;
		},
		[](int s) {return s == 0; }
		);
	testEquality(onlyZeros, onlyZeros2, false, "onlyZeros == onlyZeros2", binaryAlpha);
	// onlyEven != onlyEven2: false because of the alphabet, however, equality holds true under binary
	testEquality(onlyEven, onlyEven2, false, "onlyEven == onlyEven2", englishAlpha);
	// myName != notMyName: a case that should obviously be false
	testEquality(myName, notMyName, false, "myName == notMyName", englishAlpha);
	// onlyEmpty != noStr: Only different is that empty str is accepted by one DFA
	testEquality(onlyEmpty, noStr, false, "onlyEmpty == noStr", binaryAlpha);
	// the L(zeroOne) = the set of all str's that have a consecutive zero and one anywhere in it.
	// L(signedBinary) = the set of str's starting with a 1
	testEquality(zeroOne, signedBinary, false, "oneZero == signedBinary", binaryAlpha);
	// L(binaryStrs) = the set of strings that are of only binary char's, being 1 or 0, no empty str.
	// L(onlyZeros) = the set of strings that contain at least one 0, no accept of empty str
	DFA<int, int>* binaryStrs = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1); },
		0,
		[](int s, int c) {
			if ((c == 0 || c == 1) && (s == 0))
				return 0;
			else
				return 1;
		},
		[](int s) {return s == 0; }
		);
	// onlyZero's is a subset of binaryStrs,
	testSubset(onlyZeros, binaryStrs, true, "onlyZeros !subset binaryStrs", binaryAlpha);
	// but binaryStrs is not a subset of onlyZeros,
	testSubset(binaryStrs, onlyZeros, false, "onlyZeros subset binaryStrs", binaryAlpha);
	// therefore, they are not equal. 
	testEquality(onlyZeros, binaryStrs, false, "onlyZeros == binaryStrs", binaryAlpha);
	/*
		TASK #22 - Verify your complement, union, and intersect functions using the equality function.
	*/
	// This is a different definition of notMyNameDFA. 
	// The complement of this DFA will be equal to the DFA myName
	DFA<int, int>* notMyName2 = new DFA<int, int>(
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
		[](int s) {return s == 0 || s == 1 || s == 3; }
		);
	testEquality(complement(notMyName2), myName, true, "~notMyName != myName", englishAlpha);
	// L(notOnlyEmpty) = the set of all binary strings, except the empty string
	DFA<int, int>* notOnlyEmpty = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1); },
		0,
		[](int s, int c) {
			if (s == 0)
				return 1;
			else
				return 1;
		},
		[](int s) {return s == 1; }
		);
	testEquality(complement(notOnlyEmpty), onlyEmpty, true, "~notOnlyEmpty != onlyEmpty", binaryAlpha);
	// trafficLight accepts no strings, meaning ~trafficLight accepts all strings
	// noStr also accepts no strings, so the complement, ~noStr, accepts all strings. 
	testEquality(complement(trafficLight), complement(noStr), true, "~trafficLight != ~noStr", binaryAlpha);
	//oneZero accepts strings that have the character of 1 and 0 after one another, accepts empty string
	DFA<int, int>* oneZero = new DFA<int, int>(
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
			else if ((c == 1) && (s == 2))
				return 2;
			else if ((c == 0) && (s == 2))
				return 2;
		},
		[](int s) {return s == 0 || s == 1; }
		);
	testEquality(zeroOne, complement(oneZero), true, "zeroOne != ~oneZero", binaryAlpha);
	// L(binaryStrsNoEmpty) = The set of strings that are of only 1's and/or 0's, being a binary str.
	// with no accept for the empty str
	DFA<int, int>* binaryStrsNoEmpty = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2); },
		0,
		[](int s, int c) {
			if ((c == 0 || c == 1) && (s == 0 || s == 1))
				return 1;
			else
				return 2;
		},
		[](int s) {return s == 1; }
		);
	// onlyZeros U signedBinary U zeroOne == binaryStrsNoEmpty
	testEquality(unionDFA(onlyZeros_U_signedBinary, zeroOne), binaryStrsNoEmpty,
		true, "onlyZerosUsignedBinaryUzeroOne != binaryStrs", binaryAlpha);
	// a test that should be obviously true 
	testEquality(unionDFA(myName, myName), myName, true, "myName U myName != myName", englishAlpha);
	// onlyEvenUonlyZeros2 is a DFA that is equal to the union of onlyZeros and onlyEven
	DFA<int, int>* onlyEvenUonlyZeros2 = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3); },
		0,
		[](int s, int c) {
			if ((s == 0) && (c == 0))
				return 1;
			else if ((s == 0) && (c == 1))
				return 3;
			else if ((s == 1) && (c == 0))
				return 0;
			else if ((s == 1) && (c == 1))
				return 2;
			else if ((s == 2) && (c == 0 || c == 1))
				return 3;
			else if ((s == 3) && (c == 0 || c == 1))
				return 2;
		},
		[](int s) {return s == 0 || s == 1 || s == 2; }
		);
	testEquality(unionDFA(onlyEven, onlyZeros), onlyEvenUonlyZeros2, true, 
		"onlyEvenUonlyZeros != onlyEvenUonlyZeros2", binaryAlpha);
	// This is a DFA that should have equality with the union of onlyZeros and onlyEmpty
	DFA<int, int>* onlyZerosUonlyEmpty2 = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3) || (s == 4) || (s == 5); },
		0,
		[](int s, int c) {
			if ((s == 0) && (c == 0))
				return 3;
			else if ((s == 0) && (c == 1))
				return 5;
			else if ((s == 1) && (c == 0))
				return 3;
			else if ((s == 1) && (c == 1))
				return 5;
			else if ((s == 2) && (c == 0))
				return 3;
			else if ((s == 2) && (c == 1))
				return 5;
			else if ((s == 3) && (c == 0))
				return 3;
			else if ((s == 3) && (c == 1))
				return 5;
			else if ((s == 4) && (c == 0 || c == 1))
				return 5;
			else if ((s == 5) && (c == 0 || c == 1))
				return 5;
		},
		[](int s) {return s == 0 || s == 2 || s == 3 || s == 4; }
		);
	testEquality(unionDFA(onlyEmpty, onlyZeros), onlyZerosUonlyEmpty2, true,
		"onlyEmpty U OnlyZeros != onlyZerosUonlyEmpty2", binaryAlpha);
	// L(onlyZeros ^ onlyEven) = the set of strings that have even length and only zero, no empty str
	// L(onlyEvenZeros) = the set of strings that have even length and only zero, no empty str
	DFA<int, int>* onlyEvenZeros = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3); },
		0,
		[](int s, int c) {
			if ((s == 0) && (c == 0))
				return 1;
			else if ((s == 1) && (c == 0))
				return 2;
			else if ((s == 2) && (c == 0))
				return 1;
			else
				return 3;
		},
		[](int s) {return s == 2; }
		);
	testEquality(intersect(onlyEven, onlyZeros), onlyEvenZeros, true, 
		"onlyEven ^ onlyZeros != onlyEvenZeros", binaryAlpha);
	//This DFA should be equal to the intersection of zeroOne and signedBinary
	DFA<int, int>* zeroOneINTsigned = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3) ||  
		(s == 4) || (s == 5) || (s == 6) || (s == 7) || (s == 8); },
		0,
		[](int s, int c) {
			if ((s == 0) && (c == 0))
				return 5;
			else if ((s == 0) && (c == 1))
				return 1;
			else if ((s == 1) && (c == 0))
				return 4;
			else if ((s == 1) && (c == 1))
				return 1;
			else if ((s == 2) && (c == 0))
				return 5;
			else if ((s == 2) && (c == 1))
				return 2;
			else if ((s == 3) && (c == 0))
				return 5;
			else if ((s == 3) && (c == 1))
				return 7;
			else if ((s == 4) && (c == 0))
				return 4;
			else if ((s == 4) && (c == 1))
				return 7;
			else if ((s == 5) && (c == 0))
				return 5;
			else if ((s == 5) && (c == 1))
				return 8;
			else if ((s == 6) && (c == 0))
				return 8;
			else if ((s == 6) && (c == 1))
				return 7;
			else if ((s == 7) && (c == 0 || c == 1))
				return 7;
			else if ((s == 8) && (c == 0 || c == 1))
				return 8;
		},
		[](int s) {return s == 7; }
		);
	testEquality(intersect(zeroOne, signedBinary), zeroOneINTsigned, true, 
		"zeroOne ^ signedBinary != zeroOneINTsigned", binaryAlpha);
	// myName_INT_onlyEmpty is an intersection that results in accepting no str
	// myName_U_cMyName is a union that results in accepting all strings. 
	// Therefore the complement of myName_U_cMyName is a DFA that accepts no strings. 
	testEquality(myName_INT_onlyEmpty, complement(myName_U_cMyName), true,
		"myName_INT_onlyEmpty  != ~myName_U_cMyName", binaryAlpha);
	// ~(zeroOne intersect with zeroOne) == ~(zeroOne union with zeroOne)
	testEquality(complement(intersect(zeroOne, zeroOne)), complement(unionDFA(zeroOne, zeroOne)), true,
		"zeroOne_INT_zeroOne  != ~zeroOne_U_zeroOne ", binaryAlpha);
	// intersect zeroOne with itself is equal to itself
	testEquality(intersect(zeroOne, zeroOne), intersect(zeroOne, zeroOne), true,
		"zeroOne_INT_zeroOne  != ~zeroOne_U_zeroOne ", binaryAlpha);
	cout << endl;
	/*
		testing TASK 24
	*/
	NFA<int, int>* onlyEvenNFA = DFAtoNFA(onlyEven);
	if (!(onlyEvenNFA->Q(0) && onlyEvenNFA->Q(1) && (!onlyEvenNFA->Q(2)))) {
		cout << "### FAIL DFAtoNFA: Q ###";
	}
	if (onlyEvenNFA->q0 != 0) {
		cout << "### FAIL DFAtoNFA: q0 ###";
	}
	int tempState = onlyEvenNFA->q0;
	list<int> tempStr = {1,0,1,0};
	list<int> setState;
	while (!tempStr.empty()) {
		setState = onlyEvenNFA->d1(tempState, tempStr.front()); 
		tempStr.pop_front();
		tempState = setState.front();
	}
	if (!onlyEvenNFA->F(tempState)) {
		cout << "### FAIL DFAtoNFA: F ###";
	}
	if (onlyEvenNFA->d2(0) != list<int>{}) {
		cout << "### FAIL DFAtoNFA: d2 ###";
	}
	/*
		TASK #25 - Write a dozen example NFAs.
	*/
	// example N1 in the textbook
	NFA<int, int>* N1 = new NFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3); },
		0,
		[](int s, int c) {
			if ((s == 0) && (c == 0))
				return list<int>{0};
			else if ((s == 0) && (c == 1))
				return list<int> {0, 1};
			else if ((s == 1) && (c == 0))
				return list<int>{2};
			else if ((s == 2) && (c == 1))
				return list<int>{3};
			else if ((s == 3) && (c == 0 || c == 1))
				return list<int>{3};
			else
				return list<int>{};
		},
		[](int s) {
			if (s == 1)
				return list<int>{ 2 };
			else
				return list<int>{};
		},
			[](int s) {return s == 3; }
		);
	// using -1 as a flag for upcoming epsilon transition
	// traces that are accepting
	list<Config<int>> C1N1 = createTrace(list<int>{0,1,2,3,3}, list<int>{1,0,1,1});
	list<Config<int>> C2N1 = createTrace(list<int>{0,-1, 1, 2,3,3}, list<int>{1, 1, 1});
	list<Config<int>> C3N1 = createTrace(list<int>{0, 0, 1, 2, 3, 3, 3}, list<int>{0,1,0,1,1,0});
	list<Config<int>> C4N1 = createTrace(list<int>{0,0,0,0,1,2,3}, list<int>{0,0,0,1,0,1});
	list<Config<int>> C5N1 = createTrace(list<int>{0,0,0,0,-1, 1,2,3,3}, list<int>{0,1,0,1,1,0});
	list<Config<int>> C6N1 = createTrace(list<int>{0,0,0,1,2,3,3}, list<int>{1,0,1,0,1,0});
	// traces that are rejecting
	list<Config<int>> C7N1 = createTrace(list<int>{0,0,0,0,1}, list<int>{1, 0, 1, 1});
	list<Config<int>> C8N1 = createTrace(list<int>{0,0,0,1}, list<int>{1, 1, 1});
	list<Config<int>> C9N1 = createTrace(list<int>{0,0,0,0,0,1,2}, list<int>{0, 1, 0, 1, 1, 0});
	list<Config<int>> C10N1 = createTrace(list<int>{0,0,0,0,0,0,0}, list<int>{0, 0, 0, 1, 0, 1});
	list<Config<int>> C11N1 = createTrace(list<int>{0,0,0,0,0,1,2}, list<int>{0, 1, 0, 1, 1, 0});
	list<Config<int>> C12N1 = createTrace(list<int>{0,0,0,0,0,1,2}, list<int>{1, 0, 1, 0, 1, 0});
	oracleLoop( 
		N1,"N1",
		{ {1,0,1,1}, {1, 1, 1}, {0,1,0,1,1,0}, {0,0,0,1,0,1}, {0,1,0,1,1,0}, {1,0,1,0,1,0}, 
		{1, 0, 1, 1}, {1, 1, 1}, {0, 1, 0, 1, 1, 0}, {0, 0, 0, 1, 0, 1}, {0, 1, 0, 1, 1, 0}, {1, 0, 1, 0, 1, 0} },
		{C1N1,C2N1,C3N1,C4N1,C5N1,C6N1,C7N1,C8N1,C9N1,C10N1,C11N1,C12N1 }
	);
	// example N2 in the textbook, L(N2) = strings over {0,1} with a 1 third from the end
	NFA<int, int>* N2 = new NFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3); },
		0,
		[](int s, int c) {
			if ((s == 0) && (c == 0))
				return list<int>{0};
			else if ((s == 0) && (c == 1))
				return list<int> {0, 1};
			else if ((s == 1) && (c == 0 || c == 1))
				return list<int>{2};
			else if ((s == 2) && (c == 0 || c == 1))
				return list<int>{3};
			else
				return list<int>{};
		},
		[](int s) {
			return list<int>{};
		},
			[](int s) {return s == 3; }
		);
	// traces that are accepting
	list<Config<int>> C1N2 = createTrace(list<int>{0,1,2,3}, list<int>{1,0,0});
	list<Config<int>> C2N2 = createTrace(list<int>{0,1,2,3}, list<int>{1,0,1});
	list<Config<int>> C3N2 = createTrace(list<int>{0,1,2,3}, list<int>{1,1,1});
	list<Config<int>> C4N2 = createTrace(list<int>{0,0,0,0,0,1,2,3}, list<int>{0,0,0,0,1,0,0});
	list<Config<int>> C5N2 = createTrace(list<int>{0,0,1,2,3}, list<int>{0,1,0,0});
	list<Config<int>> C6N2 = createTrace(list<int>{0,0,1,2,3}, list<int>{0,1,1,0});
	// traces that are rejecting
	list<Config<int>> C7N2 = createTrace(list<int>{0,0,1,2}, list<int>{0,1,1});
	list<Config<int>> C8N2 = createTrace(list<int>{0,0,0,0}, list<int>{1,0,0});
	list<Config<int>> C9N2 = createTrace(list<int>{0,0,1,2}, list<int>{1,1,1});
	list<Config<int>> C10N2 = createTrace(list<int>{0,0,0,1}, list<int>{1,0,1});
	list<Config<int>> C11N2 = createTrace(list<int>{0,0,0,0,0}, list<int>{0,1,0,0});
	list<Config<int>> C12N2 = createTrace(list<int>{0,0,0,1,2}, list<int>{0,1,1,0});
	oracleLoop(
		N2, "N2",
		{ C1N2.front().curStr,C2N2.front().curStr,C3N2.front().curStr,C4N2.front().curStr,
		C5N2.front().curStr,C6N2.front().curStr,C7N2.front().curStr,C8N2.front().curStr,C9N2.front().curStr,
		C10N2.front().curStr,C11N2.front().curStr,C12N2.front().curStr },
		{ C1N2,C2N2,C3N2,C4N2,C5N2,C6N2,C7N2,C8N2,C9N2,C10N2,C11N2,C12N2 }
	);
	// example in textbook N3
	// aceepts strings that are multiples of 2 or 3
	NFA<int, int>* N3 = new NFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3) || (s == 4) || (s == 5); },
		0,
		[](int s, int c) {
			if (s == 1 && c == 0)
				return list<int>{2};
			else if (s == 2 && c == 0)
				return list<int> {1};
			else if (s == 3 && c == 0)
				return list<int>{4};
			else if (s == 4 && c == 0)
				return list<int>{5};
			else if (s == 5 && c == 0)
				return list<int>{3};
			else
				return list<int>{};
		},
		[](int s) {
			if (s == 0)
				return list<int>{ 1,3 };
			else
				return list<int>{};
		},
			[](int s) {return s == 1 || s == 3; }
		);
	// traces that are accepting
	list<Config<int>> C1N3 = createTrace(list<int>{-1,0,1,2,1}, list<int>{0,0});
	list<Config<int>> C2N3 = createTrace(list<int>{-1,0,3,4,5,3}, list<int>{0,0,0});
	list<Config<int>> C3N3 = createTrace(list<int>{-1,0,1,2,1,2,1}, list<int>{0,0,0,0});
	list<Config<int>> C4N3 = createTrace(list<int>{-1,0,3,4,5,3,4,5,3}, list<int>{0,0,0,0,0,0,});
	list<Config<int>> C5N3 = createTrace(list<int>{-1,0,1,2,1,2,1,2,1}, list<int>{0,0,0,0,0,0});
	list<Config<int>> C6N3 = createTrace(list<int>{-1,0,1,2,1,2,1,2,1,2,1}, list<int>{0,0,0,0,0,0,0,0});
	// traces that are rejecting
	list<Config<int>> C7N3 = createTrace(list<int>{-1,0,3,4,5}, list<int>{0,0});
	list<Config<int>> C8N3 = createTrace(list<int>{-1,0,1,2,1,2}, list<int>{0,0,0});
	list<Config<int>> C9N3 = createTrace(list<int>{-1,0,3,4,5,3,4}, list<int>{0,0,0,0});
	list<Config<int>> C10N3 = createTrace(list<int>{-1,0,1,2,1,2,1,2}, list<int>{0,0,0,0,0});
	list<Config<int>> C11N3 = createTrace(list<int>{-1,0,3,4,5,3,4,5}, list<int>{0,0,0,0,0});
	list<Config<int>> C12N3 = createTrace(list<int>{-1,0,1,2}, list<int>{0});
	oracleLoop(
		N3, "N3",
		{ C1N3.front().curStr,C2N3.front().curStr,C3N3.front().curStr,C4N3.front().curStr,
		C5N3.front().curStr,C6N3.front().curStr,C7N3.front().curStr,C8N3.front().curStr,C9N3.front().curStr,
		C10N3.front().curStr,C11N3.front().curStr,C12N3.front().curStr },
		{ C1N3,C2N3,C3N3,C4N3,C5N3,C6N3,C7N3,C8N3,C9N3,C10N3,C11N3,C12N3 }
	);
	// Example from textbook. accepts: epsilon, {0}, {1010}, {100}; doesnt accept: {1}, {11}, {10110}
	NFA<int, int>* N4 = new NFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2); },
		0,
		[](int s, int c) {
			if ((s == 0) && (c == 1))
				return list<int>{1};
			else if (s == 1 && c == 0)
				return list<int>{1, 2};
			else if ((s == 1) && (c == 1))
				return list<int>{2};
			else if (s == 2 && c == 0)
				return list<int>{0};
			else
				return list<int>{};
		},
		[](int s) {
			if (s == 0)
				return list<int>{ 2 };
			else
				return list<int>{};
		},
			[](int s) {return s == 0; }
		);
	// traces that are accepting
	list<Config<int>> C1N4 = createTrace(list<int>{0,1,1,2,0}, list<int>{1,0,1,0});
	list<Config<int>> C2N4 = createTrace(list<int>{-1,0,2,0}, list<int>{0});
	list<Config<int>> C3N4 = createTrace(list<int>{0}, list<int>{});
	list<Config<int>> C4N4 = createTrace(list<int>{0,1,2,0}, list<int>{1,0,0});
	list<Config<int>> C5N4 = createTrace(list<int>{0,1,2,0}, list<int>{1,1,0});
	list<Config<int>> C6N4 = createTrace(list<int>{-1,0,2,-1,0,2,0}, list<int>{0,0});
	// traces that are rejecting
	list<Config<int>> C7N4 = createTrace(list<int>{-1,0,2}, list<int>{1,0,1,0});
	list<Config<int>> C8N4 = createTrace(list<int>{-1,0,2}, list<int>{});
	list<Config<int>> C9N4 = createTrace(list<int>{0,1,1,2}, list<int>{1,0,0});
	list<Config<int>> C10N4 = createTrace(list<int>{-1,0,2}, list<int>{1,1,0});
	list<Config<int>> C11N4 = createTrace(list<int>{0,1,2}, list<int>{1,1});
	list<Config<int>> C12N4 = createTrace(list<int>{0,1,1,2}, list<int>{1,0,1});
	oracleLoop(
		N4, "N4",
		{ C1N4.front().curStr,C2N4.front().curStr,C3N4.front().curStr,C4N4.front().curStr,
		C5N4.front().curStr,C6N4.front().curStr,C7N4.front().curStr,C8N4.front().curStr,C9N4.front().curStr,
		C10N4.front().curStr,C11N4.front().curStr,C12N4.front().curStr },
		{ C1N4,C2N4,C3N4,C4N4,C5N4,C6N4,C7N4,C8N4,C9N4,C10N4,C11N4,C12N4 }
	);
	// NFA with a graph that is infinitly large
	NFA<int, int>* N5 = new NFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2); },
		0,
		[](int s, int c) {
			if (s == 0 && c == 0)
				return list<int>{1};
			else if (s == 1 && c == 1)
				return list<int>{2};
			else
				return list<int>{};
		},
		[](int s) {
			if(s == 0)
				return list<int>{1};
			else if(s == 1)
				return list<int>{0};
			else
				return list<int>{};
		},
			[](int s) {return s == 2; }
		);
	// traces that are accepting
	list<Config<int>> C1N5 = createTrace(list<int>{0,1,2}, list<int>{0,1});
	list<Config<int>> C2N5 = createTrace(list<int>{-1,0,1,2}, list<int>{1});
	list<Config<int>> C3N5 = createTrace(list<int>{0,-1,1,0,-1,1,0,1,2}, list<int>{0,0,0,1});
	list<Config<int>> C4N5 = createTrace(list<int>{0,-1,1,0,1,2}, list<int>{0,0,1});
	list<Config<int>> C5N5 = createTrace(list<int>{0,-1,1,0,-1,1,0,-1,1,0,1,2}, 
		list<int>{0,0,0,0,1});
	list<Config<int>> C6N5 = createTrace(list<int>{0,-1,1,0,-1,1,0,-1,1,0,-1,1,0,1,2}, list<int>{0,0,0,0,0,1});
	//list<Config<int>> C6N5 = createTrace(list<int>{0, -1, 1,-1, 0, 1}, list<int>{0, 0, 0, 0, 0, 1});
	// traces that are rejecting
	list<Config<int>> C7N5 = createTrace(list<int>{-1,0,1,2}, list<int>{1,1});
	list<Config<int>> C8N5 = createTrace(list<int>{-1,0,1,2}, list<int>{1,0,1});
	list<Config<int>> C9N5 = createTrace(list<int>{0,-1,1,-1,0,1,2}, list<int>{0,1,0});
	list<Config<int>> C10N5 = createTrace(list<int>{-1,0,1,2}, list<int>{1,1,1});
	list<Config<int>> C11N5 = createTrace(list<int>{-1,0,1,2}, list<int>{1,0});
	list<Config<int>> C12N5 = createTrace(list<int>{0,1}, list<int>{0});
	oracleLoop(
		N5, "N5",
		{ C1N5.front().curStr,C2N5.front().curStr,C3N5.front().curStr,C4N5.front().curStr,
		C5N5.front().curStr,C6N5.front().curStr,C7N5.front().curStr,C8N5.front().curStr,C9N5.front().curStr,
		C10N5.front().curStr,C11N5.front().curStr,C12N5.front().curStr },
		{ C1N5,C2N5,C3N5,C4N5,C5N5,C6N5,C7N5,C8N5,C9N5,C10N5,C11N5,C12N5 }
	);
	// L(N6) = strings of a finite length that end in either '11' or '00'
	NFA<int, int>* N6 = new NFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3) ||
			(s == 4) || (s == 5) || (s == 6); },
		0,
		[](int s, int c) {
			if (s == 1 && c == 0)
				return list<int>{1, 2};
			else if (s == 1 && c == 1)
				return list<int>{1};
			else if(s == 2 && c == 0)
				return list<int>{3};
			else if (s == 4 && c == 0)
				return list<int>{4};
			else if (s == 4 && c == 1)
				return list<int>{4, 5};
			else if (s == 5 && c == 1)
				return list<int>{6};
			else
				return list<int>{};
		},
		[](int s) {
			if (s == 0)
				return list<int>{1, 4};
			else
				return list<int>{};
		},
		[](int s) {return s == 3 || s == 6; }
		);
	// traces that are accepting
	list<Config<int>> C1N6 = createTrace(list<int>{-1,0,4,5,6}, list<int>{1,1});
	list<Config<int>> C2N6 = createTrace(list<int>{-1,0,1,2,3}, list<int>{0,0});
	list<Config<int>> C3N6 = createTrace(list<int>{-1,0,4,4,5,6}, list<int>{0,1,1});
	list<Config<int>> C4N6 = createTrace(list<int>{-1,0,1,1,2,3}, list<int>{1,0,0});
	list<Config<int>> C5N6 = createTrace(list<int>{-1,0,1,1,1,2,3}, list<int>{0,1,0,0});
	list<Config<int>> C6N6 = createTrace(list<int>{-1,0,4,4,4,5,6}, list<int>{1,0,1,1});
	// traces that are rejecting
	list<Config<int>> C7N6 = createTrace(list<int>{-1,0,1,1,1}, list<int>{1,1});
	list<Config<int>> C8N6 = createTrace(list<int>{-1,0,4,4,4}, list<int>{0,0});
	list<Config<int>> C9N6 = createTrace(list<int>{-1,0,4,4,4,4}, list<int>{0,1,1});
	list<Config<int>> C10N6 = createTrace(list<int>{-1,0,4,4,4,5}, list<int>{0,1,1});
	list<Config<int>> C11N6 = createTrace(list<int>{-1,0,1}, list<int>{});
	list<Config<int>> C12N6 = createTrace(list<int>{-1,0,4,5}, list<int>{1});
	oracleLoop(
		N6, "N6",
		{ C1N6.front().curStr,C2N6.front().curStr,C3N6.front().curStr,C4N6.front().curStr,
		C5N6.front().curStr,C6N6.front().curStr,C7N6.front().curStr,C8N6.front().curStr,C9N6.front().curStr,
		C10N6.front().curStr,C11N6.front().curStr,C12N6.front().curStr },
		{ C1N6,C2N6,C3N6,C4N6,C5N6,C6N6,C7N6,C8N6,C9N6,C10N6,C11N6,C12N6 }
	);
	// L(N7) = only the strings {00},{01},{10},{11}
	NFA<int, int>* N7 = new NFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3) || (s == 4); },
		0,
		[](int s, int c) {
			if (s == 0 && (c == 0 || c == 1))
				return list<int>{1, 3};
			else if (s == 1 && c == 1)
				return list<int>{2};
			else if (s == 3 && c == 0)
				return list<int>{4};
			else
				return list<int>{};
		},
		[](int s) {
				return list<int>{};
		},
			[](int s) {return s == 2 || s == 4; }
		);
	// traces that are accepting
	list<Config<int>> C1N7 = createTrace(list<int>{0,3,4}, list<int>{0,0});
	list<Config<int>> C2N7 = createTrace(list<int>{0,1,2}, list<int>{0,1});
	list<Config<int>> C3N7 = createTrace(list<int>{0,3,4}, list<int>{1,0});
	list<Config<int>> C4N7 = createTrace(list<int>{0,1,2}, list<int>{1,1});
	list<Config<int>> C5N7 = createTrace(list<int>{0,1}, list<int>{0});
	list<Config<int>> C6N7 = createTrace(list<int>{0,3}, list<int>{0});
	// traces that are rejecting
	list<Config<int>> C7N7 = createTrace(list<int>{0,1}, list<int>{1});
	list<Config<int>> C8N7 = createTrace(list<int>{0,3}, list<int>{1});
	list<Config<int>> C9N7 = createTrace(list<int>{0}, list<int>{});
	list<Config<int>> C10N7 = createTrace(list<int>{0,3,4}, list<int>{0,0,0});
	list<Config<int>> C11N7 = createTrace(list<int>{0,1}, list<int>{0,0,0});
	list<Config<int>> C12N7 = createTrace(list<int>{0,1}, list<int>{0,0});
	oracleLoop(
		N7, "N7",
		{ C1N7.front().curStr,C2N7.front().curStr,C3N7.front().curStr,C4N7.front().curStr,
		C5N7.front().curStr,C6N7.front().curStr,C7N7.front().curStr,C8N7.front().curStr,C9N7.front().curStr,
		C10N7.front().curStr,C11N7.front().curStr,C12N7.front().curStr },
		{ C1N7,C2N7,C3N7,C4N7,C5N7,C6N7,C7N7,C8N7,C9N7,C10N7,C11N7,C12N7 }
	);
	// L(N8) = all strings that if they are even, will be all 1's, and if they are odd, they are all 0's
	// accepts: {0}, {000}, {00000}, {11}, {1111}, {111111}; does NOT accept: {01}, {00}, {111}, {1}
	NFA<int, int>* N8 = new NFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3) || (s == 4); },
		0,
		[](int s, int c) {
			if (s == 1 && c == 1)
				return list<int>{2};
			else if (s == 2 && c == 1)
				return list<int>{1};
			else if (s == 3 && c == 0)
				return list<int>{4};
			else if (s == 4 && c == 0)
				return list<int>{3};
			else
				return list<int>{};
		},
		[](int s) {
			if (s == 0)
				return list<int>{1, 3};
			else
				return list<int>{};
		},
			[](int s) {return s == 1 || s == 4; }
		);
	// traces that are accepting
	list<Config<int>> C1N8 = createTrace(list<int>{-1,0,1,2,1}, list<int>{1,1});
	list<Config<int>> C2N8 = createTrace(list<int>{-1,0,1,2,1,2,1}, list<int>{1,1,1,1});
	list<Config<int>> C3N8 = createTrace(list<int>{-1,0,3,4}, list<int>{0});
	list<Config<int>> C4N8 = createTrace(list<int>{-1,0,3,4,3,4}, list<int>{0,0,0});
	list<Config<int>> C5N8 = createTrace(list<int>{-1,0,3,4,3}, list<int>{0,0,0,0,0});
	list<Config<int>> C6N8 = createTrace(list<int>{-1,0,1,2,1,2,1,2,1}, list<int>{1,1,1,1,1,1});
	// traces that are rejecting
	list<Config<int>> C7N8 = createTrace(list<int>{-1,0,3}, list<int>{1,1});
	list<Config<int>> C8N8 = createTrace(list<int>{-1,0,1}, list<int>{0,0});
	list<Config<int>> C9N8 = createTrace(list<int>{-1,0,1,2}, list<int>{1,0});
	list<Config<int>> C10N8 = createTrace(list<int>{-1,0,1}, list<int>{0});
	list<Config<int>> C11N8 = createTrace(list<int>{-1,0,1}, list<int>{0,0,0});
	list<Config<int>> C12N8 = createTrace(list<int>{-1,0,3}, list<int>{1,0});
	oracleLoop(
		N8, "N8",
		{ C1N8.front().curStr,C2N8.front().curStr,C3N8.front().curStr,C4N8.front().curStr,
		C5N8.front().curStr,C6N8.front().curStr,C7N8.front().curStr,C8N8.front().curStr,C9N8.front().curStr,
		C10N8.front().curStr,C11N8.front().curStr,C12N8.front().curStr },
		{ C1N8,C2N8,C3N8,C4N8,C5N8,C6N8,C7N8,C8N8,C9N8,C10N8,C11N8,C12N8 }
	);
	// L(N9) = all strings that start and end with the char 1, with any 
	// amount of char's in between, over sigma{0, 1}.  
	NFA<int, int>* N9 = new NFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2); },
		0,
		[](int s, int c) {
			if (s == 0 && c == 1)
				return list<int>{1};
			else if (s == 1 && c == 0)
				return list<int>{1};
			else if (s == 1 && c == 1)
				return list<int>{1, 2};
			else
				return list<int>{};
		},
		[](int s) {
			return list<int>{};
		},
			[](int s) {return s == 2; }
		);
	// traces that are accepting
	list<Config<int>> C1N9 = createTrace(list<int>{0,1,1,2}, list<int>{1,1,1});
	list<Config<int>> C2N9 = createTrace(list<int>{0,1,1,2}, list<int>{1,1,1});
	list<Config<int>> C3N9 = createTrace(list<int>{0,1,1,1,2}, list<int>{1,0,0,1});
	list<Config<int>> C4N9 = createTrace(list<int>{0,1,1,1,1,2}, list<int>{1,0,1,0,1});
	list<Config<int>> C5N9 = createTrace(list<int>{0,1,1,1,2}, list<int>{1,0,1,1});
	list<Config<int>> C6N9 = createTrace(list<int>{0,1,2}, list<int>{1,1});
	// traces that are rejecting
	list<Config<int>> C7N9 = createTrace(list<int>{0,1,1}, list<int>{1,1});
	list<Config<int>> C8N9 = createTrace(list<int>{0,1,2}, list<int>{1,1,1});
	list<Config<int>> C9N9 = createTrace(list<int>{0,1,1,1}, list<int>{1,1,1});
	list<Config<int>> C10N9 = createTrace(list<int>{0}, list<int>{0});
	list<Config<int>> C11N9 = createTrace(list<int>{0}, list<int>{});
	list<Config<int>> C12N9 = createTrace(list<int>{0,1,1}, list<int>{1,0});
	oracleLoop(
		N9, "N9",
		{ C1N9.front().curStr,C2N9.front().curStr,C3N9.front().curStr,C4N9.front().curStr,
		C5N9.front().curStr,C6N9.front().curStr,C7N9.front().curStr,C8N9.front().curStr,C9N9.front().curStr,
		C10N9.front().curStr,C11N9.front().curStr,C12N9.front().curStr },
		{ C1N9,C2N9,C3N9,C4N9,C5N9,C6N9,C7N9,C8N9,C9N9,C10N9,C11N9,C12N9 }
	);
	// L(N10) = any string that alternates between 1 and 0, starting with either 1 or 0. 
	// accepts: {0}, {1}, {10}, {01},  {010}, {1010101}, {101010}; does NOT accept: {11}, {00}, {1011}
	NFA<int, int>* N10 = new NFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2); },
		0,
		[](int s, int c) {
			if (s == 1 && c == 0)
				return list<int>{2};
			else if (s == 2 && c == 1)
				return list<int>{1};
			else
				return list<int>{};
		},
		[](int s) {
			if (s == 0)
				return list<int>{1,2};
			else
				return list<int>{};
		},
			[](int s) {return s == 1 || s == 2; }
		);
	// traces that are accepting
	list<Config<int>> C1N10 = createTrace(list<int>{-1,0,1}, list<int>{});
	list<Config<int>> C2N10 = createTrace(list<int>{-1,0,2,1}, list<int>{1});
	list<Config<int>> C3N10 = createTrace(list<int>{-1,0,1,2}, list<int>{0});
	list<Config<int>> C4N10 = createTrace(list<int>{-1,0,2,1,2}, list<int>{1,0});
	list<Config<int>> C5N10 = createTrace(list<int>{-1,0,1,2,1}, list<int>{0,1});
	list<Config<int>> C6N10 = createTrace(list<int>{-1,0,2,1,2,1}, list<int>{1,0,1});
	// traces that are rejecting
	list<Config<int>> C7N10 = createTrace(list<int>{-1,0,1}, list<int>{1});
	list<Config<int>> C8N10 = createTrace(list<int>{-1,0,2}, list<int>{0});
	list<Config<int>> C9N10 = createTrace(list<int>{-1,0,1}, list<int>{1,0});
	list<Config<int>> C10N10 = createTrace(list<int>{-1,0,2}, list<int>{0,1});
	list<Config<int>> C11N10 = createTrace(list<int>{-1,0,2,1}, list<int>{1,1});
	list<Config<int>> C12N10 = createTrace(list<int>{-1,0,1}, list<int>{1,1});
	oracleLoop(
		N10, "N10",
		{ C1N10.front().curStr,C2N10.front().curStr,C3N10.front().curStr,C4N10.front().curStr,
		C5N10.front().curStr,C6N10.front().curStr,C7N10.front().curStr,C8N10.front().curStr,C9N10.front().curStr,
		C10N10.front().curStr,C11N10.front().curStr,C12N10.front().curStr },
		{ C1N10,C2N10,C3N10,C4N10,C5N10,C6N10,C7N10,C8N10,C9N10,C10N10,C11N10,C12N10 }
	);
	// N11 is an implementation of my signedBinary DFA intersected with my zeroOne DFA.
	// The definition was very long and I wanted to see, how much less code it would be.
	// The delta for the DFA version of this is 31 lines, and the delta for this one is 13 lines. 
	NFA<int, int>* N11 = new NFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3); },
		0,
		[](int s, int c) {
			if (s == 0 && c == 1)
				return list<int>{1};
			else if (s == 1 && c == 0)
				return list<int>{2};
			else if (s == 1 && c == 1)
				return list<int>{1};
			else if (s == 2 && c == 0)
				return list<int>{2};
			else if (s == 2 && c == 1)
				return list<int>{3};
			else if (s == 3 && (c == 0 || c == 1))
				return list<int>{3};
			else
				return list<int>{};
		},
		[](int s) {
			return list<int>{};
		},
			[](int s) {return s == 3; }
		);
	// traces that are accepting
	list<Config<int>> C1N11 = createTrace(list<int>{0,1,2,3}, list<int>{1,0,1});
	list<Config<int>> C2N11 = createTrace(list<int>{0,1,2,3,3}, list<int>{1,0,1,1});
	list<Config<int>> C3N11 = createTrace(list<int>{0,1,2,3,3}, list<int>{1,0,1,0});
	list<Config<int>> C4N11 = createTrace(list<int>{0,1,1,2,3,3}, list<int>{1,1,0,1,1});
	list<Config<int>> C5N11 = createTrace(list<int>{0,1,1,2,2,2,3}, list<int>{1,1,0,0,0,1});
	list<Config<int>> C6N11 = createTrace(list<int>{0,1,2,2,3}, list<int>{1,0,0,1});
	// traces that are rejecting
	list<Config<int>> C7N11 = createTrace(list<int>{0,1}, list<int>{1});
	list<Config<int>> C8N11 = createTrace(list<int>{0}, list<int>{0});
	list<Config<int>> C9N11 = createTrace(list<int>{0,1,1,1}, list<int>{1,1,1});
	list<Config<int>> C10N11 = createTrace(list<int>{0}, list<int>{0,1});
	list<Config<int>> C11N11 = createTrace(list<int>{0,1,1,2}, list<int>{1,1,0});
	list<Config<int>> C12N11 = createTrace(list<int>{0,1,2,2}, list<int>{1,0,0});
	oracleLoop(
		N11, "N11",
		{ C1N11.front().curStr,C2N11.front().curStr,C3N11.front().curStr,C4N11.front().curStr,
		C5N11.front().curStr,C6N11.front().curStr,C7N11.front().curStr,C8N11.front().curStr,C9N11.front().curStr,
		C10N11.front().curStr,C11N11.front().curStr,C12N11.front().curStr },
		{ C1N11,C2N11,C3N11,C4N11,C5N11,C6N11,C7N11,C8N11,C9N11,C10N11,C11N11,C12N11 }
	);
	// This is a similar take on the previous NFA that had multiple of 2 or 3 except with decimal
	// accept: {2468}, {222}, {24}, {68}, {666}, {693}; does not accept: {23}, {2469}, {932}
	NFA<int, int>* N12 = new NFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2); },
		0,
		[](int s, int c) {
			if (s == 1 && (c == 2 || c == 4 || c == 6 || c == 8))
				return list<int>{1};
			if (s == 2 && (c == 3 || c == 6 || c == 9))
				return list<int>{2};
			else
				return list<int>{};
		},
		[](int s) {
			if (s == 0)
				return list<int>{1, 2};
			else
				return list<int>{};
		},
			[](int s) {return s == 1 || s == 2; }
		);
	// traces that are accepting
	list<Config<int>> C1N12 = createTrace(list<int>{-1,0,1,1}, list<int>{2});
	list<Config<int>> C2N12 = createTrace(list<int>{-1,0,1,1,1}, list<int>{2,4});
	list<Config<int>> C3N12 = createTrace(list<int>{-1,0,1,1,1}, list<int>{6,8});
	list<Config<int>> C4N12 = createTrace(list<int>{-1,0,2,2,2,2,2,2}, list<int>{3,3,9,6,9});
	list<Config<int>> C5N12 = createTrace(list<int>{-1,0,1,1}, list<int>{6});
	list<Config<int>> C6N12 = createTrace(list<int>{-1,0,2,2}, list<int>{6});
	// traces that are rejecting
	list<Config<int>> C7N12 = createTrace(list<int>{-1,0,2}, list<int>{2});
	list<Config<int>> C8N12 = createTrace(list<int>{-1,0,1}, list<int>{3});
	list<Config<int>> C9N12 = createTrace(list<int>{-1,0,1,1}, list<int>{2,3});
	list<Config<int>> C10N12 = createTrace(list<int>{-1,0,2,2,2}, list<int>{6,3,2});
	list<Config<int>> C11N12 = createTrace(list<int>{-1,0,2,2}, list<int>{6,8});
	list<Config<int>> C12N12 = createTrace(list<int>{-1,0,1,1}, list<int>{6,9});
	oracleLoop(
		N12, "N12",
		{ C1N12.front().curStr,C2N12.front().curStr,C3N12.front().curStr,C4N12.front().curStr,
		C5N12.front().curStr,C6N12.front().curStr,C7N12.front().curStr,C8N12.front().curStr,C9N12.front().curStr,
		C10N12.front().curStr,C11N12.front().curStr,C12N12.front().curStr },
		{ C1N12,C2N12,C3N12,C4N12,C5N12,C6N12,C7N12,C8N12,C9N12,C10N12,C11N12,C12N12 }
	);
	//
	// 
	NFA<int, int>* N13 = new NFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2); },
		0,
		[](int s, int c) {
			if (s == 0 && c == 0)
				return list<int>{1};
			else if (s == 1 && c == 1)
				return list<int>{2};
			else
				return list<int>{};
		},
		[](int s) {
			if (s == 0)
				return list<int>{1};
			else
				return list<int>{};
		},
			[](int s) {return s == 2; }
		);

	//
	//
	NFA<int, int>* N14 = new NFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2); },
		0,
		[](int s, int c) {
			if (s == 0 && c == 1)
				return list<int>{1};
			else if (s == 1 && c == 1)
				return list<int>{1};
			else if (s == 2 && c == 0)
				return list<int>{2};
			else
				return list<int>{};
		},
		[](int s) {
			if (s == 1)
				return list<int>{2};
			else
				return list<int>{};
		},
			[](int s) {return s == 2; }
		);
	// N15 is the NFA example from lecture pg.7-6
	NFA<int, int>* N15 = new NFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3) || (s == 4); },
		0,
		[](int s, int c) {
			if (s == 0 && c == 1)
				return list<int>{3};
			else if (s == 1 && c == 0)
				return list<int>{2};
			else if (s == 2 && c == 0)
				return list<int>{1};
			else if (s == 2 && c == 1)
				return list<int>{4};
			else
				return list<int>{};
		},
		[](int s) {
			if (s == 0)
				return list<int>{1};
			else if (s == 3)
				return list<int>{2};
			else
				return list<int>{};
		},
			[](int s) {return s == 4; }
		);

	/*
		TASK 29 - For each example NFA, write a half-dozen trace trees of their behavior.
	*/

	// TT for NFA: N1 
	// str: {1011}
	shared_ptr<TT<int,int>> tt1Root =  make_shared<TT<int, int>>(N1->q0, N1->d1, N1->d2);
	tt1Root->createTreeL(1);
	//cout << "Root:"<< tt1Root->branch << endl;
	bool stop = false;
	for (auto i0 : tt1Root->treeL) {
		i0->createTreeL(0);
		//cout << "L1:" << (*i0)->branch << endl;
		for (auto i1 : i0->treeL) {
			if (i1->branch == 2 && stop == false) {
				stop = true;
			}
			else {
				i1->createTreeL(1);
			}
			//cout << "----L2:" << (*i1)->branch << endl;
			for (auto i2 : i1->treeL) {
				i2->createTreeL(1);
				//cout << "--------L3:" << (*i2)->branch << endl;
				for (auto i3 : i2->treeL) {
					if (i3->branch == 1) {
						i3->push({{i3->d.second(1)}});
					}
					if (i3->branch == 2) {
						i3->push({{i3->d.first(2,1)}});
					}
					//cout << "------------L4:" << i3->branch << endl;
					for (auto i4 : i3->treeL) {
						//cout << "----------------L5:" << i4->branch << endl;
					}
				}
			}
		}

	}
	// TT for NFA: N1 
	// str: {111}
	shared_ptr<TT<int, int>> tt2Root = make_shared<TT<int, int>>(N1->q0, N1->d1, N1->d2);
	tt2Root->createTreeL(1);
	//cout << "Root:" << tt2Root->branch << endl;
	for (auto i0 : tt2Root->treeL) {
		i0->createTreeL(1);
		//cout << "L1:" << i0->branch << endl;
		for (auto i1 : i0->treeL) {
			i1->createTreeL(1);
			//cout << "----L2:" << i1->branch << endl;
			for (auto i2 : i1->treeL) {
				if (i2->branch == 1) {
					i2->push({ {i2->d.second(1)} });
				}
				if (i2->branch == 2) {
					i2->push({ {i2->d.first(2,1)} });
				}
				if (i2->branch == 3) {
					i2->push({ {i2->d.first(3,1)} });
				}
				//cout << "--------L3:" << i2->branch << endl;
				for (auto i3 : i2->treeL) {
					//cout << "------------L4:" << i3->branch << endl;
				}
			}
		}

	}
	// TT for NFA: N1 
	// str: {110}
	shared_ptr<TT<int, int>> tt3Root = make_shared<TT<int, int>>(N1->q0, N1->d1, N1->d2);
	tt3Root->createTreeL(1);
	//cout << "Root:" << tt3Root->branch << endl;
	for (auto i0 : tt3Root->treeL) {
		i0->createTreeL(1);
		//cout << "L1:" << i0->branch << endl;
		for (auto i1 : i0->treeL) {
			if (i1->branch == 2) {
				i1->push({ {i1->d.first(2,1)} });
			}
			else {
				i1->createTreeL(0);
			}
			//cout << "----L2:" << i1->branch << endl;
			for (auto i2 : i1->treeL) {
				if (i2->branch == 3) {
					i2->push({ {i2->d.first(3,0)} });
				}
				//cout << "--------L3:" << i2->branch << endl;
				for (auto i3 : i2->treeL) {
					//cout << "------------L4:" << i3->branch << endl;
				}
			}
		}

	}
	// TT for NFA: N1 
	// str: {101010}
	shared_ptr<TT<int, int>> tt4Root = make_shared<TT<int, int>>(N1->q0, N1->d1, N1->d2);
	tt4Root->createTreeL(1);
	//cout << "Root:" << tt4Root->branch << endl;
	int num = 0;
	int num1 = 0;
	for (auto i1 : tt4Root->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			if ((i2->branch) == 2 && (num <= 1)) {
				i2->push({ {i2->d.first(2,0)} });
				
			}
			else {
				i2->createTreeL(1);
			}
			num++;
			//cout << "----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(0);
				//cout << "--------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					if ((i4->branch) == 2 && (num1 == 1)) {
						i4->push({ {i4->d.first(2,0)} });

					}
					else {
						i4->createTreeL(1);
					}
					num1++;
					//cout << "------------L4:" << i4->branch << endl;
					for (auto i5 : i4->treeL) {
						i5->createTreeL(0);
						//cout << "----------------L5:" << i5->branch << endl;
						for (auto i6 : i5->treeL) {
							//cout << "--------------------L6:" << i6->branch << endl;
						}
					}
				}
			}
		}

	}
	// TT for NFA: N1 
	// str: {11}
	shared_ptr<TT<int, int>> tt5Root = make_shared<TT<int, int>>(N1->q0, N1->d1, N1->d2);
	tt5Root->createTreeL(1);
	//cout << "Root:" << tt3Root->branch << endl;
	for (auto i1 : tt5Root->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			if (i2->branch == 2) {
				i2->push({ {i2->d.first(2,1)} });
			}
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}

	}
	// TT for NFA: N1 
	// str: {011}
	shared_ptr<TT<int, int>> tt6Root = make_shared<TT<int, int>>(N1->q0, N1->d1, N1->d2);
	tt6Root->createTreeL(0);
	//cout << "Root:" << tt6Root->branch << endl;
	for (auto i1 : tt6Root->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				if (i3->branch == 2) {
					i3->push({ {i3->d.first(2,1)} });
				}
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					//cout << "---------------L4:" << i4->branch << endl;
				}
			}
		}

	}
	// TT for NFA: N2 
	// str: {100}
	shared_ptr<TT<int, int>> tt1RootN2 = make_shared<TT<int, int>>(N2->q0, N2->d1, N2->d2);
	tt1RootN2->createTreeL(1);
	//cout << "Root:" << tt1RootN2->branch << endl;
	for (auto i1 : tt1RootN2->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(0);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}

	}
	// TT for NFA: N2 
	// str: {101}
	shared_ptr<TT<int, int>> tt2RootN2 = make_shared<TT<int, int>>(N2->q0, N2->d1, N2->d2);
	tt2RootN2->createTreeL(1);
	//cout << "Root:" << tt2RootN2->branch << endl;
	for (auto i1 : tt2RootN2->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	
	// TT for NFA: N2 
	// str: {111}
	shared_ptr<TT<int, int>> tt3RootN2 = make_shared<TT<int, int>>(N2->q0, N2->d1, N2->d2);
	tt3RootN2->createTreeL(1);
	//cout << "Root:" << tt3RootN2->branch << endl;
	for (auto i1 : tt3RootN2->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N2 
	// str: {0100}
	shared_ptr<TT<int, int>> tt4RootN2 = make_shared<TT<int, int>>(N2->q0, N2->d1, N2->d2);
	tt4RootN2->createTreeL(0);
	//cout << "Root:" << tt4RootN2->branch << endl;
	for (auto i1 : tt4RootN2->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(0);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(0);
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					
					//cout << "---------------L4:" << i4->branch << endl;
				}
			}
		}
	}
	// TT for NFA: N2 
	// str: {0110}
	shared_ptr<TT<int, int>> tt5RootN2 = make_shared<TT<int, int>>(N2->q0, N2->d1, N2->d2);
	tt5RootN2->createTreeL(0);
	//cout << "Root:" << tt5RootN2->branch << endl;
	for (auto i1 : tt5RootN2->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(0);
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
				//	cout << "---------------L4:" << i4->branch << endl;
				}
			}
		}
	}
	// TT for NFA: N2 
	// str: {00100}
	shared_ptr<TT<int, int>> tt6RootN2 = make_shared<TT<int, int>>(N2->q0, N2->d1, N2->d2);
	tt6RootN2->createTreeL(0);
	//cout << "Root:" << tt6RootN2->branch << endl;
	for (auto i1 : tt6RootN2->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(0);
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					i4->createTreeL(0);
					//cout << "---------------L4:" << i4->branch << endl;
					for (auto i5 : i4->treeL) {
						//cout << "--------------------L5:" << i5->branch << endl;
					}
				}
			}
		}
	}
	// TT for NFA: N3
	// str: {00}
	shared_ptr<TT<int, int>> tt1RootN3 = make_shared<TT<int, int>>(N3->q0, N3->d1, N3->d2);
	tt1RootN3->createTreeL(0);
	//cout << "Root:" << tt1RootN3->branch << endl;
	for (auto i1 : tt1RootN3->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(0);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N3
	// str: {000}
	shared_ptr<TT<int, int>> tt2RootN3 = make_shared<TT<int, int>>(N3->q0, N3->d1, N3->d2);
	tt2RootN3->createTreeL(0);
	//cout << "Root:" << tt2RootN3->branch << endl;
	for (auto i1 : tt2RootN3->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(0);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(0);
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					//cout << "--------------L4:" << i4->branch << endl;
				}
			}
		}
	}
	// TT for NFA: N3
	// str: {0000}
	shared_ptr<TT<int, int>> tt3RootN3 = make_shared<TT<int, int>>(N3->q0, N3->d1, N3->d2);
	tt3RootN3->createTreeL(0);
	//cout << "Root:" << tt3RootN3->branch << endl;
	for (auto i1 : tt3RootN3->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(0);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(0);
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					i4->createTreeL(0);
					//cout << "--------------L4:" << i4->branch << endl;
					for (auto i5 : i4->treeL) {
						//cout << "-------------------L5:" << i5->branch << endl;
					}
				}
			}
		}
	}
	// TT for NFA: N3
	// str: {0}
	// rejects
	shared_ptr<TT<int, int>> tt4RootN3 = make_shared<TT<int, int>>(N3->q0, N3->d1, N3->d2);
	tt4RootN3->createTreeL(0);
	//cout << "Root:" << tt4RootN3->branch << endl;
	for (auto i1 : tt4RootN3->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "FAIL" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N3
	// str: {000000}
	shared_ptr<TT<int, int>> tt5RootN3 = make_shared<TT<int, int>>(N3->q0, N3->d1, N3->d2);
	tt5RootN3->createTreeL(0);
	//cout << "Root:" << tt5RootN3->branch << endl;
	for (auto i1 : tt5RootN3->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(0);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(0);
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					i4->createTreeL(0);
					//cout << "---------------L4:" << i4->branch << endl;
					for (auto i5 : i4->treeL) {
						i5->createTreeL(0);
						//cout << "-------------------------L5:" << i5->branch << endl;
						for (auto i6 : i5->treeL) {
							i6->createTreeL(0);
							//cout << "------------------------------L6:" << i6->branch << endl;
							for (auto i7 : i6->treeL) {
								//cout << "-----------------------------------L7:" << i7->branch << endl;
							}
						}
					}
				}
				
			}
		}
	}
	// TT for NFA: N3
	// str: {empty}
	// rejects
	shared_ptr<TT<int, int>> tt6RootN3 = make_shared<TT<int, int>>(N3->q0, N3->d1, N3->d2);
	tt6RootN3->createTreeL({});
	//cout << "Root:" << tt6RootN3->branch << endl;
	for (auto i1 : tt6RootN3->treeL) {
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N4
	// str: {0}
	shared_ptr<TT<int, int>> tt1RootN4 = make_shared<TT<int, int>>(N4->q0, N4->d1, N4->d2);
	tt1RootN4->createTreeL(0);
	//cout << "Root:" << tt1RootN4->branch << endl;
	for (auto i1 : tt1RootN4->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N4
	// str: {00}
	shared_ptr<TT<int, int>> tt2RootN4 = make_shared<TT<int, int>>(N4->q0, N4->d1, N4->d2);
	tt2RootN4->createTreeL(0);
	//cout << "Root:" << tt2RootN4->branch << endl;
	for (auto i1 : tt2RootN4->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(0);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(0);
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					//cout << "---------------L4:" << i4->branch << endl;
				}
			}
		}
	}
	// TT for NFA: N4
	// str: {100}
	shared_ptr<TT<int, int>> tt3RootN4 = make_shared<TT<int, int>>(N4->q0, N4->d1, N4->d2);
	tt3RootN4->createTreeL(1);
	//cout << "Root:" << tt3RootN4->branch << endl;
	for (auto i1 : tt3RootN4->treeL) {
		if (i1->branch == 2) {
			i1->push({ {i1->d.first(2,1)},{i1->d.second(2)} });
		}
		else {
			i1->createTreeL(0);
		}
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(0);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N4
	// str: {1010}
	shared_ptr<TT<int, int>> tt4RootN4 = make_shared<TT<int, int>>(N4->q0, N4->d1, N4->d2);
	tt4RootN4->createTreeL(1);
	//cout << "Root:" << tt4RootN4->branch << endl;
	for (auto i1 : tt4RootN4->treeL) {
		if (i1->branch == 2) {
			i1->push({ {i1->d.first(2,1)},{i1->d.second(2)} });
		}
		else {
			i1->createTreeL(0);
		}
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(0);
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					//cout << "---------------L4:" << i4->branch << endl;
				}
			}
		}
	}
	// TT for NFA: N4
	// str: {110}
	shared_ptr<TT<int, int>> tt5RootN4 = make_shared<TT<int, int>>(N4->q0, N4->d1, N4->d2);
	tt5RootN4->createTreeL(1);
	//cout << "Root:" << tt5RootN4->branch << endl;
	for (auto i1 : tt5RootN4->treeL) {
		if (i1->branch == 2) {
			i1->push({ {i1->d.first(2,1)},{i1->d.second(2)} });
		}
		else {
			i1->createTreeL(1);
		}
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(0);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
				
			}
		}
	}
	// TT for NFA: N4
	// str: {01}
	// rejects
	shared_ptr<TT<int, int>> tt6RootN4 = make_shared<TT<int, int>>(N4->q0, N4->d1, N4->d2);
	tt6RootN4->createTreeL(0);
	//cout << "Root:" << tt6RootN4->branch << endl;
	for (auto i1 : tt6RootN4->treeL) {
		if (i1->branch == 2) {
			i1->push({ {i1->d.first(2,0)},{i1->d.second(2)} });
		}
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			if (i2->branch == 0) {
				i2->push({ {i2->d.first(0,1)},{i2->d.second(0)} });
			}
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N13
	// str: {01}
	shared_ptr<TT<int, int>> tt1RootN13 = make_shared<TT<int, int>>(N13->q0, N13->d1, N13->d2);
	tt1RootN13->createTreeL(0);
	//cout << "Root:" << tt1RootN13->branch << endl;
	int count =0;
	for (auto i1 : tt1RootN13->treeL) {
		if (i1->branch == 1 && (count == 0)) {
			i1->push({ {i1->d.first(1,0)},{i1->d.second(1)} });
			count++;
		}
		else {
			i1->createTreeL(1);
		}
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N13
	// str: {1}
	shared_ptr<TT<int, int>> tt2RootN13 = make_shared<TT<int, int>>(N13->q0, N13->d1, N13->d2);
	tt2RootN13->createTreeL(1);
	//cout << "Root:" << tt2RootN13->branch << endl;
	count = 0;
	for (auto i1 : tt2RootN13->treeL) {
		if (i1->branch == 1 && (count == 0)) {
			i1->push({ {i1->d.first(1,1)},{i1->d.second(1)} });
			count++;
		}
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
		//	cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N13
	// str: {0}
	// rejects
	shared_ptr<TT<int, int>> tt3RootN13 = make_shared<TT<int, int>>(N13->q0, N13->d1, N13->d2);
	tt3RootN13->createTreeL(0);
	//cout << "Root:" << tt3RootN13->branch << endl;
	count = 0;
	for (auto i1 : tt3RootN13->treeL) {
		if (i1->branch == 1 && (count == 0)) {
			i1->push({ {i1->d.first(1,{})},{i1->d.second(1)} });
			count++;
		}
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N13
	// str: {00}
	// rejects
	shared_ptr<TT<int, int>> tt4RootN13 = make_shared<TT<int, int>>(N13->q0, N13->d1, N13->d2);
	tt4RootN13->createTreeL(0);
	//cout << "Root:" << tt4RootN13->branch << endl;
	count = 0;
	for (auto i1 : tt4RootN13->treeL) {
		if (i1->branch == 1 && (count == 0)) {
			i1->push({ {i1->d.first(1,{})},{i1->d.second(1)} });
			count++;
		}
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N13
	// str: {11}
	// rejects
	shared_ptr<TT<int, int>> tt5RootN13 = make_shared<TT<int, int>>(N13->q0, N13->d1, N13->d2);
	tt5RootN13->createTreeL(1);
	//cout << "Root:" << tt5RootN13->branch << endl;
	count = 0;
	for (auto i1 : tt5RootN13->treeL) {
		if (i1->branch == 1 && (count == 0)) {
			i1->push({ {i1->d.first(1,1)},{i1->d.second(1)} });
			count++;
		}
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N13
	// str: {10}
	// rejects
	shared_ptr<TT<int, int>> tt6RootN13 = make_shared<TT<int, int>>(N13->q0, N13->d1, N13->d2);
	tt6RootN13->createTreeL(1);
	//cout << "Root:" << tt6RootN13->branch << endl;
	count = 0;
	for (auto i1 : tt6RootN13->treeL) {
		if (i1->branch == 1 && (count == 0)) {
			i1->push({ {i1->d.first(1,1)},{i1->d.second(1)} });
			count++;
		}
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N6
	// str: {11}
	shared_ptr<TT<int, int>> tt1RootN6 = make_shared<TT<int, int>>(N6->q0, N6->d1, N6->d2);
	tt1RootN6->createTreeL(1);
	///cout << "Root:" << tt1RootN6->branch << endl;
	count = 0;
	for (auto i1 : tt1RootN6->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(1);
				//cout << "----------L2:" << i3->branch << endl;
			}
		}

	}
	// TT for NFA: N6
	// str: {00}
	shared_ptr<TT<int, int>> tt2RootN6 = make_shared<TT<int, int>>(N6->q0, N6->d1, N6->d2);
	tt2RootN6->createTreeL(0);
	//cout << "Root:" << tt2RootN6->branch << endl;
	count = 0;
	for (auto i1 : tt2RootN6->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(0);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}

	}
	// TT for NFA: N6
	// str: {011}
	shared_ptr<TT<int, int>> tt3RootN6 = make_shared<TT<int, int>>(N6->q0, N6->d1, N6->d2);
	tt3RootN6->createTreeL(0);
	//cout << "Root:" << tt3RootN6->branch << endl;
	count = 0;
	for (auto i1 : tt3RootN6->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(1);
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					//cout << "---------------L4:" << i4->branch << endl;
				}
			}
		}

	}
	// TT for NFA: N6
	// str: {100}
	shared_ptr<TT<int, int>> tt4RootN6 = make_shared<TT<int, int>>(N6->q0, N6->d1, N6->d2);
	tt4RootN6->createTreeL(1);
	//cout << "Root:" << tt4RootN6->branch << endl;
	count = 0;
	for (auto i1 : tt4RootN6->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(0);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(0);
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					//cout << "---------------L4:" << i4->branch << endl;
				}
			}
		}

	}
	// TT for NFA: N6
	// str: {0100}
	shared_ptr<TT<int, int>> tt5RootN6 = make_shared<TT<int, int>>(N6->q0, N6->d1, N6->d2);
	tt5RootN6->createTreeL(0);
	//cout << "Root:" << tt5RootN6->branch << endl;
	count = 0;
	for (auto i1 : tt5RootN6->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(0);
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					i4->createTreeL(0);
					//cout << "---------------L4:" << i4->branch << endl;
					for (auto i5 : i4->treeL) {
						//cout << "--------------------L5:" << i5->branch << endl;
					}
				}
			}
		}

	}
	// TT for NFA: N6
	// str: {01}
	// rejects
	shared_ptr<TT<int, int>> tt6RootN6 = make_shared<TT<int, int>>(N6->q0, N6->d1, N6->d2);
	tt6RootN6->createTreeL(0);
	//cout << "Root:" << tt6RootN6->branch << endl;
	count = 0;
	for (auto i1 : tt6RootN6->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N7
	// str: {00}
	shared_ptr<TT<int, int>> tt1RootN7 = make_shared<TT<int, int>>(N7->q0, N7->d1, N7->d2);
	tt1RootN7->createTreeL(0);
	//cout << "Root:" << tt1RootN7->branch << endl;
	count = 0;
	for (auto i1 : tt1RootN7->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N7
	// str: {01}
	shared_ptr<TT<int, int>> tt2RootN7 = make_shared<TT<int, int>>(N7->q0, N7->d1, N7->d2);
	tt2RootN7->createTreeL(0);
	//cout << "Root:" << tt2RootN7->branch << endl;
	count = 0;
	for (auto i1 : tt2RootN7->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N7
	// str: {10}
	shared_ptr<TT<int, int>> tt3RootN7 = make_shared<TT<int, int>>(N7->q0, N7->d1, N7->d2);
	tt3RootN7->createTreeL(1);
	//cout << "Root:" << tt3RootN7->branch << endl;
	count = 0;
	for (auto i1 : tt3RootN7->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N7
	// str: {11}
	shared_ptr<TT<int, int>> tt4RootN7 = make_shared<TT<int, int>>(N7->q0, N7->d1, N7->d2);
	tt4RootN7->createTreeL(1);
	//cout << "Root:" << tt4RootN7->branch << endl;
	count = 0;
	for (auto i1 : tt4RootN7->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N7
	// str: {1}
	// rejects
	shared_ptr<TT<int, int>> tt5RootN7 = make_shared<TT<int, int>>(N7->q0, N7->d1, N7->d2);
	tt5RootN7->createTreeL(1);
	//cout << "Root:" << tt5RootN7->branch << endl;
	count = 0;
	for (auto i1 : tt5RootN7->treeL) {
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N7
	// str: {111}
	// reject
	shared_ptr<TT<int, int>> tt6RootN7 = make_shared<TT<int, int>>(N7->q0, N7->d1, N7->d2);
	tt6RootN7->createTreeL(1);
	//cout << "Root:" << tt6RootN7->branch << endl;
	count = 0;
	for (auto i1 : tt6RootN7->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N8
	// str: {0}
	shared_ptr<TT<int, int>> tt1RootN8 = make_shared<TT<int, int>>(N8->q0, N8->d1, N8->d2);
	tt1RootN8->createTreeL(0);
	//cout << "Root:" << tt1RootN8->branch << endl;
	count = 0;
	for (auto i1 : tt1RootN8->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N8
	// str: {11}
	shared_ptr<TT<int, int>> tt2RootN8 = make_shared<TT<int, int>>(N8->q0, N8->d1, N8->d2);
	tt2RootN8->createTreeL(1);
	//cout << "Root:" << tt2RootN8->branch << endl;
	count = 0;
	for (auto i1 : tt2RootN8->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				///cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N8
	// str: {000}
	shared_ptr<TT<int, int>> tt3RootN8 = make_shared<TT<int, int>>(N8->q0, N8->d1, N8->d2);
	tt3RootN8->createTreeL(0);
	///cout << "Root:" << tt3RootN8->branch << endl;
	count = 0;
	for (auto i1 : tt3RootN8->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(0);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(0);
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					//cout << "---------------L4:" << i4->branch << endl;
				}
			}
		}
	}
	// TT for NFA: N8
	// str: {1111}
	shared_ptr<TT<int, int>> tt4RootN8 = make_shared<TT<int, int>>(N8->q0, N8->d1, N8->d2);
	tt4RootN8->createTreeL(1);
	//cout << "Root:" << tt4RootN8->branch << endl;
	count = 0;
	for (auto i1 : tt4RootN8->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(1);
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					i4->createTreeL(1);
					//cout << "---------------L4:" << i4->branch << endl;
					for (auto i5 : i4->treeL) {
						//cout << "--------------------L5:" << i5->branch << endl;
					}
				}
			}
		}
	}
	// TT for NFA: N8
	// str: {00}
	shared_ptr<TT<int, int>> tt5RootN8 = make_shared<TT<int, int>>(N8->q0, N8->d1, N8->d2);
	tt5RootN8->createTreeL(0);
	//cout << "Root:" << tt5RootN8->branch << endl;
	count = 0;
	for (auto i1 : tt5RootN8->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(0);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N8
	// str: {1}
	shared_ptr<TT<int, int>> tt6RootN8 = make_shared<TT<int, int>>(N8->q0, N8->d1, N8->d2);
	tt6RootN8->createTreeL(1);
	//cout << "Root:" << tt6RootN8->branch << endl;
	count = 0;
	for (auto i1 : tt6RootN8->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N9
	// str: {11}
	shared_ptr<TT<int, int>> tt1RootN9 = make_shared<TT<int, int>>(N9->q0, N9->d1, N9->d2);
	tt1RootN9->createTreeL(1);
	//cout << "Root:" << tt1RootN9->branch << endl;
	count = 0;
	for (auto i1 : tt1RootN9->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N9
	// str: {111}
	shared_ptr<TT<int, int>> tt2RootN9 = make_shared<TT<int, int>>(N9->q0, N9->d1, N9->d2);
	tt2RootN9->createTreeL(1);
	//cout << "Root:" << tt2RootN9->branch << endl;
	count = 0;
	for (auto i1 : tt2RootN9->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N9
	// str: {1011}
	shared_ptr<TT<int, int>> tt3RootN9 = make_shared<TT<int, int>>(N9->q0, N9->d1, N9->d2);
	tt3RootN9->createTreeL(1);
	//cout << "Root:" << tt3RootN9->branch << endl;
	count = 0;
	for (auto i1 : tt3RootN9->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(1);
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					//cout << "---------------L4:" << i4->branch << endl;
				}
			}
		}
	}
	// TT for NFA: N9
	// str: {101}
	shared_ptr<TT<int, int>> tt4RootN9 = make_shared<TT<int, int>>(N9->q0, N9->d1, N9->d2);
	tt4RootN9->createTreeL(1);
	//cout << "Root:" << tt4RootN9->branch << endl;
	count = 0;
	for (auto i1 : tt4RootN9->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N9
	// str: {10101}
	shared_ptr<TT<int, int>> tt5RootN9 = make_shared<TT<int, int>>(N9->q0, N9->d1, N9->d2);
	tt5RootN9->createTreeL(1);
	//cout << "Root:" << tt5RootN9->branch << endl;
	count = 0;
	for (auto i1 : tt5RootN9->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(0);
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					i4->createTreeL(1);
					//cout << "---------------L4:" << i4->branch << endl;
					for (auto i5 : i4->treeL) {
						//cout << "--------------------L5:" << i5->branch << endl;
					}
				}
			}
		}
	}
	// TT for NFA: N9
	// str: {10}
	// rejects
	shared_ptr<TT<int, int>> tt6RootN9 = make_shared<TT<int, int>>(N9->q0, N9->d1, N9->d2);
	tt6RootN9->createTreeL(1);
	//cout << "Root:" << tt6RootN9->branch << endl;
	count = 0;
	for (auto i1 : tt6RootN9->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N10
	// str: {empty}
	shared_ptr<TT<int, int>> tt1RootN10 = make_shared<TT<int, int>>(N10->q0, N10->d1, N10->d2);
	tt1RootN10->createTreeL({});
	//cout << "Root:" << tt1RootN10->branch << endl;
	count = 0;
	for (auto i1 : tt1RootN10->treeL) {
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N10
	// str: {0}
	shared_ptr<TT<int, int>> tt2RootN10 = make_shared<TT<int, int>>(N10->q0, N10->d1, N10->d2);
	tt2RootN10->createTreeL(0);
	//cout << "Root:" << tt2RootN10->branch << endl;
	count = 0;
	for (auto i1 : tt2RootN10->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N10
	// str: {1}
	shared_ptr<TT<int, int>> tt3RootN10 = make_shared<TT<int, int>>(N10->q0, N10->d1, N10->d2);
	tt3RootN10->createTreeL(1);
	//cout << "Root:" << tt3RootN10->branch << endl;
	count = 0;
	for (auto i1 : tt3RootN10->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N10
	// str: {10}
	shared_ptr<TT<int, int>> tt4RootN10 = make_shared<TT<int, int>>(N10->q0, N10->d1, N10->d2);
	tt4RootN10->createTreeL(1);
	//cout << "Root:" << tt4RootN10->branch << endl;
	count = 0;
	for (auto i1 : tt4RootN10->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(0);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N10
	// str: {01}
	shared_ptr<TT<int, int>> tt5RootN10 = make_shared<TT<int, int>>(N10->q0, N10->d1, N10->d2);
	tt5RootN10->createTreeL(0);
	//cout << "Root:" << tt5RootN10->branch << endl;
	count = 0;
	for (auto i1 : tt5RootN10->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(1);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N10
	// str: {101}
	shared_ptr<TT<int, int>> tt6RootN10 = make_shared<TT<int, int>>(N10->q0, N10->d1, N10->d2);
	tt6RootN10->createTreeL(1);
	//cout << "Root:" << tt6RootN10->branch << endl;
	count = 0;
	for (auto i1 : tt6RootN10->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(0);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				i3->createTreeL(1);
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					//cout << "---------------L4:" << i4->branch << endl;
				}
			}
		}
	}
	// TT for NFA: N14
	// str: {111}
	shared_ptr<TT<int, int>> tt1RootN14 = make_shared<TT<int, int>>(N14->q0, N14->d1, N14->d2);
	tt1RootN14->createTreeL(1);
	//cout << "Root:" << tt1RootN14->branch << endl;
	count = 0;
	for (auto i1 : tt1RootN14->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			if (i2->branch == 2) {
				i2->push({ {i2->d.first(2,1)}, {i2->d.second(2)} });
			}
			else {
				i2->createTreeL(1);
			}
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				if (i3->branch == 2) {
					i3->push({ {i3->d.first(2,1)}, {i3->d.second(2)} });
				}
				else {
					i3->createTreeL({});
				}
				///cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					//cout << "---------------L4:" << i4->branch << endl;
				}
			}
		}
	}
	// TT for NFA: N14
	// str: {1}
	shared_ptr<TT<int, int>> tt2RootN14 = make_shared<TT<int, int>>(N14->q0, N14->d1, N14->d2);
	tt2RootN14->createTreeL(1);
	//cout << "Root:" << tt2RootN14->branch << endl;
	count = 0;
	for (auto i1 : tt2RootN14->treeL) {
		i1->createTreeL({});
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N14
	// str: {10}
	shared_ptr<TT<int, int>> tt3RootN14 = make_shared<TT<int, int>>(N14->q0, N14->d1, N14->d2);
	tt3RootN14->createTreeL(1);
	//cout << "Root:" << tt3RootN14->branch << endl;
	count = 0;
	for (auto i1 : tt3RootN14->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL({});
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N14
	// str: {110}
	shared_ptr<TT<int, int>> tt4RootN14 = make_shared<TT<int, int>>(N14->q0, N14->d1, N14->d2);
	tt4RootN14->createTreeL(1);
	//cout << "Root:" << tt4RootN14->branch << endl;
	count = 0;
	for (auto i1 : tt4RootN14->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			if (i2->branch == 2) {
				i2->push({ {i2->d.first(2,1)}, {i2->d.second(2)} });
			}
			else {
				i2->createTreeL(0);
			}
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				if (i3->branch == 2) {
					i3->push({ {i3->d.first(2,0)}, {i3->d.second(2)} });
				}
				//cout << "----------L3:" << i3->branch << endl;
				for (auto i4 : i3->treeL) {
					//cout << "---------------L4:" << i4->branch << endl;
				}
			}
		}
	}
	// TT for NFA: N14
	// str: {11}
	shared_ptr<TT<int, int>> tt5RootN14 = make_shared<TT<int, int>>(N14->q0, N14->d1, N14->d2);
	tt5RootN14->createTreeL(1);
	//cout << "Root:" << tt5RootN14->branch << endl;
	count = 0;
	for (auto i1 : tt5RootN14->treeL) {
		i1->createTreeL(1);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			if (i2->branch == 2) {
				i2->push({ {i2->d.first(2,1)}, {i2->d.second(2)} });
			}
			else {
				i2->createTreeL({});
			}
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N14
	// str: {101}
	// rejects
	shared_ptr<TT<int, int>> tt6RootN14 = make_shared<TT<int, int>>(N14->q0, N14->d1, N14->d2);
	tt6RootN14->createTreeL(1);
	//cout << "Root:" << tt6RootN14->branch << endl;
	count = 0;
	for (auto i1 : tt6RootN14->treeL) {
		i1->createTreeL(0);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			if (i2->branch == 2) {
				i2->push({ {i2->d.first(2,0)}, {i2->d.second(2)} });
			}
			else {
				i2->createTreeL(1);
			}
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
	
			}
		}
	}
	// TT for NFA: N12
	// str: {68}
	shared_ptr<TT<int, int>> tt1RootN12 = make_shared<TT<int, int>>(N12->q0, N12->d1, N12->d2);
	tt1RootN12->createTreeL({});
	//cout << "Root:" << tt1RootN12->branch << endl;
	count = 0;
	for (auto i1 : tt1RootN12->treeL) {
		i1->createTreeL(6);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(8);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N12
	// str: {2}
	shared_ptr<TT<int, int>> tt2RootN12 = make_shared<TT<int, int>>(N12->q0, N12->d1, N12->d2);
	tt2RootN12->createTreeL({});
	//cout << "Root:" << tt2RootN12->branch << endl;
	count = 0;
	for (auto i1 : tt2RootN12->treeL) {
		i1->createTreeL(2);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N12
	// str: {6}
	shared_ptr<TT<int, int>> tt3RootN12 = make_shared<TT<int, int>>(N12->q0, N12->d1, N12->d2);
	tt3RootN12->createTreeL({});
	//cout << "Root:" << tt3RootN12->branch << endl;
	count = 0;
	for (auto i1 : tt3RootN12->treeL) {
		i1->createTreeL(6);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
		//	cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N12
	// str: {empty}
	shared_ptr<TT<int, int>> tt4RootN12 = make_shared<TT<int, int>>(N12->q0, N12->d1, N12->d2);
	tt4RootN12->createTreeL({});
	//cout << "Root:" << tt4RootN12->branch << endl;
	//count = 0;
	for (auto i1 : tt4RootN12->treeL) {
		i1->createTreeL({});
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			//cout << "-----L2:" << i2->branch << endl;
		}
	}
	// TT for NFA: N12
	// str: {empty}
	shared_ptr<TT<int, int>> tt5RootN12 = make_shared<TT<int, int>>(N12->q0, N12->d1, N12->d2);
	tt5RootN12->createTreeL({});
	//cout << "Root:" << tt5RootN12->branch << endl;
	count = 0;
	for (auto i1 : tt4RootN12->treeL) {
		i1->createTreeL(6);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(3);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	// TT for NFA: N12
	// str: {32}
	// rejects
	shared_ptr<TT<int, int>> tt6RootN12 = make_shared<TT<int, int>>(N12->q0, N12->d1, N12->d2);
	tt6RootN12->createTreeL({});
	//cout << "Root:" << tt6RootN12->branch << endl;
	count = 0;
	for (auto i1 : tt6RootN12->treeL) {
		i1->createTreeL(3);
		//cout << "L1:" << i1->branch << endl;
		for (auto i2 : i1->treeL) {
			i2->createTreeL(2);
			//cout << "-----L2:" << i2->branch << endl;
			for (auto i3 : i2->treeL) {
				//cout << "----------L3:" << i3->branch << endl;
			}
		}
	}
	
	/*
		Task 31 - For each example NFA, write a dozen tests of their behavior.
	*/
	// N1 accepting string
		//shared_ptr<TT<int, int>> test = forking(N1, {1,0,1,1});
		//shared_ptr<TT<int, int>> test = forking(N1, {1,1,1});
		//shared_ptr<TT<int, int>> test = forking(N1, {0,0,0,1,0,1});
		//shared_ptr<TT<int, int>> test = forking(N1, {0,1,0,1,1,0});
		//shared_ptr<TT<int, int>> test = forking(N1, {1,0,1,0,1,0});
		//shared_ptr<TT<int, int>> test = forking(N1, {1,1,0});
	// N1 rejecting strings
		//shared_ptr<TT<int, int>> test = forking(N1, {1,0,1});
		//shared_ptr<TT<int, int>> test = forking(N1, {1,1});
		//shared_ptr<TT<int, int>> test = forking(N1, {0,0,0});
		//shared_ptr<TT<int, int>> test = forking(N1, {0,1,0});
		//shared_ptr<TT<int, int>> test = forking(N1, {1});
		//shared_ptr<TT<int, int>> test = forking(N1, {0});

	//N2 accepting string
		//shared_ptr<TT<int, int>> test = forking(N2, {1,0,0});
		//shared_ptr<TT<int, int>> test = forking(N2, {1,0,1});
		//shared_ptr<TT<int, int>> test = forking(N2, {1,1,1});
		//shared_ptr<TT<int, int>> test = forking(N2, {0,1,0,0});
		//shared_ptr<TT<int, int>> test = forking(N2, {0,1,1,0});
		//shared_ptr<TT<int, int>> test = forking(N2, {0,0,1,0,0});
	// N2 rejecting strings
		//shared_ptr<TT<int, int>> test = forking(N2, {1,0,1});
		//shared_ptr<TT<int, int>> test = forking(N2, {1,1});
		//shared_ptr<TT<int, int>> test = forking(N2, {0,0,0});
		//shared_ptr<TT<int, int>> test = forking(N2, {0,1,0});
		//shared_ptr<TT<int, int>> test = forking(N2, {1});
		//shared_ptr<TT<int, int>> test = forking(N2, {0});
		
	// N3 accepting string
		//shared_ptr<TT<int, int>> test = forking(N3, {0,0});
		//shared_ptr<TT<int, int>> test = forking(N3, {0,0,0});
		//shared_ptr<TT<int, int>> test = forking(N3, {0,0,0,0});
		//shared_ptr<TT<int, int>> test = forking(N3, {0});
		//shared_ptr<TT<int, int>> test = forking(N3, {0,0,0,0,0,0});
		//shared_ptr<TT<int, int>> test = forking(N3, {});
	// N3 rejecting strings
		//shared_ptr<TT<int, int>> test = forking(N3, {1,0});
		//shared_ptr<TT<int, int>> test = forking(N3, {1,1});
		//shared_ptr<TT<int, int>> test = forking(N3, {0,0,0});
		//shared_ptr<TT<int, int>> test = forking(N3, {0,1,0});
		//shared_ptr<TT<int, int>> test = forking(N3, {1,1,1});
		//shared_ptr<TT<int, int>> test = forking(N3, {1});

	// N4 accepting string
		//shared_ptr<TT<int, int>> test = forking(N4, {1,0,1,0});
		//shared_ptr<TT<int, int>> test = forking(N4, {1,1,0});
		//shared_ptr<TT<int, int>> test = forking(N4, {1,1,0,0});
		//shared_ptr<TT<int, int>> test = forking(N4, {0});
		//shared_ptr<TT<int, int>> test = forking(N4, {0,0});
		//shared_ptr<TT<int, int>> test = forking(N4, {1,0,0});
	// N4 rejecting strings
		//shared_ptr<TT<int, int>> test = forking(N4, {1});
		//shared_ptr<TT<int, int>> test = forking(N4, {1,1});
		//shared_ptr<TT<int, int>> test = forking(N4, {1,0});
		//shared_ptr<TT<int, int>> test = forking(N4, {1,0,1});
		//shared_ptr<TT<int, int>> test = forking(N4, {1,1,1});
		//shared_ptr<TT<int, int>> test = forking(N4, {0,1});
	
	// N13 accepting string
		//shared_ptr<TT<int, int>> test = forking(N13, {0,1});
		//shared_ptr<TT<int, int>> test = forking(N13, {1});
		//shared_ptr<TT<int, int>> test = forking(N13, {1,1});
		//shared_ptr<TT<int, int>> test = forking(N13, {1,0});
		
	// N13 rejecting strings
		//shared_ptr<TT<int, int>> test = forking(N13, {0});
		//shared_ptr<TT<int, int>> test = forking(N13, {0,0});
		//shared_ptr<TT<int, int>> test = forking(N13, {1});
		//shared_ptr<TT<int, int>> test = forking(N13, {1,0,1});
		//shared_ptr<TT<int, int>> test = forking(N13, {1,1,1});
		//shared_ptr<TT<int, int>> test = forking(N13, {0,1,1,1});

	// N6 accepting string
		//shared_ptr<TT<int, int>> test = forking(N6, {1,1});
		//shared_ptr<TT<int, int>> test = forking(N6, {0,0});
		//shared_ptr<TT<int, int>> test = forking(N6, {0,1,1});
		//shared_ptr<TT<int, int>> test = forking(N6, {1,0,0});
		//shared_ptr<TT<int, int>> test = forking(N6, {0,1,0,0});
		//shared_ptr<TT<int, int>> test = forking(N6, {0,0,0});
	// N6 rejecting strings
		//shared_ptr<TT<int, int>> test = forking(N6, {0});
		//shared_ptr<TT<int, int>> test = forking(N6, {0,1});
		//shared_ptr<TT<int, int>> test = forking(N6, {1});
		//shared_ptr<TT<int, int>> test = forking(N6, {1,0});
		//shared_ptr<TT<int, int>> test = forking(N6, {1,1,0});
		//shared_ptr<TT<int, int>> test = forking(N6, {0,1,0,1});

	// N7 accepting string
		//shared_ptr<TT<int, int>> test = forking(N7, {0,0});
		//shared_ptr<TT<int, int>> test = forking(N7, {0,1});
		//shared_ptr<TT<int, int>> test = forking(N7, {1,0});
		//shared_ptr<TT<int, int>> test = forking(N7, {1,1});
		// only accepts four strings 
	// N7 rejecting strings
		//shared_ptr<TT<int, int>> test = forking(N7, {0});
		//shared_ptr<TT<int, int>> test = forking(N7, {1});
		//shared_ptr<TT<int, int>> test = forking(N7, {1,1,1});
		//shared_ptr<TT<int, int>> test = forking(N7, {0,0,0});
		//shared_ptr<TT<int, int>> test = forking(N7, {1,1,0});
		//shared_ptr<TT<int, int>> test = forking(N7, {0,1,0,1});
	
	// N8 accepting string
		//shared_ptr<TT<int, int>> test = forking(N8, {0});
		//shared_ptr<TT<int, int>> test = forking(N8, {1,1});
		//shared_ptr<TT<int, int>> test = forking(N8, {0,0,0});
		//shared_ptr<TT<int, int>> test = forking(N8, {1,1,1,1});
		//shared_ptr<TT<int, int>> test = forking(N8, {0,0,0,0,0});
		// //shared_ptr<TT<int, int>> test = forking(N8, {1,1,1,1,1,1});
	// N8 rejecting strings
		//shared_ptr<TT<int, int>> test = forking(N8, {1});
		//shared_ptr<TT<int, int>> test = forking(N8, {0,0});
		//shared_ptr<TT<int, int>> test = forking(N8, {1,1,1});
		//shared_ptr<TT<int, int>> test = forking(N8, {0,0,0,0});
		//shared_ptr<TT<int, int>> test = forking(N8, {1,1,1,1,1});
		//shared_ptr<TT<int, int>> test = forking(N8, {0,0,0,0,0,0});

	// N9 accepting string
		//shared_ptr<TT<int, int>> test = forking(N9, {1,1});
		//shared_ptr<TT<int, int>> test = forking(N9, {1,1,1});
		//shared_ptr<TT<int, int>> test = forking(N9, {1,0,1,1});
		//shared_ptr<TT<int, int>> test = forking(N9, {1,0,1});
		//shared_ptr<TT<int, int>> test = forking(N9, {1,0,1,0,1});
		// //shared_ptr<TT<int, int>> test = forking(N9, {1,1,1,1,1});
	// N9 rejecting strings
		//shared_ptr<TT<int, int>> test = forking(N9, {0});
		//shared_ptr<TT<int, int>> test = forking(N9, {0,0});
		//shared_ptr<TT<int, int>> test = forking(N9, {0,1,1});
		//shared_ptr<TT<int, int>> test = forking(N9, {0,0,0,0});
		//shared_ptr<TT<int, int>> test = forking(N9, {0,1,1,1,1});
		//shared_ptr<TT<int, int>> test = forking(N9, {0,0,0,0,0,0});

	// N10 accepting string
		//shared_ptr<TT<int, int>> test = forking(N10, {});
		//shared_ptr<TT<int, int>> test = forking(N10, {1});
		//shared_ptr<TT<int, int>> test = forking(N10, {0});
		//shared_ptr<TT<int, int>> test = forking(N10, {1,0});
		//shared_ptr<TT<int, int>> test = forking(N10, {0,1});
		// //shared_ptr<TT<int, int>> test = forking(N10, {1,0,1});
	// N10 rejecting strings
		//shared_ptr<TT<int, int>> test = forking(N10, {1,1});
		//shared_ptr<TT<int, int>> test = forking(N10, {0,0});
		//shared_ptr<TT<int, int>> test = forking(N10, {0,1,1});
		//shared_ptr<TT<int, int>> test = forking(N10, {0,0,0,0});
		//shared_ptr<TT<int, int>> test = forking(N10, {0,1,1,1,1});
		//shared_ptr<TT<int, int>> test = forking(N10, {0,0,0,0,0,0});

	// N14 accepting string
		//shared_ptr<TT<int, int>> test = forking(N14, {1});
		//shared_ptr<TT<int, int>> test = forking(N14, {1,0});
		//shared_ptr<TT<int, int>> test = forking(N14, {1,1,0});
		//shared_ptr<TT<int, int>> test = forking(N14, {1,1});
		//shared_ptr<TT<int, int>> test = forking(N14, {1,1,1});
		// //shared_ptr<TT<int, int>> test = forking(N14, {1,0,0});
	// N114 rejecting strings
		//shared_ptr<TT<int, int>> test = forking(N14, {1,0,1});
		//shared_ptr<TT<int, int>> test = forking(N14, {1});
		//shared_ptr<TT<int, int>> test = forking(N14, {0});
		//shared_ptr<TT<int, int>> test = forking(N14, {0,0,0,0});
		//shared_ptr<TT<int, int>> test = forking(N14, {1,1,0,1});
		//shared_ptr<TT<int, int>> test = forking(N14, {0,0,0,0,0,0});

	// N12 accepting string
		//shared_ptr<TT<int, int>> test = forking(N12, {2});
		//shared_ptr<TT<int, int>> test = forking(N12, {6});
		//shared_ptr<TT<int, int>> test = forking(N12, {6,8});
		//shared_ptr<TT<int, int>> test = forking(N12, {6,3});
		//shared_ptr<TT<int, int>> test = forking(N12, {});
		//shared_ptr<TT<int, int>> test = forking(N12, {2,2});
	// N112 rejecting strings
		//shared_ptr<TT<int, int>> test = forking(N12, {3,2});
		//shared_ptr<TT<int, int>> test = forking(N12, {1});
		//shared_ptr<TT<int, int>> test = forking(N12, {2,2,3});
		//shared_ptr<TT<int, int>> test = forking(N12, {0});
		//shared_ptr<TT<int, int>> test = forking(N12, {2,4,9});
		//shared_ptr<TT<int, int>> test = forking(N12, {3,9,2});

	/*
		testing task 32 accepts function
	*/
	testNFAAccepts(N1, { 1,0,1,1 }, true, "N1");
	testNFAAccepts(N1, { 1,1,1 }, true,"N1");
	testNFAAccepts(N1, { 0,0,0,1,0,1}, true, "N1");
	testNFAAccepts(N1, { 0,1,0,1,1,0}, true, "N1");
	testNFAAccepts(N1, { 1,0,1,0,1,0}, true, "N1");
	testNFAAccepts(N1, { 1,1,0}, true, "N1");
	testNFAAccepts(N1, { 1 }, false, "N1");

	testNFAAccepts(N4, { 0 }, true, "N4");
	testNFAAccepts(N4, { 0,0 }, true, "N4");
	testNFAAccepts(N4, { 1,0,0 }, true, "N4");
	testNFAAccepts(N4, { 1,0,1,0 }, true, "N4");
	testNFAAccepts(N4, { 1,1,0 }, true, "N4");
	testNFAAccepts(N4, { 0,1 }, false, "N4");
	testNFAAccepts(N4, { 0,1,1 }, false, "N4");
	testNFAAccepts(N4, { 1,1 }, false, "N4");
	
	/*
		Testing Union
	*/
	auto* N4_U_N6 = unionNFA(N4, N6);
	list<pair<int,int>> N4_U_N6_Q = { pair<int,int>(-1,-1), pair<int,int>(0, 0), pair<int,int>(0, 1), pair<int,int>(0, 2),
	pair<int,int>(1, 0), pair<int,int>(1, 1), pair<int,int>(1, 2), pair<int,int>(1, 3), pair<int,int>(1, 4), 
	pair<int,int>(1, 5), pair<int,int>(1, 6) };
	for (auto i : N4_U_N6_Q) {
		if (!N4_U_N6->Q(i)) {
			cout << "FAIL Q" << endl;
		}
	}
	list<pair<int, int>> N4_U_N6_F = { pair<int,int>(0, 0), pair<int,int>(1, 3), pair<int,int>(1, 6) };
	for (auto i : N4_U_N6_F) {
		if (!N4_U_N6->F(i)) {
			cout << "FAIL Q" << endl;
		}
	}
	if (N4_U_N6->q0 != pair<int, int>(-1,-1)) {
		cout << "FAIL q0" << endl;
	}
	testNFA(N4_U_N6, "N4_U_N6", false, false,
		{ {0}, {0,0}, {1,1}, {1,1,0}, {1,0,0,0}, {1,0,0,1,1},	//tests that should accept
		{1}, {1,1,0,1}, {1,0}, {1,0,0,0,1}, {0,0,1}, {0,1} }	// tests that should reject
	);
	/*
		TASK #35 - Testing concat
	*/
	// N4 accepts: epsilon, {0}, {1010}, {100}; doesnt accept: {1}, {11}, {10110}
	// L(N6) = strings of a finite length that end in either '11' or '00'
	auto* N4_concat_N6 = concat(N4, N6);
	testNFA(N4_concat_N6, "N4_concat_N6", false, false,
		{ {0,0,0}, {1,0,1,1}, {0,0}, {1,1}, {0,1,1}, {1,0,0,1,1},
		{1}, {0}, {1,0}, {1,0,0,0,1}, {0,0,1}, {1,1,0} }
		);
	// N1 accepts {1,1}, {1,0,1}, {0,1,1}
	// L(N3) = strings that are multiples of 2 or 3
	auto* N1_concat_N3 = concat(N1, N3);
	testNFA(N1_concat_N3, "N1_concat_N3", false, false,
		{ {1,1}, {1,1,0,0}, {1,1,0,0,0}, {1,0,1,0,0,0}, {1,0,1}, {1,0,1,0,0,0,0,0,0},
		{}, {0}, {1,0}, {1,0,0,0,1}, {1,0,0}, {0,0,0} }
	);
	// L(N2) = strings over {0,1} with a 1 third from the end
	// N13 only accepts {1} and {0,1}
	auto* N2_concat_N13 = concat(N2, N13);
	testNFA(N2_concat_N13, "N2_concat_N13", false, false,
		{ {1,1,1,1}, {1,1,1,0,1}, {1,0,1,1,1,1,1}, {1,0,0,1}, {1,0,0,0,1}, {1,1,1,1,1,1,1},
		{}, {0}, {1}, {1,1,1}, {1,0,0}, {0,0,0} }
	);
	// L(N7) = only the strings {00},{01},{10},{11}
	// L(N8) = all strings that if they are even, will be all 1's, and if they are odd, they are all 0's
	auto* N7_concat_N8 = concat(N7, N8);
	testNFA(N7_concat_N8, "N7_concat_N8", false, false,
		{ {0,0,0}, {1,1,1,1}, {0,0,1,1}, {1,1,0}, {0,1,1,1}, {1,0,0,0,0},
		{}, {0}, {1}, {1,1,1}, {1,0,0,0}, {0,0,1} }
	);
	// L(N8) = all strings that if they are even, will be all 1's, and if they are odd, they are all 0's
	// L(N9) = all strings that start and end with the char 1, with any 
	// amount of char's in between.
	auto* N8_concat_N9 = concat(N8, N9);
	testNFA(N8_concat_N9, "N8_concat_N9", false, false,
		{ {1,0,1}, {1,1,1,0,1}, {0,0,0,1,1,0,1,1}, {0,1,1,1}, {0,0,0,1,0,1}, {1,1,1},
		{}, {0}, {1}, {1,1,0}, {1,0,0,0}, {0,0,1} }
	);	
	// L(N10) = any string that alternates between 1 and 0, starting with either 1 or 0.
	// N14 accepts {1}, {1,0}, {1,1}, {1,1,0}
	auto* N10_concat_N14 = concat(N10, N14);
	testNFA(N10_concat_N14, "N10_concat_N14", false, false,
		{ {1}, {1,0}, {1,0,1,0,1}, {1,0,1,1,1}, {0,1,0,1,1,0}, {1,1,1},
		{}, {0}, {0,0}, {0,0,0}, {0,0,0,0}, {0,0,0,1,0,1}}
	);
	// N4 accepts: epsilon, {0}, {1010}, {100}; doesnt accept: {1}, {11}, {10110}
	// L(N6) = strings of a finite length that end in either '11' or '00'
	auto* N6_concat_N4 = concat(N6, N4);
	testNFA(N6_concat_N4, "N6_concat_N4", false, false,
		{ {0,0,0}, {1,0,1,1}, {0,0}, {1,1}, {0,1,1}, {1,0,0,1,1},
		{1}, {0}, {1,0}, {1,0,0,0,1}, {0,0,1}, {} }
	);
	// N1 accepts {1,1}, {1,0,1}, {0,1,1}
	// L(N3) = strings that are multiples of 2 or 3
	auto* N3_concat_N1 = concat(N3, N1);
	testNFA(N3_concat_N1, "N3_concat_N1", false, false,
		{ {1,1}, {1,1,0,0}, {1,1,0,0,0}, {1,0,1,0,0,0}, {1,0,1}, {1,0,1,0,0,0,0,0,0},
		{}, {0}, {1,0}, {1,0,0,0,1}, {1,0,0}, {0,0,0} }
	);
	// L(N2) = strings over {0,1} with a 1 third from the end
	// N13 only accepts {1} and {0,1}
	auto* N13_concat_N2 = concat(N13, N2);
	testNFA(N13_concat_N2, "N13_concat_N2", false, false,
		{ {1,1,1,1}, {1,1,1,0,1}, {1,0,1,1,1,1,1}, {1,1,0,1}, {1,0,1,0,1}, {1,1,1,1,1,1,1},
		{}, {0}, {1}, {1,1,1}, {1,0,0}, {0,0,0} }
	);
	// L(N7) = only the strings {00},{01},{10},{11}
	// L(N8) = all strings that if they are even, will be all 1's, and if they are odd, they are all 0's
	auto* N8_concat_N7 = concat(N8, N7);
	testNFA(N8_concat_N7, "N8_concat_N7", false, false,
		{ {0,0,0}, {1,1,1,1}, {1,1,0,0}, {0,1,1}, {0,0,0,0,1}, {0,0,0,1,1},
		{}, {0}, {1}, {1,1,1}, {1,0,0,0}, {0,0,0,1} }
	);
	// L(N8) = all strings that if they are even, will be all 1's, and if they are odd, they are all 0's
	// L(N9) = all strings that start and end with the char 1, with any 
	// amount of char's in between.
	auto* N9_concat_N8 = concat(N9, N8);
	testNFA(N9_concat_N8, "N9_concat_N8", false, false,
		{ {1,0,1}, {1,1,1,0,1}, {1,0,1,1,1}, {1,0,1,0}, {1,1,1,0,0,0}, {1,1,1},
		{}, {0}, {1}, {0,1,0}, {1,0,0,0}, {0,0,1} }
	);
	// L(N10) = any string that alternates between 1 and 0, starting with either 1 or 0.
	// N14 accepts {1}, {1,0}, {1,1}, {1,1,0}
	auto* N14_concat_N10 = concat(N14, N10);
	testNFA(N14_concat_N10, "N14_concat_N10", false, false,
		{ {1}, {1,0}, {1,0,1,0,1}, {1,1,0,1,0}, {1,1,0,1,0}, {1,1,1},
		{}, {0}, {0,0}, {0,0,0}, {0,0,0,0}, {0,0,0,1,0,1} }
	);
	/*
		TASK 37 - Write a dozen tests for your Kleene star function.
	*/
	auto* N1Star = star(N1);
	testNFA(N1Star, "N1Star", false, false,
		{ {}, {1,0,1,1}, {1,0,1,1,1,0,1,1}, {1,1,1,1,0,1,1}, {1,1,1,1,0,1,1,1,1,1}, {0,1,1,1,1,1},
		{1,0}, {0}, {1}, {0,1}, {0,1,0}, {0,1,0,0} }
	);
	auto* N2Star = star(N2);
	testNFA(N2Star, "N2Star", false, false,
		{ {}, {1,0,0}, {1,0,0,1,0,1}, {1,1,1,1,0,1,1,0,0}, {1,1,1,1,0,0}, {1,0,0,1,0,0,1,0,0},
		{1}, {0}, {1,1}, {1,0}, {0,1}, {1,0,0,1} }
	);
	// if L(N3) = all strings that are multiples of 2 or 3 under sigma = {0}, 
	// then N3* should accept a str of { 0,0,0,0,0,0,0 } (7 zeros)
	// because it accepts a string of {0,0,0,0} (4 zeros) and accepts a string of {0,0,0} (three zeros) 
	auto* N3Star = star(N3);
	testNFA(N3Star, "N3Star", false, false,
		{ {0,0,0,0,0,0,0}, {}, {0,0,0,0,0,0,0,0,0,0,0 }, {0,0,0,0,0}, {0,0}, {0,0,0},
		{0}}
	);
	auto* N4Star = star(N4);
	testNFA(N4Star, "N4Star", false, false,
		{ {}, {1,0,1,0}, {1,0,0,1,0,1,0}, {1,1,0,1,0,0}, {1,0,0,1,1,0,0,0}, {1,0,1,0,0,1,0,0,1,1,0},
		{0,1}, {1,0,1,0,1}, {1,0,0,1}, {1,0,1,0,1}, {0,0,1}, {0,0,1,0} }
	);
	auto* N5Star = star(N5);
	testNFA(N5Star, "N5Star", false, false,
		{ {}, {1,1}, {1,1,0,1}, {0,1,1}, {1}, {0,1,0,1},
		{0}, {0,0}, {1,0}, {1,0,0}, {1,1,0}, {1,1,0,1,0} }
	);
	auto* N6Star = star(N6);
	testNFA(N6Star, "N6Star", false, false,
		{ {}, {1,1}, {1,1,0,0}, {0,1,1,1,0,0}, {0,0,0,1,1,1,0,0}, {1,1,1,1,0,0,0,1,1},
		{1,1,0}, {0,0,1,0}, {1,0,0,1}, {1,1,1,0}, {0,1,1,0}, {0,1,1,1,0} }
	);
	
	auto* N7Star = star(N7);
	testNFA(N7Star, "N7Star", false, false,
		{ {}, {0,0}, {0,0,0,0}, {0,0,0,1,1,0,1,1}, {1,1,0,1,1,0,0,0}, {1,1,1,1},
		{1,1,1}, {0}, {0,0,0}, {1,1,0}, {0,0,1,1,0}, {0,1,0,0,1} }
	);
	// L(N8*) = all strings that have an even number of ones and any number of zeros
	auto* N8Star = star(N8);
	testNFA(N8Star, "N8Star", false, false,
		{ {}, {1,1}, {1,1,0}, {0,0,0,0,1,1}, {1,1,1,1,0}, {1,1,0,0,0},
		{1,0,0}, {0,0,1}, {1,1,1,0}, {1,1,1,0,0}, {1,0}, {1,1,1} }
	);
	auto* N9Star = star(N9);
	testNFA(N9Star, "N9Star", false, false,
		{ {}, {1,1,1}, {1,0,1,1,0,1}, {1,1,1,1,0,1,1}, {1,1,1,1,1,1}, {1,0,1,1,1,1},
		{1}, {0}, {1,0}, {0,1}, {1,0,0}, {1,0,1,0} }
	);
	// N10* accepts all strings under sigma = {0,1}
	auto* N10Star = star(N10);
	testNFA(N10Star, "N10Star", false, true,
		{ {}, {1}, {1,0,0,1}, {0,1,1,0}, {1,0,1,1,0,0,1,0,0,0,1}, {0} }
	);
	auto* N11Star = star(N11);
	testNFA(N11Star, "N11Star", false, false,
		{ {}, {1,0,1}, {1,0,0,1}, {1,1,0,0,1,0,1}, {1,0,1,1,0,0,1,0,0,0,1}, {1,0,1,0,0}, 
		{1}, {0}, {1,0}, {0,1}, {1,0,0}, {1,1,1,1,1,0} }
	);
	// L(N12*) = all strings that contain only char's of 2, 3, 4, 6, 8, and 9 
	// under sigma = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto* N12Star = star(N12);
	testNFA(N12Star, "N12Star", false, false,
		{ {}, {2,3,4}, {4,4,3}, {8,9}, {8,9,8,9,2,3}, {2,3,2},
		{0}, {1}, {3,4,5}, {7}, {1,2,3,4}, {2,3,9,7} }
	);
	auto* N13Star = star(N13);
	testNFA(N13Star, "N13Star", false, false,
		{ {}, {0,1}, {0,1,1}, {1,1,1,1,1,1}, {0,1,0,1,0,1}, {0,1,1,0,1},
		{0,0}, {1,0}, {0,1,0}, {1,1,0}, {1,1,1,1,0}, {0,1,0,1,1,0} }
	);
	auto* N14Star = star(N14);
	testNFA(N14Star, "N14Star", false, false,
		{ {}, {1}, {1,0,1}, {1,1,0}, {1,0,1,1}, {1,1,1,1,0,1},
		{0}, {0,1}, {0,1,1}, {0,0}, {0,0,0}, {0,0,0,1,0} }
	);
	/*
		TASK #39 - Ensure that all of your NFA tests return the correct results 
		when converted to DFAs and run through the DFA accept function.
	*/
	auto* N1d = NFAtoDFA(N1);
	testDFA(N1d, "N1d", false, false,
		{ {1,0,1,1},{1,1,1},{0,1,0,1,1,0},{0,0,0,1,0,1},{1,0,1,0,1,0},{1,1} },
		{ {1}, {}, {1,0}, {0,1}, {0,1,0}, {0,0,0,1} });
	testQ_q0_F(N1d,
		{ {0},{0,1,2},{0,1,3,2},{0,2},{0,2,3},{0,1,3} },
		{ 0 },
		{ {0,1,2,3}, {0,1,3}, {0,2,3}, {0,3} });
	auto* N2d = NFAtoDFA(N2);
	testDFA(N2d, "N2d", false, false,
		{ {1,0,0},{1,0,1},{1,1,1},{0,0,0,0,1,0,0},{0,1,0,0},{0,1,1,0} },
		{ {}, {1,1}, {1,0}, {0,1}, {0,0,0}, {0,0,0,1} });
	auto* N3d = NFAtoDFA(N3);
	testDFA(N3d, "N3d", false, false,
		{ {0,0},{0,0,0},{0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0} },
		{ {0}, {0,0,0,0,0}, {0,0,0,0,0,0,0}});
	auto*N4d = NFAtoDFA(N4);
	testDFA(N4d, "N4DFA", false, false,
		{ {1,0,1,0},{0},{},{1,0,0},{1,1,0},{0,0} },
		{ {1,1}, {1,0,1}, {1,1,1}, {0,1}, {0,1,0}, {0,1,0,1,1} });
	auto* N5d = NFAtoDFA(N5);
	testDFA(N5d, "N5d", false, false,
		{ {0,1},{1},{0,0,0,1},{0,0,1},{0,0,0,0,1},{0, 0, 0, 0, 0, 1} },
		{ {0}, {}, {1,0}, {1,1}, {1,1,1,0}, {0,1,0} });
	auto* N6d = NFAtoDFA(N6);
	testDFA(N6d, "N6d", false, false,
		{ {1,1},{0,0},{0,1,1},{1,0,0},{0,1,0,0},{1,0,1,1} },
		{ {}, {1}, {0}, {0,1,0}, {1,0}, {0,1,1,0} });
	// L(N7d) = only the strings of {00},{01},{10},{11}
	auto* N7d = NFAtoDFA(N7);
	testDFA(N7d, "N7d", false, false,
		{ {0,0},{0,1},{1,0},{1,1},{1,1},{1,1} },
		{ {}, {1}, {0}, {1,1,0}, {0,1,0}, {1,0,1,0,1,0,0,0,1} });
	auto* N8d = NFAtoDFA(N8);
	testDFA(N8d, "N8d", false, false,
		{ {1,1},{1,1,1,1},{0},{0,0,0},{0,0,0,0,0},{1,1,1,1,1,1} },
		{ {1}, {0,0}, {0,0,0,0}, {1,0}, {1,1,1}, {0,0,0,0,0,0} });
	auto* N9d = NFAtoDFA(N9);
	testDFA(N9d, "N9d", false, false,
		{ {1,1,1},{1,0,1},{1,0,0,0,1},{1,0,1,0,1},{1,0,1,1},{1,1} },
		{ {}, {0}, {0,1}, {0,1,1}, {1,0,1,0}, {1} });
	auto* N10d = NFAtoDFA(N10);
	testDFA(N10d, "N10d", false, false,
		{ {},{1},{0},{1,0},{0,1,0,1,0},{1,0,1} },
		{ {1,0,0}, {1,1}, {0,0}, {1,0,1,0,0}, {0,1,1,0,1}, {1,0,1,0,0,1} });
	auto* N11d = NFAtoDFA(N11);
	testDFA(N11d, "N11d", false, false,
		{ {1,0,1},{1,0,1,1},{1,0,1,0},{1,1,0,1,1},{1,1,0,0,0,1},{1,0,0,1} },
		{ {}, {1}, {0}, {1,1,0}, {1,0,0}, {0,1} });
	auto* N12d = NFAtoDFA(N12);
	testDFA(N12d, "N12d", false, false,
		{ {},{2,4},{6,8},{3,3,9,6,9},{6},{2,6,6} },
		{ {2,3}, {4,6,9}, {2,4,9}, {9,3,2}, {1}, {4,4,6,2,2,2,9} });
	auto* N13d = NFAtoDFA(N13);
	testDFA(N13d, "N13d", false, false,
		{ {1},{0,1},{1},{1},{1},{1} },
		{ {0}, {1,0}, {1,1,0}, {0,1,1}, {1,1}, {1,1,1,1,0} });
	auto* N14d = NFAtoDFA(N14);
	testDFA(N14d, "N14d", false, false,
		{ {1},{1,1},{1,0},{1,1,1,0},{1,1,0},{1,0,0,0} },
		{ {}, {0}, {0,1}, {0,0,1}, {0,0,0,1}, {0,0,0} });
	auto* N15d = NFAtoDFA(N15);
	testDFA(N15d, "N15d", false, false,
		{ {0,1},{0,0,0,1},{1,1},{1,0,0,1},{0,0,0,0,0,1},{1,0,0,0,0,1} },
		{ {}, {1}, {1,0}, {1,0,0}, {0,0}, {0,1,0} });
	/*
		TASK #40 - Manually convert a few NFAs to DFAs and verify the output of your compiler with your DFA equality function.
	*/
	// N4 manually converted into the DFA N4manual. 
	// after each definition, there is a testing for equality using the DFA equality function
	// to ensure that the manually created DFA is equal to the NFA that was converted into a DFA
	DFA<int, int>* N4manual = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3) || (s == 4) || (s == 5); },
		0,
		[](int s, int c) {
			if (s == 0 && c == 0)
				return 0;
			if (s == 0 && c == 1)
				return 1;
			if (s == 1 && c == 0)
				return 2;
			if (s == 1 && c == 1)
				return 4;
			if (s == 2 && c == 0)
				return 3;
			if (s == 2 && c == 1)
				return 4;
			if (s == 3 && c == 0)
				return 3;
			if (s == 3 && c == 1)
				return 2;
			if (s == 4 && c == 0)
				return 0;
			if (s == 4 && c == 1)
				return 5;
			if (s == 5)
				return 5;
		},
		[](int s) {return s == 0 || s == 3 ; }
		);
	testEquality(N4manual, N4d, true, "N4manual=N4d", binaryAlpha);
	testQ_q0_F(N4d,
		{ {0,2},{1},{1,2},{0,1,2},{2,1},{},{0,2,5},{3},{1,0,0},{0,1,2,3},{0,2,0} },
		{ 0, 2 },
		{ {0,2},{0,2,1},{1,2,0}, {2,0},{1,0,2},{2,1,0},{},{2},{1,0,0},{0,1,2,3},{1} });
	// N8 manually converted into the DFA N8manual
	DFA<int, int>* N8manual = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3) || (s == 4) || (s == 5); },
		0,
		[](int s, int c) {
			if (s == 0 && c == 0)
				return 4;
			if (s == 0 && c == 1)
				return 2;
			if (s == 1 && c == 0)
				return 5;
			if (s == 1 && c == 1)
				return 2;
			if (s == 2 && c == 0)
				return 5;
			if (s == 2 && c == 1)
				return 1;
			if (s == 3 && c == 0)
				return 4;
			if (s == 3 && c == 1)
				return 5;
			if (s == 4 && c == 0)
				return 3;
			if (s == 4 && c == 1)
				return 5;
			if (s == 5)
				return 5;
		},
		[](int s) {return s == 0 || s == 1 || s == 4; }
		);
	testEquality(N8manual, N8d, true, "N8manual=N8d", binaryAlpha);
	// N5 manually converted into the DFA N5manual
	// This NFA could run infinitely so I wanted to test this one to make sure it worked right
	DFA<int, int>* N5manual = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2); },
		0,
		[](int s, int c) {
			if (s == 0 && c == 0)
				return 0;
			if (s == 0 && c == 1)
				return 1;
			if (s == 1)
				return 2;
			if (s == 2)
				return 2;
		},
		[](int s) {return s == 1; }
		);
	testEquality(N5manual, N5d, true, "N5manual=N5d", binaryAlpha);
	// N1 NFA converted into the DFA named N1manual
	DFA<int, int>* N1manual = new DFA<int, int>(
		[](int s) {return (s == 0) || (s == 1) || (s == 2) || (s == 3) || (s == 4) || (s == 5); },
		0,
		[](int s, int c) {
			if (s == 0 && c == 0)
				return 0;
			if (s == 0 && c == 1)
				return 1;
			if (s == 1 && c == 0)
				return 3;
			if (s == 1 && c == 1)
				return 2;
			if (s == 2 && c == 0)
				return 4;
			if (s == 2 && c == 1)
				return 2;
			if (s == 3 && c == 0)
				return 0;
			if (s == 3 && c == 1)
				return 2;
			if (s == 4 && c == 0)
				return 5;
			if (s == 4 && c == 1)
				return 2;
			if (s == 5 && c == 0)
				return 5;
			if (s == 5 && c == 1)
				return 2;
		
		},
		[](int s) {return s == 2 || s == 4 || s == 5; }
		);
	testEquality(N1manual, N1d, true, "N1manual=N1d", binaryAlpha);

	return 0;
}
/*
	********** FUNCTION DEFINITIONS **********
*/
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
template<typename State, typename C>
void testDFA(DFA<State, C>* dfa, string DFAName, bool noAccepts, bool allAccepts,
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
}
// Task #12
template<typename State, typename C>
pair<bool, list<int>> wouldBeAccept(DFA<State, C>* dfa, list<int> sigma) {
	pair<bool, list<int>> ret;
	ret.first = false;
	list<Config<State>> h = { Config<State>(dfa->q0, {}) };
	list<State> v = {dfa->q0};
	State qi, qj;
	list<int> w; //Str
	while (!h.empty()) {
		qi = h.front().curS;
		w = h.front().curStr;
		h.pop_front();
		if (dfa->F(qi)) { // if you've reached a state that accepts, return that string
			ret.first = true;
			ret.second = w;
			break;
		}
		for (auto i : sigma) {
			qj = dfa->d(qi, i); // get the next state
			auto found = find(v.begin(), v.end(), qj); // find algorithm
			if (found == v.end()) {	// if its wasnt found, push into visited  
				v.push_back(qj);
				w.push_back(i);
				h.push_back(Config<State>(qj, w));
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
DFA<State, C> *complement(DFA<State, C> *dfa) {
	DFA<State, C> *cDFA = new DFA<State, C>(
		dfa->Q,
		dfa->q0,
		dfa->d,
		[=](State s) { return !dfa->F(s); }
		);
	return cDFA;
}
// Task #14 - union
template<typename State, typename State2, typename C>
DFA<pair<State, State2>, C>* unionDFA(DFA<State, C> *A, DFA<State2, C> *B) {
	DFA<pair<State, State2>, C>* uDFA = new DFA<pair<State, State2>, C>(
		[=](pair<State, State2> s) { return A->Q(s.first) && B->Q(s.second); },
		pair<State, State2>(A->q0, B->q0),
		[=](pair<State, State2> s, C c) {
			return pair<State, State2>(A->d(s.first, c), B->d(s.second, c));
		},
		[=](pair<State, State2> s) {
			return (A->F(s.first) && B->Q(s.second)) || A->Q(s.first) && (B->F(s.second));
		}
		);
	return uDFA;
}
//Task #15
template<typename State1, typename State2, typename C>
void testUandInter(DFA<pair<State1,State2>, C>*dfa, string DFAName, bool noAccepts, bool allAccepts, 
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
}// Task # 16 - intersect
template<typename State, typename State2, typename C>
DFA<pair<State, State2>, C>* intersect(DFA<State, C> *A, DFA<State2, C> *B) {
	DFA<pair<State, State2>, C>* uDFA = new DFA<pair<State, State2>, C>(
		[=](pair<State, State2> s) { return A->Q(s.first) && B->Q(s.second); },
		pair<State, State2>(A->q0, B->q0),
		[=](pair<State, State2> s, C c) {
			return pair<State, State2>(A->d(s.first, c), B->d(s.second, c));
		},
		[=](pair<State, State2> s) {
			return A->F(s.first) && B->F(s.second);
		}
		);
	return uDFA;
}
/*
Task # 18
(Subset) Write a function which takes two DFAs (X and Y) and returns 
whether every string accepted by X is also accepted by Y.
*/
template<typename State1, typename State2, typename C>
bool subset(DFA<State1, C> *X, DFA<State2, C> *Y, list<int> sigma) {
	if (wouldBeAccept(intersect(complement(Y), X), sigma).first) {
		return false;
	}
	return true;
}

template<typename State1, typename State2, typename C>
void testSubset(DFA<State1, C>* X, DFA<State2, C>* Y, bool answer, string name, list<int> sigma) {
	if (!(subset(X, Y, sigma) == answer)) {
		cout << endl << "### FAIL: " << name << " ###" << endl;
	}
}
/*Task #20 - (Equality) Write a function which takes two DFAs (X and Y) and returns 
whether every string accepted by X is also accepted by Y and vice versa.*/
template<typename State1, typename State2, typename C>
bool equality(DFA<State1, C>* X, DFA<State2, C>* Y, list<int> sigma) {
	if (subset(X, Y, sigma) && subset(Y, X, sigma)) {
		return true;
	}
	return false;
}
template<typename State1, typename State2, typename C>
void testEquality(DFA<State1, C>* X, DFA<State2, C>* Y, bool answer, string name, list<int> sigma) {
	if (!(equality(X, Y, sigma) == answer)) {
		cout << endl << "### FAIL: " << name << " ###" << endl;
	}
}
/*
	TASK #24 - Write a (trivial) function that converts DFAs into NFAs.
*/
template<typename State, typename C>
NFA<State, C>* DFAtoNFA(DFA<State, C>* dfa) {
	NFA<int, int>* nfa = new NFA<int, int>(
		[dfa](int s) {return dfa->Q(s); },
		dfa->q0,
		[dfa](int s, int c) {return list<int>{dfa->d(s, c)}; },
		[dfa](int s) {return list<int>{}; },
		[dfa](int s) {return dfa->F(s); }
		);

	return nfa;
}
template<typename State, typename C>
void testNFA(NFA<State, C>*nfa, list<int> str) {
	int tempState = nfa->q0;
	list<int> setState;
	while (!str.empty()) {
		setState = nfa->d1(tempState, str.front());
		str.pop_front();
		tempState = setState.front();
	}
	if (!nfa->F(tempState)) {
		cout << "### FAIL:  ###";
	}
}
template<typename State>
list<Config<State>> createTrace(list<State> states, list<int> str) {
	list<Config<State>> lc;
	while (!states.empty()) {
		if (states.front() == -1) {
			//pop off two states leave the str, then pushback
			states.pop_front();
			lc.push_back(Config<State>(states.front(), str));
			states.pop_front();
		}
		else {
			lc.push_back(Config<State>(states.front(), str));
			if (!str.empty()) {
				str.pop_front();
			}
			states.pop_front();
		}
	}
	return lc;
}
/*
	27 - Oracle
*/
template<typename State, typename C>
bool oracle(NFA<State, C>* nfa, list<int> str, list<Config<State>> ts) {
	State qi = nfa->q0;
	list<State> possibleStates1; // for d1
	list<State> possibleStates2; // for d2
	list<int> nextStr = str;
	// check that the first state and string passed to the function match with the first config in the list
	if ((!(ts.front().curS == qi) || (!(ts.front().curStr == str)))) { 
		return false;
	}
	// pop off first configuration out of the trace
	if (ts.empty())
		return false;
	else
		ts.pop_front();
	while (!ts.empty()) {
		if (!str.empty()) {
			possibleStates1 = nfa->d1(qi, str.front());  
		}
		else {
			possibleStates1 = {};
		}
		possibleStates2 = nfa->d2(qi);
		auto found1 = find(possibleStates1.begin(), possibleStates1.end(), ts.front().curS);
		auto found2 = find(possibleStates2.begin(), possibleStates2.end(), ts.front().curS);
		if (found1 != possibleStates1.end()) {
			if (!nextStr.empty()){
				nextStr.pop_front();
			}
			if (ts.front().curStr == nextStr) {
				if (!str.empty()) {
					str.pop_front();
				}
				qi = *found1;
				ts.pop_front();
			}
			else {
				qi = *found2;
				ts.pop_front();
			}
		}
		else if ((found2 != possibleStates2.end()) && (ts.front().curStr == str)) {
			qi = *found2;
			ts.pop_front();
		}
		else {
			return false;
		}
	}
	return true;
}
template<typename State, typename C>
void oracleLoop(NFA<State, C>* nfa, string name, list<list<int>> strs, list<list<Config<State>>> ts) {
	list<list<int>>::iterator strsIt = strs.begin();
	int count = 1;
	for (auto i : ts) {
		if (!oracle(nfa, *strsIt, i)) {
				cout << "### FAIL-oracle at C"<< count << name << " ###" << endl;
				printConfigList(i);
				cout << endl;
		}
		strsIt++;
		count++;
	}
}
/*
	TASK 30 - 	(Forking) Write a function that given an NFA and a string, returns a tree of all possible traces.
*/

template<typename State, typename C>
shared_ptr <TT<State, C>> forking(NFA<State, C>* nfa, list<int> str ) {
	shared_ptr<TT<State, C>> tt = make_shared<TT<State, C>>(nfa->q0, nfa->d1, nfa->d2, str);
	pair<list<int>, list<int>> next;
	list<list<int>> dResults;
	list<shared_ptr<TT<State, C>>> nextTreeL;
	list<int> tempStr = tt->curStr;
	
	cout << "Root: " << tt->branch;
	cout << "-";
	tt->printCurStr();
	
	tempStr.pop_front();
	cout << endl;
	if (!tt->curStr.empty()) {
		dResults.push_back(tt->d.first(tt->branch, str.front()));
		dResults.push_back(tt->d.second(tt->branch));
		next.first = dResults.front();
		next.second = dResults.back();
		nextTreeL = tt->push2(next);
		tt->printTreeL();
		cout << endl;
		treeLoop(nextTreeL, tempStr);
	}
	return tt;
}
template<typename State, typename C>
void treeLoop(list<shared_ptr <TT<State, C>>> tL, list<int> str) {
	list<shared_ptr <TT<State, C>>> temp;
	pair<list<int>, list<int>> next;
	list<list<int>> dResults;
	for (auto i : tL) {
		cout << i->branch << "-";
		i->printCurStr();
		cout << endl;
		if (!i->curStr.empty()) {
			
			dResults = {};
			dResults.push_back(i->d.first(i->branch, i->curStr.front()));
			dResults.push_back(i->d.second(i->branch));
			next.first = {};
			next.second = {};
			next.first = dResults.front();
			next.second = dResults.back();
			temp = {};
			temp = i->push2(next);
			treeLoop(temp, str);
		}
		else {
			dResults = {};
			dResults.push_back(i->d.second(i->branch));
			if (!dResults.empty()) {
				next.first = {};
				next.second = {};
				next.second = dResults.front();
				temp = {};
				temp = i->push2(next);
				treeLoop(temp, str);
			}
			else {
				continue;
			}
			
		}
	}
}
template<typename State, typename C>
void testNFAAccepts(NFA<State, C>* nfa, list<int> str, bool strShouldAccept, string name) {
	if (strShouldAccept) {
		if (!(nfa->accepts(str))) {
			cout << "### " << name << " YOU FAIL : The string was rejected when it should have accepted ###" << endl;
		}
	}
	else {
		if (nfa->accepts(str)) {
			cout << "### " << name << " YOU FAIL : The string accepted when it should have rejected ###" << endl;
		}
	}
}
/*
		
TASk #33 - (Union) Write a function that takes two NFAs and returns a third NFA that 
			accepts a string if either argument accepts it.
*/
template<typename State, typename C>
NFA<pair<int, State>, C>* unionNFA(NFA<State, C>* a, NFA<State, C>* b) {
	NFA<pair<int, State>, C>* nfa = new NFA<pair<int, State>, C>(
		[=](pair<int, State> s) {
			return (((s.first == 0) && a->Q(s.second)) || ((s.first == 1) && b->Q(s.second)) || (s.first == -1 && s.second == -1));
		},
		pair<int, State>(-1, -1),
		[=](pair<int, State> s, C c) {
			if (s.first == 0) {
				return nfaH(a->d1(s.second, c), 0);
			}
			else if (s.first == 1) {
				return nfaH(b->d1(s.second, c), 1);
			}
			else
				return list<pair<int, State>>{};
		},
		[=](pair<int, State> s) {
			if (s.first == -1 && s.second == -1) {
				return list<pair<int, State>>{pair<int, State>(0,a->q0), pair<int, State>(1,b->q0)};
			}
			else if (s.first == 0) {
				return nfaH(a->d2(s.second), 0);
			}
			else if (s.first == 1) {
				return nfaH(b->d2(s.second), 1);
			}
			else
				return list<pair<int, State>>{};
		},
		[=](pair<int, State> s) {
			return ((s.first == 0) && (a->F(s.second))) || ((s.first == 1) && (b->F(s.second)));
		});
	return nfa;
}
/*
	TASK #34 - (Concatenation) Write a function that takes two NFAs and returns a third NFA that accepts 
	a string if it can be broken into two pieces, one accepted by the first NFA and the other accepted by the second.
*/
template<typename State, typename C>
NFA<pair<int, State>, C>* concat(NFA<State, C>* a, NFA<State, C>* b) {
	NFA<pair<int, State>, C>* nfa = new NFA<pair<int, State>, C>(
		[=](pair<int, State> s) {
			return (((s.first == 0) && a->Q(s.second)) || ((s.first == 1) && b->Q(s.second)));
		},
		pair<int, State>(0, a->q0),
		[=](pair<int, State> s, C c) {
			if (s.first == 0) {
				return nfaH(a->d1(s.second, c), 0);
			}
			else if (s.first == 1) {
				return nfaH(b->d1(s.second, c), 1);
			}
			else
				return list<pair<int, State>>{};
		},
		[=](pair<int, State> s) {
			if (s.first == 0) {
				list<pair<int, State>>temp = nfaH(a->d2(s.second), 0);
				if (a->F(s.second)) {
					temp.push_back(pair<int, State>(1, b->q0));
					return temp;
				}
				else 
					return temp;
			}
			else if (s.first == 1) {
				return nfaH(b->d2(s.second), 1);
			}
			else
				return list<pair<int, State>>{};
		},
		[=](pair<int, State> s) {
			return ((s.first == 1) && (b->F(s.second)));

		});
	return nfa;
}
template<typename State>
list<pair<int, State>> nfaH(list<State> l, int tag) {
	list<pair<int, State>> ret;
	for (auto i : l) {
		ret.push_back(pair<int, State>(tag, i));
	}
	return ret;
}
template<typename State, typename C>
void testNFA(NFA<State, C> *nfa, string name, bool noAccepts, bool allAccepts,
	list<list<int>> strL) {
	int count = 0;
	for (auto i : strL) {
		if (!allAccepts) {
			if (count > 5) {
				if (nfa->accepts(i)) {
					cout << "\t\t" << name << "### FAIL at index " << count << endl;
				}
			}
		}
		if (!noAccepts) {
			if (count <= 5) {
				if (!nfa->accepts(i)) {
					cout << "\t\t" << name << "### FAIL at index " << count << endl;
				}

			}
		}
		count++;
	}
}
/*
	TASK #36 - (Kleene Star) Write a function that takes an NFA and returns a new NFA that 
	accepts a string if it can be broken into N pieces, each accepted by the argument.
*/
template<typename State, typename C>
NFA<State, C>* star(NFA<State, C>* a) {
	NFA<State, C>* nfa = new NFA<State, C>(
		[=](State s) {
			return ((a->Q(s)) || (s == -1));
		},
		-1,
		[=](State s, C c) {
			if (s != -1)
				return a->d1(s, c);
			else
				return list<State>{};
		},
		[=](State s) {
			if (s != -1) {
				if (a->F(s)) {
					list<State> temp = a->d2(s);
					temp.push_back(-1);
					return temp;
				}
				else
					return a->d2(s);
			}	
			else if (s == -1) 
				return list<State>{a->q0};
			else
				return list<State>{};
		},
		[=](State s) {
			return s == -1;
		});
	return nfa;
}
/*
	TASK #38 - Write a function which converts an NFA into a DFA that accepts the same language.
*/
template<typename State, typename C>
DFA<list<State>, C> * NFAtoDFA(NFA<State, C> *nfa) {
	DFA<list<State>, C>* dfa = new DFA<list<State>, C>(
		[nfa](list<State> s) {
			if (s == list<State>{}) {
				return true;
			}
			list<int> v;
			for (auto i : s) {
				auto found = find(v.begin(), v.end(), i);
				if (found != v.end()) {
					return false;
				}
				if (!nfa->Q(i)) {
					return false;
				}
				else
					v.push_back(i);
			}
			return true;
		},
		E(list<State>{nfa->q0}, nfa),
		[nfa](list<State> s, C c) { 
			list<State> ret;
			list<State> u;
			if (s == list<State> {}) {
				return list<State> {};
			}
			for (auto i : s) {
				ret = nfa->d1(i,c);
				for (auto j : ret) {
					auto found = find(u.begin(), u.end(), j);
					if (found == u.end()) {
						u.push_back(j);
					}
				}
			}
			if (E(u, nfa) == list<State>{}) {
				return list<State> {};
			}
			else {
				return E(u, nfa);
			}
		},
		[nfa](list<State> s) {
			list<State> v;
			for (auto i : s) {
				auto found = find(v.begin(), v.end(), i);
				if (found != v.end() || s.empty()) {
					return false;
				}
				else {
					v.push_back(i);
				}
			}
			for (auto i : s) {
				if (!nfa->Q(i)) {
					return false;
				}
			}
			for (auto i : s) {
				if (nfa->F(i)) {
					return true;
				}
			}
			return false; }
		);
	return dfa;
}
template<typename State, typename C>
list<State> E(list<State> x, NFA<State, C>* nfa) {
	bool changed = true;
	while (changed) {
		changed = false;
		for (auto i : x) {
			list<State> states = nfa->d2(i);
			for (auto j : states) {
				auto found = find(x.begin(), x.end(), j);
				if (found == x.end()) {
					changed = true;
					x.push_back(j);
					E(x,nfa);
				}
			}
		}
	}
	return x;
}
template<typename State, typename C>
void testQ_q0_F(DFA<State, C>*dfa, list<list<int>>Q, list<int>q0, list<list<int>>F) {
	int count = 0;
	for (auto i : Q) {
		if (count < 6) {
			if (!dfa->Q(i)) {
				cout << "FAIL accepts NFA->Q at " << count << endl;
			}
		}
		if (count >= 6) {
			if (dfa->Q(i)) {
				cout << "FAIL reject NFA->Q at " << count << endl;
			}
		}
		count++;
	}
	// testing N4DFA->q0
	if (dfa->q0 != q0) {
		cout << "FAIL q0" << endl;
	}
	// testing N4DFA->F
	count = 0;
	for (auto i : F) {
		if (count < 6) {
			if (!dfa->F(i)) {
				cout << "FAIL accepts NFA->F at " << count << endl;
			}
		}
		if (count >= 6) {
			if (dfa->F(i)) {
				cout << "FAIL reject NFA->F at " << count << endl;
			}
		}
		count++;
	}
}