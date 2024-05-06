#ifndef HEADER_H 
#define HEADER_H

using namespace std;
#include<iostream>
class kvad
{
private:
	double a, b, c;

public:
	kvad();
	kvad(double a_val, double b_val, double c_val);
	double getA();
	double getB();
	double getC();
	double calculatedisc();
	void printfun(ostream& out);

};

ostream& operator << (ostream &out, kvad el);

#endif