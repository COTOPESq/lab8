#include <iostream>
#include "Header.h"

using namespace std;

kvad::kvad() {
	//cout << "hello" << endl;
	a = b = c = 0;
}

kvad::kvad(double a_val, double b_val, double c_val) : a(a_val), b(b_val), c(c_val) {}

double kvad::getA() {
	return a;
}

double kvad::getB() {
	return b;
}
double kvad::getC() {
	return c;
}

double kvad::calculatedisc() {
	return b * b - 4 * a * c;
}

void kvad::printfun(ostream& out) {
	out << "a: " << a << " b: " << b << " c: " << c << endl;
	out << calculatedisc() << endl;
}

ostream& operator << (ostream out, kvad el) {
	el.printfun(out);
	return out;
}

