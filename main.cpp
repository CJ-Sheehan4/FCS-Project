#include <iostream>
#include <list>
#include "DFA.h"
#include "DFA.cpp"
//#include "testDFA.cpp"
using namespace std;
list<list<int>> getLayer(list<int> sigma, int N);
list<int> lexi(list<int> sigma, int N);
void printLayer(list<list<int>> layer);
void printElement(list<int> element);
int main() {
	//Task #1
	list<int> sigma = { 0,1 };	// -1 represents epsilon, the alphabet consists of positive integers, including 0

	//Task #2 - using a list to represent a string 
	list<list<int>> layerOne = getLayer(sigma, 3);
	printLayer(layerOne);
	cout << endl;
	list<int> element = lexi(sigma, 3);
	printElement(element);
	
	//testing DFA class
	cout << endl << "Testing DFA:" << endl;
	//test0();
	DFA<char, int>* test = new DFA<char, int>(
		[](char s) {return s == 'A'; },
		'A',
		[](char s, int c) {return s; },
		[](char s) {return s == 'A'; }
		);
	cout << test->d('A', 1);
	test->setd([](char s, int c) {return 'B'; });
	cout << test->d('B', 1);

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
	list<int> str = { 0,1 };
	list<int> emptyStr = { -1 };

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
			for (i = sigma.begin(); i != sigma.end(); i++) {
				temp.push_back(*i);
				layer.push_back(temp);
				temp.clear();
			}
			uniLayers.push_back(layer);
		}
		else if(count > 1){
			layer.clear();
			layer = uniLayers.back();
			for (sigmaIt = sigma.begin(); sigmaIt != sigma.end(); sigmaIt++) {
				for (j = layer.begin(); j != layer.end(); j++) {
					for (i = j->begin(); i != j->end(); i++) {
						temp.push_back(*i);
					}
					temp.push_front(*sigmaIt);
					newLayer.push_back(temp);
					temp.clear();
				}
			}
			uniLayers.push_back(newLayer);
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
		layerN = getLayer(sigma, i);
		int size = layerN.size();
		if (N >= size) {
			N = N - size;
		}
		else {
			it = layerN.begin();
			while (N > 0) {
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
