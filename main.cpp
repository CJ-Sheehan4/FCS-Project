#include <iostream>
#include <list>
using namespace std;
list<int> layer(list<int> sigma, int N);
int main() {
	//Task #1
	list<int> sigma = { 0, 1 };
	//Task #2 - using a list to represent a string 
	list<int> str = layer(sigma, 1);
	return 0;
}
list<int> layer(list<int> sigma, int N) {
	return sigma;
}
