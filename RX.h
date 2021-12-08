/*
		TASK 41 - Define a data type to represent regular expressions.
*/
#ifndef RX_H
#define RX_H
#include <iostream>
#include <list>
template<typename C>
class RX {
public:
	/*
	TASK 42 - Write a printer for regular expressions.
	*/
	virtual void print(void) = 0;
};
template<typename C>
class RX_Null : public RX<C> {
public:
	RX_Null() {}
	void print(void) override {
		cout << "null";
	}
};
template<typename C>
class RX_Epsilon : public RX<C> {
public:
	RX_Epsilon() {}
	void print(void) override {
		cout << "e";
	}
};
template<typename C>
class RX_Char : public RX<C> {
public:
	RX_Char(C initC) : c(initC) {}
	void print(void) override {
		cout << c;
	}
	C c;
};
template<typename C>
class RX_Union : public RX<C> {
public:
	RX_Union(RX<C> *initL, RX<C> *initR) : l(initL), r(initR) {}
	void print(void) override {
		cout << "(";
		this->l->print();
		cout << "U";
		this->r->print();
		cout << ")";
	}
	RX<C> *l;
	RX<C> *r;
};
template<typename C>
class RX_Star : public RX<C> {
public:
	RX_Star(RX<C> *initRX) : next(initRX) {}
	void print(void) override {
		this->next->print();
		cout << "*";
	}
	RX<C> *next;
};
template<typename C>
class RX_Circ : public RX<C> {
public:

	RX_Circ(RX<C> *initL, RX<C> *initR) : l(initL), r(initR) {}
	void print(void) override {
		cout << "(";
		this->l->print();
		cout << "o";
		this->r->print();
		cout << ")";
	}
	RX<C> *l;
	RX<C> *r;
};
#endif