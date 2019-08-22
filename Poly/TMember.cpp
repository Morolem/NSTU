#include "TMember.h"
#include <stdio.h>
#include <string.h>

bool TMember::operator<(TMember &A)
{
	return (A.FDegree < this->FDegree);
}

TMember TMember::operator+(TMember A)
{
	if (this->FDegree == A.FDegree) {
		TMember tmp;
		tmp.FCoeff += A.FCoeff;
		tmp.toString();
		return tmp;
	}
	return *this;
}

TMember::TMember() {
	this->FCoeff = 0;
	this->FDegree = 1;
}

int TMember::getFCoeff()
{
	return this->FCoeff;
}

int TMember::getFDegree()
{
	return this->FDegree;
}

void TMember::setFCoeff(int c)
{
	this->FCoeff = c;
}

void TMember::setFDegree(int d)
{
	this->FDegree = d;
}

TMember::TMember(int c, int d)
{
	this->FCoeff = c;
	this->FDegree = d;
}

TMember::~TMember() { }

int TMember::Abs(int a)
{
	return a < 0 ? -a : a;
}

void TMember::numberToString(int c, char* t)
{
	int i = 0;
	if (c == 0)
	{
		t[i] = '0';
		t[++i] = '\0';
	}
	else
	{
		bool sign = (c < 0);
		for (i = 0; i < 30 && c != 0; ++i)
		{
			t[i] = Abs(c % 10) + 0x30;
			c /= 10;
		}
		if (sign)
		{
			t[i] = '-';
			++i;
		}
		int n = i;
		char b;
		for (i = 0; i < n / 2; ++i)
		{
			b = t[i];
			t[i] = t[n - i - 1];
			t[n - i - 1] = b;
		}
		t[n] = '\0';
	}
}

void TMember::difference()
{
	this->FCoeff *= this->FDegree;
	this->FDegree -= 1;
}

int TMember::calc(int x)
{
	if (x == 0) return 0;
	else
	{
		x = this->getFCoeff() * pow(x, this->getFDegree());
		return x;
	}
}

char* TMember::toString()
{
	char coeff[15], degree[15];

	if (this->FCoeff == 0)
	{
		buf[0] = '+';
		buf[1] = '0';
		buf[2] = '\0';
		return buf;
	}
	
	if (this->FDegree == 0)
	{
		this->numberToString(this->FCoeff, coeff);
		return coeff;
	}

	
	this->numberToString(this->FCoeff, coeff);
	this->numberToString(this->FDegree, degree);

	int  i = 0;
	for (i = 0; i < strlen(coeff); i++)
		buf[i] = coeff[i];
	buf[i++] = 'x';
	buf[i++] = '^';
	for (int k = 0; k < strlen(degree); k++, i++)
		buf[i] = degree[k];
	buf[i] = '\0';
	return buf;
}