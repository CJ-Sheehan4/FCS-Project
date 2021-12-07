#ifndef RX_H
#define RX_H
#include <iostream>
#include <list>
template<typename C>
class RX {
public:
	virtual void print(void) = 0;
};
template<typename C>
class RX_Empty : public RX<C> {
public:
	void print(void) override {
	}
};
template<typename C>
class RX_Epsilon : public RX<C> {
public:
	void print(void) override {
	}
		list<int> e = {};
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
		this->l->print();
		this->r->print();
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
	}
	RX<C> *next;
};
template<typename C>
class RX_Circ : public RX<C> {
public:

	RX_Circ(RX<C> *initL, RX<C> *initR) : l(initL), r(initR) {}
	void print(void) override {
		this->l->print();
		this->r->print();
	}
	RX<C> *l;
	RX<C> *r;
};
#endif