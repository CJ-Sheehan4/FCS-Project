#include <iostream>
#include <list>
using namespace std;
list<list<int>> getLayer(list<list<int>> layerOne, list<int> sigma, int N);
void printLayer(list<list<int>> layer);
int main() {
	//Task #1
	list<int> sigma = { 0, 1 };	// -1 represents epsilon, the alphabet consists of positive integers, including 0
	//Task #2 - using a list to represent a string 
	list<list<int>> layerOne;
	layerOne = getLayer(layerOne, sigma, 2);
	printLayer(layerOne);
	return 0;
}
list<list<int>> getLayer(list<list<int>> layer, list<int> sigma, int N) {
	list<int>::iterator i;
	list<list<int>>::iterator j;
	list<int> epsilon = { -1 };
	int count = 0;
	layer.push_back(epsilon);
	while (count < N) {
		if (count == 1) {
			for (i = sigma.begin(); i != sigma.end(); i++) {
				list<int> temp;
				temp.push_back(*i);
				layer.push_back(temp);
			}
		}
		else {
			
		}
		count++;
	}
	
	return layer;
}
void printLayer(list<list<int>> layer) {
	list<list<int>>::iterator rowIt;
	list<int>::iterator columnIt;
	for (rowIt = layer.begin(); rowIt != layer.end(); rowIt++) {
		for (columnIt = rowIt->begin(); columnIt != rowIt->end(); columnIt++) {
			cout << *columnIt << " ";
		}
		cout << " | ";
	}
}