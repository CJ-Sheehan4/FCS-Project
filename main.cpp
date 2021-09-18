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
	layerOne = getLayer(layerOne, sigma, 4);
	printLayer(layerOne);
	return 0;
}
list<list<int>> getLayer(list<list<int>> layer, list<int> sigma, int N) {
	list<int>::iterator i;
	list<list<int>>::iterator j;
	list<int>::iterator sigmaIt;
	list<list<list<int>>> uniLayers;
	list<list<int>> newLayer;
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