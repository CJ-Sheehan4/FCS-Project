/*
		TASK 41 - Define a data type to represent regular expressions.
*/
#ifndef RX_H
#define RX_H
#include <iostream>
#include <list>
template<typename State,typename C>
class RX {
public:
	/*
	TASK 42 - Write a printer for regular expressions.
	*/
	virtual void print(void) = 0;
	virtual char id(void) = 0;
	virtual RX<State, C>* getL(void) = 0;
	virtual RX<State, C>* getR(void) = 0;
	virtual C getC(void) = 0;
};
template<typename State, typename C>
class RX_Null : public RX<State, C> {
public:
	RX_Null() {}
	void print(void) override {
		cout << "null";
	}
	char id(void) override{
		return 'n';
	}
	RX<State, C>* getL(void) override {
		return nullptr;
	}
	RX<State, C>* getR(void) override {
		return nullptr;
	}
	C getC(void) override {
		return -1;
	}
};
template<typename State, typename C>
class RX_Epsilon : public RX<State, C> {
public:
	RX_Epsilon() {}
	void print(void) override {
		cout << "e";
	}
	char id(void) override {
		return 'e';
	}
	RX<State, C>* getL(void) override {
		return nullptr;
	}
	RX<State, C>* getR(void) override {
		return nullptr;
	}
	C getC(void) override {
		return -1;
	}
};
template<typename State, typename C>
class RX_Char : public RX<State, C> {
public:
	RX_Char(C initC) : c(initC) {}
	void print(void) override {
		cout << c;
	}
	char id(void) override {
		return 'c';
	}
	RX<State, C>* getL(void) override {
		return nullptr;
	}
	RX<State, C>* getR(void) override {
		return nullptr;
	}
	C getC(void) override {
		return c;
	}
	C c;
};
template<typename State, typename C>
class RX_Union : public RX<State, C> {
public:
	RX_Union(RX<State, C>*initL, RX<State, C>*initR) : l(initL), r(initR) {}
	void print(void) override {
		cout << "(";
		this->l->print();
		cout << "U";
		this->r->print();
		cout << ")";
	}
	char id(void) override {
		return 'u';
	}
	RX<State, C>* getL(void) override {
		return l;
	}
	RX<State, C>* getR(void) override {
		return r;
	}
	C getC(void) override {
		return -1;
	}
	RX<State, C>*l;
	RX<State, C>*r;
};
template<typename State, typename C>
class RX_Star : public RX<State, C> {
public:
	RX_Star(RX<State, C>*initRX) : next(initRX) {}
	void print(void) override {
		this->next->print();
		cout << "*";
	}
	char id(void) override {
		return 's';
	}
	RX<State, C>* getL(void) override {
		return next;
	}
	RX<State, C>* getR(void) override {
		return next;
	}
	C getC(void) override {
		return -1;
	}
	RX<State, C>*next;
};
template<typename State, typename C>
class RX_Circ : public RX<State, C> {
public:

	RX_Circ(RX<State, C>*initL, RX<State, C>*initR) : l(initL), r(initR) {}
	void print(void) override {
		cout << "(";
		this->l->print();
		cout << "o";
		this->r->print();
		cout << ")";
	}
	char id(void) override {
		return 'o';
	}
	RX<State, C>* getL(void) override {
		return l;
	}
	RX<State, C>* getR(void) override {
		return r;
	}
	C getC(void) override {
		return -1;
	}
	RX<State, C>*l;
	RX<State, C>*r;
};
#endif