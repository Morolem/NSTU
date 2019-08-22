#pragma once
#include <math.h>
class TMember
{
private:
	int FCoeff, FDegree;
	void numberToString(int n, char* res); // перевод числа в строку
	char buf[64];
	int Abs(int a); // модуль числа а
public:
	TMember(int c, int d);
	TMember();
	~TMember();
	int getFCoeff(); // получить коэффициент
	int getFDegree(); // получить степень
	void setFCoeff(int c); // добавить коэф.
	void setFDegree(int d); // добавить степень
	void difference(); // продифференцировать
	int calc(int x); // вычислить элемент
	char* toString(); // перевод полинома в строку
	bool operator<(TMember &A);
	TMember operator+(TMember A);
};

