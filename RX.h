/*
		TASK 41 - Define a data type to represent regular expressions.
*/
/*
	TASK #50 - Write an optimizer for regular expressions that simplifies them.
	*This was implemented within the RX object*
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
	virtual RX<State, C>* optimize(void) = 0;
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
	RX<State, C>* optimize(void) override {
		return this;
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
	RX<State, C>* optimize(void) override {
		return this;
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
	RX<State, C>* optimize(void) override {
		return this;
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
	RX<State, C>* optimize(void) override {
		
		if (getL()->id() == 'o') {
			if (getL()->getL()->id() == 'e') {
				delete getL()->getL();
				this->l = getL()->getR();
				delete getL()->getR();
				return this;
			}
			else if (getL()->getR()->id() == 'e') {
				delete getL()->getR();
				this->l = getL()->getL();
				delete getL()->getL();
				return this;
			}
				
		}	
		else if (getR()->id() == 'o') {
			if (getR()->getR()->id() == 'e') {
				delete getR()->getR();
				this->l = getR()->getL();
				delete getR()->getL();
				return this;
			}
			else if (getR()->getL()->id() == 'e') {
				delete getR()->getL();
				this->l = getR()->getR();
				delete getR()->getR();
				return this;
			}
		}
		else if (getL()->id() == 'n') {
			
			return getR();
		}
		else if (getR()->id() == 'n') {
			
			return getL();
		}
		else {
			return this;
		}
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
	RX<State, C>* optimize(void) override {
		if (getL()->id() == 'n') {
			RX<State,C>*temp = new RX_Epsilon<State,C>();
			return temp;
		}
		if (getL()->id() == 'e') {
			return getL();
		}
		if (getL() != nullptr) {
			if (getL()->getL() != nullptr && getL()->getR() != nullptr) {
				if (getL()->id() == 'o') {
					if (getL()->getL()->id() == 'e') {
						delete getL()->getL();
						this->next = getL()->getR();
						delete getL()->getR();
						return this;
					}
					else if (getL()->getR()->id() == 'e') {
						delete getL()->getR();
						this->next = getL()->getL();
						delete getL()->getL();
						return this;
					}
					else {
						return this;
					}
				}
				else {
					return this;
				}
			}
			else {
				return this;
			}
		}
		else {
			return this;
		}
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
	RX<State, C>* optimize(void) override {
		if (l->id() == 'n') {
			return this->l;
		}
		else if (r->id() == 'n') {
			return this->r;
		}
		else if (l->id() == 'e') {
			return getR();
		}
		else if (r->id() == 'e') {
			return getL();
		}
		else 
			return this;
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